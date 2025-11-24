using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;
using System;
using System.Diagnostics;

namespace Zozo
{
    public partial class LobbySocketManager : Node
    {
        public void SendAuthReq(string account, string password)
        {
            m_lobbyImpl.SendCommonLogic((FlatBufferBuilder fbb) =>
            {
                var accountStr = fbb.CreateString(account);
                var passwordStr = fbb.CreateString(password);
                var authReq = AuthReq.CreateAuthReq(fbb, accountStr, passwordStr);
                var message = LobbyMessage.CreateLobbyMessage(fbb, LobbyPayload.AuthReq, authReq.Value);
                fbb.Finish(message.Value);
            });
        }
    }
}
