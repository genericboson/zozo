using GenericBoson.Zozo;
using Godot;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
        public void RecvCharacterSelectAck(GameMessage gameMessage)
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

                        GetTree().ChangeSceneToFile("res://scene/Main.tscn");
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
