using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
        public void SendCharacterPositionUpdateReq(float x, float y)
        {
            m_gameImpl.SendCommonLogic((FlatBufferBuilder fbb) =>
            {
                var updateReq = CharacterMoveReq.CreateCharacterMoveReq(fbb, x, y);
                var message = GameMessage.CreateGameMessage(fbb, GamePayload.CharacterPositionUpdateReq, updateReq.Value);
                fbb.Finish(message.Value);
            });
        }
    }
}