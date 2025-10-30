using GenericBoson.Zozo;
using Godot;

namespace Zozo
{
    public partial class SocketManager : Node
    {
        public void ReceiveAuthAck(LobbyMessage lobbyMessage)
        {
            var authAck = lobbyMessage.PayloadAsAuthAck();
            ConsumeAuthAck(authAck);
        }

        private void ConsumeAuthAck(AuthAck ack)
        {
            using (var globalNode = GetNode<Node>("/root/Global"))
            {
                switch (ack.ResultCode)
                {
                    case ResultCode.Success:
                        {
                            globalNode.Set("token", ack.Token);
                            GetTree().ChangeSceneToFile("res://scene/CharacterSelect.tscn");
                        }
                        break;
                    case ResultCode.NewAccount:
                        {
                            globalNode.Set("token", ack.Token);
                            GetTree().ChangeSceneToFile("res://scene/CharacterCreate.tscn");
                        }
                        break;
                    case ResultCode.WrongPassword:
                        {
                            globalNode.Call("message_box", "Wrong password");
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
