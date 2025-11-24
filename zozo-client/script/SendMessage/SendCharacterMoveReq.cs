using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;
using System;
using System.Diagnostics;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
        public void SendCharacterMoveReq(float x, float y)
        {
            m_gameImpl.SendCommonLogic((FlatBufferBuilder fbb) =>
            {
                var characterMoveReq = CharacterMoveReq.CreateCharacterMoveReq(fbb, x, y);
                var message = GameMessage.CreateGameMessage(fbb, GamePayload.CharacterMoveReq, characterMoveReq.Value);
                fbb.Finish(message.Value);
            });
        }
    }
}