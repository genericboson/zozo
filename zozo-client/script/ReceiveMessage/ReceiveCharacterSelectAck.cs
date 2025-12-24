using GenericBoson.Zozo;
using Godot;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
        public void ReceiveCharacterSelectAck(GameMessage gameMessage)
        {
            GD.Print("test1");
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
                        var position = ack.Pos.Value.Position;
                        selectNode.Call("_select_character", position.Value.X, position.Value.Y);
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
