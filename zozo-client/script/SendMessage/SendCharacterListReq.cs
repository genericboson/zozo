using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;
using System;
using System.Diagnostics;

namespace Zozo
{
    public partial class SocketManager : Node
    {
        public void SendCharacterListReq(string account, string token)
        {
            SendCommonLogic((FlatBufferBuilder fbb) =>
            {
                var accountStr = fbb.CreateString(account);
                var tokenStr = fbb.CreateString(token);
                var req = CharacterListReq.CreateCharacterListReq(fbb, accountStr, tokenStr);
                var message = LobbyMessage.CreateLobbyMessage(fbb, LobbyPayload.CharacterListReq, req.Value);
                fbb.Finish(message.Value);
            });
        }
    }
}
