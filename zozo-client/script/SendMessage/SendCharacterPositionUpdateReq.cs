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
                var position = GenericBoson.Zozo.Vector2I.CreateVector2I(fbb, (int)x, (int)y);

                fbb.StartTable(2);
                CharacterPositionUpdateReq.AddId(fbb, (int)CSGlobal.Instance.characterData.Id);
                CharacterPositionUpdateReq.AddPosition(fbb, position);
                var updateReq = CharacterPositionUpdateReq.EndCharacterPositionUpdateReq(fbb);

                var message = GameMessage.CreateGameMessage(fbb, GamePayload.CharacterPositionUpdateReq, updateReq.Value);
                fbb.Finish(message.Value);
            });
        }
    }
}