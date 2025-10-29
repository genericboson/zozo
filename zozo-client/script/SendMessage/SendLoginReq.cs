using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;
using System;
using System.Diagnostics;

namespace Zozo
{
    public partial class SocketManager : Node
    {
        public void SendLoginReq(string account, string password)
        {
            SendCommonLogic((FlatBufferBuilder fbb) =>
            {
                var accountStr = fbb.CreateString(account);
                var passwordStr = fbb.CreateString(password);
                var loginReq = LoginReq.CreateLoginReq(fbb, accountStr, passwordStr);
                var message = LobbyMessage.CreateLobbyMessage(fbb, LobbyPayload.LoginReq, loginReq.Value);
                fbb.Finish(message.Value);
            });
        }
    }
}
