using Godot;
using System.Collections.Generic;

public class ZZTcpSocket
{
    private StreamPeerTcp         m_stream     = new();
    private StreamPeerTcp.Status  m_lastStatus = StreamPeerTcp.Status.None;
    private Queue<byte[]>         m_sendQueue  = new();

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
            GD.Print($"Dequeued");
            var err = m_stream.PutData(data);
            if (err != Error.Ok)
                GD.PrintErr($"PutData error: {err}");
        }

        // receive
        if (m_stream.GetAvailableBytes() > 0)
        {
            // Godot.StreamPeerTcp scatter and gather automatically
            // Checked from StreamPeerSocket::read in godot/core/io/stream__peer_socket.cpp
            var received = m_stream.GetData(m_stream.GetAvailableBytes());
            GD.Print(received.ToString());
        }
    }
}