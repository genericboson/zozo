using Godot;
using Google.FlatBuffers;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;

namespace Zozo
{
    abstract public partial class AbstractSocket
    {
        abstract public StreamPeerTcp GetStream();
        abstract public StreamPeerTcp.Status GetLastStatus();
        abstract public void SetLastStatus(StreamPeerTcp.Status newStatus);
        abstract public Queue<byte[]> GetSendQueue();

        abstract public int GetNextReceiveSize();
        abstract public void SetNextReceiveSize(int nextSize);
        abstract public bool GetWaitingHeader();
        abstract public void SetWaitingHeader(bool isWaitingHeader);

        abstract public void ConsumePayload(ByteBuffer bb);

        public AbstractSocket()
        {
            GetStream().SetNoDelay(true);
        }

        public void EnqueueSend(byte[] data)
        {
            GetSendQueue().Enqueue(data);
        }

        public bool CheckConnect()
        {
            var status = GetStream().GetStatus();

            if (status == StreamPeerTcp.Status.Connected)
                return true;

            if (GetLastStatus() == StreamPeerTcp.Status.Connected)
            {
                GD.Print($"Disconnected");
                return false;
            }

            var err = GetStream().ConnectToHost("127.0.0.1", 8002);
            if (err != Error.Ok)
            {
                GD.PrintErr($"ConnectToHost error: {err}");
                return false;
            }

            GD.Print($"Connected");
            SetLastStatus(status);

            return true;
        }

        public void SendAllMessage()
        {
            while (GetSendQueue().TryDequeue(out var data))
            {
                var err = GetStream().PutData(data);
                if (err != Error.Ok)
                    GD.PrintErr($"PutData error: {err}");
            }
        }

        public void ReceiveMessage()
        {
            if (GetStream().GetAvailableBytes() <= 0)
                return;

            // Godot.StreamPeerTcp scatter and gather automatically
            // Checked from StreamPeerSocket::read in godot/core/io/stream__peer_socket.cpp

            var received = GetStream().GetData(GetNextReceiveSize());

            var errorCode = (Godot.Error)received[0].AsInt32();
            var buffer = received[1].AsByteArray();

            if (GetWaitingHeader())
            {
                SetNextReceiveSize(System.BitConverter.ToInt32(buffer, 0));
                SetWaitingHeader(false);
            }
            else
            {
                SetNextReceiveSize(4);
                SetWaitingHeader(true);

                var bb = new ByteBuffer(buffer);
                ConsumePayload(bb);
            }
        }

        public void SendCommonLogic(Action<FlatBufferBuilder> callable)
        {
            var fbb = new FlatBufferBuilder(1);

            callable(fbb);

            var msg = fbb.SizedByteArray();
            
            #region for_debugging
            //{
            //    var byteStr = "";
            //    foreach (var b in msg)
            //    {
            //        byteStr += b.ToString() + " ";
            //    }

            //    GD.Print($"{callable.Method.Name}: {byteStr}");
            //}
            #endregion

            var sizeBytes = BitConverter.GetBytes(msg.Length);
            Debug.Assert(sizeBytes.Length == 4);
            if (sizeBytes.Length != 4)
            {
                GD.PrintErr($"sizeBytes.Length != 4, length - {sizeBytes.Length}");
            }

            EnqueueSend(sizeBytes);
            EnqueueSend(msg);
        }
    }
}