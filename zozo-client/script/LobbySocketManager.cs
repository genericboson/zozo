using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Zozo;

namespace ZozoClient.script
{
    public partial class LobbySocketManager : Node
    {
        private SocketManager m_socketManager = new();

        public override void _Process(double delta)
        {
            GD.Print("test!");

            m_socketManager.m_stream.Poll();

            if (!CheckConnect())
                return;

            SendAllMessage();
            ReceiveMessage();
        }

        protected override void ConsumePayload(ByteBuffer bb)
        {
            var lobbyMessage = LobbyMessage.GetRootAsLobbyMessage(bb);

            switch (lobbyMessage.PayloadType)
            {
                case LobbyPayload.AuthAck:
                    ReceiveAuthAck(lobbyMessage);
                    break;
                case LobbyPayload.ServerListAck:
                    ReceiveServerListAck(lobbyMessage);
                    break;
                default:
                    GD.PrintErr($"Unknown PayloadType: {lobbyMessage.PayloadType}");
                    break;
            }
        }
    }
}
