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

        public AbstractSocket()
        {
            GetStream().SetNoDelay(true);
        }

        public void EnqueueSend(byte[] data)
        {
            GetSendQueue().Enqueue(data);
        }

        public bool CheckConnect(string ipStr, string portStr)
        {
            var startStatus = GetStream().GetStatus();

            if (startStatus == StreamPeerTcp.Status.Connected)
            {
                if (GetLastStatus() != StreamPeerTcp.Status.Connected)
                    GD.Print($"Connected");

                SetLastStatus(startStatus);
                return true;
            }

            if (GetLastStatus() == StreamPeerTcp.Status.Connected)
            {
                SetLastStatus(startStatus);
                GD.Print($"Disconnected");
                return false;
            }

            var err = GetStream().ConnectToHost(ipStr, int.Parse(portStr));
            if (err != Error.Ok)
            {
                GD.PrintErr($"ConnectToHost error: {err}");
                return false;
            }

            SetLastStatus(startStatus);

            if (startStatus == StreamPeerTcp.Status.Connected)
            {
                GD.Print($"Connected");
                return true;
            }

            return false;
        }

        public void SendAllMessage()
        {
            while (GetSendQueue().TryDequeue(out var data))
            {
                var status = GetStream().GetStatus();
                GD.Print($"Stream Status: {status}");
                var err = GetStream().PutData(data);
                if (err != Error.Ok)
                    GD.PrintErr($"PutData error: {err}");
            }
        }

        public void ReceiveMessage(Action<ByteBuffer> callable)
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
               callable(bb);
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