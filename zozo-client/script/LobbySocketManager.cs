using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Zozo;

namespace ZozoClient.script
{
    public partial class LobbySocketManager : SocketManager
    {
        protected override void ConsumePayload(ByteBuffer bb)
        {
            var lobbyMessage = LobbyMessage.GetRootAsLobbyMessage(bb);

            switch (lobbyMessage.PayloadType)
            {
                case LobbyPayload.AuthAck:
                    ReceiveAuthAck(lobbyMessage);
                    break;
                case LobbyPayload.LoginAck:
                    ReceiveLoginAck(lobbyMessage);
                    break;
                default:
                    GD.PrintErr($"Unknown PayloadType: {lobbyMessage.PayloadType}");
                    break;
            }
        }
    }
}
