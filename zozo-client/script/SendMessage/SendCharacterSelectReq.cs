using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
        public void SendCharacterSelectReq(long characterId, string token)
        {
            m_gameImpl.SendCommonLogic((FlatBufferBuilder fbb) =>
            {
                var tokenOffset = fbb.CreateString(token);
                var characterSelectReq = CharacterSelectReq.CreateCharacterSelectReq(fbb, characterId, tokenOffset);
                var message = GameMessage.CreateGameMessage(fbb, GamePayload.CharacterSelectReq, characterSelectReq.Value);
                fbb.Finish(message.Value);
            });
        }
    }
}
