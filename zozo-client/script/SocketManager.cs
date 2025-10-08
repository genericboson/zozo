using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;
using System;
using System.Diagnostics;

public partial class SocketManager : Node
{
    static public ZZTcpSocket m_zzSocket = new();

    public override void _Ready()
    {
        m_zzSocket._Ready();
    }

    public override void _Process(double delta)
    {
        m_zzSocket._Process(delta);
    }

    public void SendCharacterMove(float x, float y)
    {
        var fbb = new FlatBufferBuilder(1);
        var characterMoveReq = CharacterMoveReq.CreateCharacterMoveReq(fbb, x, y);
        var message = GameMessage.CreateGameMessage(fbb, GamePayload.CharacterMoveReq, characterMoveReq.Value);
        fbb.Finish(message.Value);

        var msg = fbb.SizedByteArray();

        #region for_debugging
        //{
        //    var byteStr = "";
        //    foreach (var b in msg)
        //    {
        //        byteStr += b.ToString() + " ";
        //    }

        //    GD.Print($"SendCharacterMove: {byteStr}");
        //}
        #endregion

        var sizeBytes = BitConverter.GetBytes(msg.Length);
        Debug.Assert(sizeBytes.Length == 4);
        m_zzSocket.EnqueueSend(sizeBytes);
        m_zzSocket.EnqueueSend(msg);
    }

    public void SendLogin(string account, string password)
    {
        var fbb = new FlatBufferBuilder(1);
        var accountStr = fbb.CreateString(account);
        var passwordStr = fbb.CreateString(password);
        var loginReq = LoginReq.CreateLoginReq(fbb, accountStr, passwordStr);
        var message = LobbyMessage.CreateLobbyMessage(fbb, LobbyPayload.LoginReq, loginReq.Value);
        fbb.Finish(message.Value);

        var msg = fbb.SizedByteArray();

        #region for_debugging
        //{
        //    var byteStr = "";
        //    foreach (var b in msg)
        //    {
        //        byteStr += b.ToString() + " ";
        //    }

        //    GD.Print($"SendLogin: {byteStr}");
        //}
        #endregion

        var sizeBytes = BitConverter.GetBytes(msg.Length);
        Debug.Assert(sizeBytes.Length == 4);
        if(sizeBytes.Length != 4)
        {
            GD.PrintErr($"sizeBytes.Length != 4, length - {sizeBytes.Length}");
        }
        m_zzSocket.EnqueueSend(sizeBytes);
        m_zzSocket.EnqueueSend(msg);
    }
}