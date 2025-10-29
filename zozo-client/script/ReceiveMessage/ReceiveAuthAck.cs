using GenericBoson.Zozo;
using Godot;

namespace Zozo
{
    public partial class SocketManager : Node
    {
        public void ReceiveAuthAck(LobbyMessage lobbyMessage)
        {
            var authAck = lobbyMessage.PayloadAsAuthAck();
            ConsumeResultCode(authAck.ResultCode);
        }

        private void ConsumeResultCode(ResultCode resultCode)
        {
            switch(resultCode)
            {
                case ResultCode.Success:
                    GetTree().ChangeSceneToFile("res://scene/CharacterSelect.tscn");
                    break;
                case ResultCode.NewAccount:
                    GetTree().ChangeSceneToFile("res://scene/CharacterCreate.tscn");
                    break;
                case ResultCode.WrongPassword:
                    using (var globalNode = GetNode<Node>("/root/Global"))
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
