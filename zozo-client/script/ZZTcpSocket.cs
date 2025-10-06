using Godot;
using System.Collections.Generic;

public class ZZTcpSocket
{
    private StreamPeerTcp         m_stream     = new();
    private StreamPeerTcp.Status  m_lastStatus = StreamPeerTcp.Status.None;
    private Queue<byte[]>         m_sendQueue  = new();

    public ZZTcpSocket()
    {
        m_stream.SetNoDelay(true);
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
            m_stream.PutData(data);

        // receive
        if (m_stream.GetAvailableBytes() > 0)
        {
            // Do Godot.StreamPeerTcp scatter and gather automatically?
            var received = m_stream.GetData(m_stream.GetAvailableBytes());
            GD.Print(received.ToString());
        }
    }
}