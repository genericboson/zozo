using GenericBoson.Zozo;
using Godot;

namespace Zozo
{
    public partial class LobbySocketManager : Node
    {
        public void ReceiveAuthAck(LobbyMessage lobbyMessage)
        {
            var authAck = lobbyMessage.PayloadAsAuthAck();
            ConsumeAuthAck(authAck);
        }

        private void ConsumeAuthAck(AuthAck ack)
        {
            using (var globalNode = GetNode<Node>("/root/GDGlobal"))
            {
                switch (ack.ResultCode)
                {
                    case ResultCode.Success:
                    case ResultCode.NewAccount:
                        {
                            globalNode.Set("token", ack.Token);
                            globalNode.Set("user_id", ack.UserId);
                            globalNode.Set("game_server_ip", ack.Ip);
                            globalNode.Set("game_server_port", ack.Port);
                        }
                        break;
                }

                switch (ack.ResultCode)
                {
                    case ResultCode.Success:
                        {
                            GetTree().ChangeSceneToFile("res://scene/CharacterSelect.tscn");
                        }
                        break;
                    case ResultCode.NewAccount:
                        {
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
