using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
        public void SendCharacterPositionUpdateReq(float x, float y, GenericBoson.Zozo.Direction direction, bool isMoved)
        {
            m_gameImpl.SendCommonLogic((FlatBufferBuilder fbb) =>
            {
                var position = GenericBoson.Zozo.Vector2F.CreateVector2F(fbb, x, y);

                fbb.StartTable(4);
                CharacterPositionUpdateReq.AddId(fbb, (int)CSGlobal.Instance.characterData.Id);
                CharacterPositionUpdateReq.AddPosition(fbb, position);
                CharacterPositionUpdateReq.AddDirection(fbb, direction);
                CharacterPositionUpdateReq.AddIsMoved(fbb, isMoved);
                var updateReq = CharacterPositionUpdateReq.EndCharacterPositionUpdateReq(fbb);

                var message = GameMessage.CreateGameMessage(fbb, GamePayload.CharacterPositionUpdateReq, updateReq.Value);
                fbb.Finish(message.Value);
            });
        }
    }
}