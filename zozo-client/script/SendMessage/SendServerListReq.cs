using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;
using System;
using System.Diagnostics;

namespace Zozo
{
    public partial class SocketManager : Node
    {
        public void SendServerListReq()
        {
            SendCommonLogic((FlatBufferBuilder fbb) =>
            {
                ServerListReq.StartServerListReq(fbb);
                var loginReq = ServerListReq.EndServerListReq(fbb);

                var message = LobbyMessage.CreateLobbyMessage(fbb, LobbyPayload.ServerListReq, loginReq.Value);
                fbb.Finish(message.Value);
            });
        }
    }
}
