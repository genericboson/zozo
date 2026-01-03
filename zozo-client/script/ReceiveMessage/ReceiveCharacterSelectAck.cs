using GenericBoson.Zozo;
using Godot;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
        public void ReceiveCharacterSelectAck(GameMessage gameMessage)
        {
            var ack = gameMessage.PayloadAsCharacterSelectAck();
            ConsumeCharacterSelectAck(ack);
        }

        private void ConsumeCharacterSelectAck(CharacterSelectAck ack)
        {
            switch (ack.ResultCode)
            {
                case ResultCode.Success:
                    using (var selectNode = GetNode<Node>("/root/CharacterSelect"))
                    {
                        CSGlobal.Instance.characterData = ack.Data.Value;
                        var position = ack.Position.Value;
                        selectNode.Call("_select_character", position.X, position.Y);
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
