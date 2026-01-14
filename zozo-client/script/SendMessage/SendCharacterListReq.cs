using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;
using System;
using System.Diagnostics;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
        public void SendCharacterListReq()
        {
            m_gameImpl.SendCommonLogic((FlatBufferBuilder fbb) =>
            {
                var tokenStr = fbb.CreateString(CSGlobal.Instance.token);
                var req = CharacterListReq.CreateCharacterListReq(fbb, CSGlobal.Instance.user_id, tokenStr);
                var message = GameMessage.CreateGameMessage(fbb, GamePayload.CharacterListReq, req.Value);
                fbb.Finish(message.Value);
            });
        }
    }
}
