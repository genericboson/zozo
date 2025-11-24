using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;
using System;
using System.Collections.Generic;
using Zozo;

namespace Zozo
{
    public partial class LobbySocketImpl : AbstractSocket
    {
        static public StreamPeerTcp m_stream = new();
        static private StreamPeerTcp.Status m_lastStatus = StreamPeerTcp.Status.None;
        static private Queue<byte[]> m_sendQueue = new();

        static private int m_nextRecieveSize = 4;
        static private bool m_waitingHeader = true;

        public override StreamPeerTcp.Status GetLastStatus()
        {
            return m_lastStatus;
        }

        public override int GetNextReceiveSize()
        {
            return m_nextRecieveSize;
        }

        public override Queue<byte[]> GetSendQueue()
        {
            return m_sendQueue;
        }

        public override StreamPeerTcp GetStream()
        {
            return m_stream;
        }

        public override bool GetWaitingHeader()
        {
            return m_waitingHeader;
        }

        public override void SetLastStatus(StreamPeerTcp.Status newStatus)
        {
            m_lastStatus = newStatus;
        }

        public override void SetNextReceiveSize(int nextSize)
        {
            m_nextRecieveSize = nextSize;
        }

        public override void SetWaitingHeader(bool isWaitingHeader)
        {
            m_waitingHeader = isWaitingHeader;
        }
    }
}
