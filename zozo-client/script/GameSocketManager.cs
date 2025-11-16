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
    public partial class GameSocketManager : SocketManager
    {
        protected override void ConsumePayload(ByteBuffer bb)
        {
            var lobbyMessage = GameMessage.GetRootAsGameMessage(bb);

            switch (lobbyMessage.PayloadType)
            {
                case GamePayload.CharacterListAck:
                    ReceiveCharacterListAck(lobbyMessage);
                    break;
                default:
                    GD.PrintErr($"Unknown PayloadType: {lobbyMessage.PayloadType}");
                    break;
            }
        }
    }
}
