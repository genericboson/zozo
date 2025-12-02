using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
        public void SendCharacterSelectReq(long characterId)
        {
            m_gameImpl.SendCommonLogic((FlatBufferBuilder fbb) =>
            {
                var characterSelectReq = CharacterSelectReq.CreateCharacterSelectReq(fbb, characterId);
                var message = GameMessage.CreateGameMessage(fbb, GamePayload.CharacterSelectReq, characterSelectReq.Value);
                fbb.Finish(message.Value);
            });
        }
    }
}
