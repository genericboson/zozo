using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;
using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace Zozo
{
    public partial class SocketManager
    {
        static public StreamPeerTcp m_stream = new();
        static private StreamPeerTcp.Status m_lastStatus = StreamPeerTcp.Status.None;
        static private Queue<byte[]> m_sendQueue = new();

        static private int m_nextRecieveSize = 4;
        static private bool m_waitingHeader = true;

        public SocketManager()
        {
            m_stream.SetNoDelay(true);
        }

        public void EnqueueSend(byte[] data)
        {
            m_sendQueue.Enqueue(data);
        }

        public bool CheckConnect()
        {
            var status = m_stream.GetStatus();

            if (status == StreamPeerTcp.Status.Connected)
                return true;

            if (m_lastStatus == StreamPeerTcp.Status.Connected)
            {
                GD.Print($"Disconnected");
                return false;
            }

            var err = m_stream.ConnectToHost("127.0.0.1", 8002);
            if (err != Error.Ok)
            {
                GD.PrintErr($"ConnectToHost error: {err}");
                return false;
            }

            GD.Print($"Connected");
            m_lastStatus = status;

            return true;
        }

        public void SendAllMessage()
        {
            while (m_sendQueue.TryDequeue(out var data))
            {
                var err = m_stream.PutData(data);
                if (err != Error.Ok)
                    GD.PrintErr($"PutData error: {err}");
            }
        }

        public void ReceiveMessage()
        {
            if (m_stream.GetAvailableBytes() <= 0)
                return;

            // Godot.StreamPeerTcp scatter and gather automatically
            // Checked from StreamPeerSocket::read in godot/core/io/stream__peer_socket.cpp

            var received = m_stream.GetData(m_nextRecieveSize);

            var errorCode = (Godot.Error)received[0].AsInt32();
            var buffer = received[1].AsByteArray();

            if (m_waitingHeader)
            {
                m_nextRecieveSize = System.BitConverter.ToInt32(buffer, 0);
                m_waitingHeader = false;
            }
            else
            {
                m_nextRecieveSize = 4;
                m_waitingHeader = true;

                var bb = new ByteBuffer(buffer);
                ConsumePayload(bb);
            }
        }

        private void SendCommonLogic(Action<FlatBufferBuilder> callable)
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