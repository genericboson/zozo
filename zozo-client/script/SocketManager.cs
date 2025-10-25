using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;
using System;
using System.Collections.Generic;
using System.Diagnostics;

public partial class SocketManager : Node
{
    static private StreamPeerTcp m_stream = new();
    static private StreamPeerTcp.Status m_lastStatus = StreamPeerTcp.Status.None;
    static private Queue<byte[]> m_sendQueue = new();

    static private int m_nextRecieveSize = 4;
    static private bool m_waitingHeader = true;

    public SocketManager()
    {
        m_stream.SetNoDelay(true);
    }

    public override void _Ready()
    {
    }

    public void EnqueueSend(byte[] data)
    {
        m_sendQueue.Enqueue(data);
    }

    public override void _Process(double delta)
    {
        m_stream.Poll();
        var status = m_stream.GetStatus();

        if (status != StreamPeerTcp.Status.Connected)
        {
            if (m_lastStatus == StreamPeerTcp.Status.Connected)
            {
                GD.Print($"Disconnected");
                return;
            }

            var err = m_stream.ConnectToHost("127.0.0.1", 8002);
            if (err != Error.Ok)
            {
                GD.PrintErr($"ConnectToHost error: {err}");
                return;
            }

            GD.Print($"Connected");
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

                switch (lobbyMessage.PayloadType)
                {
                    case LobbyPayload.LoginAck:
                        {
                            var loginAck = lobbyMessage.PayloadAsLoginAck();
                            for (var k = 0; k < loginAck.CharactersLength; ++k)
                            {
                                var character = loginAck.Characters(k);
                                if (character is null)
                                    continue;

                                var myGDScript = GD.Load<GDScript>("res://script/Lobby.gd");
                                var myGDScriptNode = (GodotObject)myGDScript.New(); // This is a GodotObject.

                                if (myGDScriptNode != null)
                                {
                                    myGDScriptNode.Call("_test", character.Value.Password);

                                    //Variant returnValue = gdScriptNode.Call("get_data");
                                    //GD.Print($"GDScript returned: {returnValue}");
                                }
                                else
                                {
                                    GD.PrintErr("Could not find MyGDScriptNode.");
                                }

                                GD.Print($"Received LoginAck.password-{character.Value.Password}");
                            }
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
        EnqueueSend(sizeBytes);
        EnqueueSend(msg);
    }

    public void SendLogin(string account, string password)
    {
        GD.Print("SendLogin");
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
        EnqueueSend(sizeBytes);
        EnqueueSend(msg);
    }
}