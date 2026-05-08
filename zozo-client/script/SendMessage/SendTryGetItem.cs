using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;
using System;
using System.Diagnostics;

namespace Zozo
{
    // Temporary dummy
    public enum EItem
    {
        None = 0,
        Apple = 1,
    }

    public partial class GameSocketManager : Node
    {
        public void SendTryGetItem(Node itemNode, EItem itemType, int quantity)
        {
            m_gameImpl.SendCommonLogic((FlatBufferBuilder fbb) =>
            {
                var tokenStr = fbb.CreateString(CSGlobal.Instance.token);
                var req = TryGetItemReq.CreateTryGetItemReq(fbb);//, CSGlobal.Instance.user_id, tokenStr);
                var message = GameMessage.CreateGameMessage(fbb, GamePayload.TryGetItemReq, req.Value);
                fbb.Finish(message.Value);
            });
        }
    }
}
