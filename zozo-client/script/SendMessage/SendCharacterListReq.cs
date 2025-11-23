using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;
using System;
using System.Diagnostics;

namespace Zozo
{
    public partial class SocketManager : Node
    {
        public void SendCharacterListReq(int user_id, string token)
        {
            SendCommonLogic((FlatBufferBuilder fbb) =>
            {
                var tokenStr = fbb.CreateString(token);
                var req = CharacterListReq.CreateCharacterListReq(fbb, user_id, tokenStr);
                var message = GameMessage.CreateGameMessage(fbb, GamePayload.CharacterListReq, req.Value);
                fbb.Finish(message.Value);
            });
        }
    }
}
