using Godot;
using Google.FlatBuffers;
using System.Collections.Generic;
using GenericBoson.Zozo;
using System.Linq;
using System.Collections.Immutable;

public class ZZTcpSocket
{
    private StreamPeerTcp         m_stream          = new();
    private StreamPeerTcp.Status  m_lastStatus      = StreamPeerTcp.Status.None;
    private Queue<byte[]>         m_sendQueue       = new();

    private int                   m_nextRecieveSize = 4;
    private bool                  m_waitingHeader   = true;

    public ZZTcpSocket()
    {
        GD.Print($"ZZTcpSocket ctor");

        m_stream.SetNoDelay(true);
    }

    public void _Ready()
    {
        if (m_stream.GetStatus() == StreamPeerTcp.Status.Connected)
            return;

        var err = m_stream.ConnectToHost("127.0.0.1", 8002);
        if (err != Error.Ok)
            GD.PrintErr($"ConnectToHost error: {err}");
    }

    public void EnqueueSend(byte[] data)
    {
        m_sendQueue.Enqueue(data);
    }

    public void _Process(double delta)
    {
        m_stream.Poll();
        var status = m_stream.GetStatus();

        if (status != StreamPeerTcp.Status.Connected)
        {
            if (m_lastStatus == StreamPeerTcp.Status.Connected)
                GD.Print($"Disconnected");
            return;
        }
        else if (m_lastStatus == StreamPeerTcp.Status.Connected)
        {
            if (m_lastStatus != StreamPeerTcp.Status.Connected)
                GD.Print($"Connected");
        }

        // send
        while (m_sendQueue.TryDequeue(out var data))
        {
            var err = m_stream.PutData(data);
            if (err != Error.Ok)
                GD.PrintErr($"PutData error: {err}");
        }

        // receive
        if (m_stream.GetAvailableBytes() > 0)
        {
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
                var lobbyMessage = LobbyMessage.GetRootAsLobbyMessage(bb);

                switch(lobbyMessage.PayloadType)
                {
                    case LobbyPayload.LoginAck:
                        {
                            var loginAck = lobbyMessage.PayloadAsLoginAck();
                            //GD.Print($"Received LoginAck.Gameserverip-{loginAck.Gameserverip}, Gameserverport-{loginAck.Gameserverport}, Token-{loginAck.Token}");
                        }
                        break;
                    default:
                        {
                            GD.PrintErr($"Unknown PayloadType: {lobbyMessage.PayloadType}");
                        }
                        break;
                }
            }
        }
    }
}