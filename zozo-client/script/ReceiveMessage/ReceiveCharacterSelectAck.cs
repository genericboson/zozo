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
                        GD.Print("test2");
                        CSGlobal.Instance.characterData = ack.Data.Value;
                        selectNode.Call("_select_character", ack.Pos.Value.X, ack.Pos.Value.Y);
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
