using Godot;

public partial class SocketManager : Node
{
    static public ZZTcpSocket m_zzSocket = new();

    public override void _Process(double delta)
    {
        m_zzSocket._Process(delta);
    }

    public void Send(byte[] data)
    {
        m_zzSocket.EnqueueSend(data);
    }
}