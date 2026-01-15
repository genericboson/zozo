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
            switch (ack.ResultCode)
            {
                case ResultCode.Success:
                case ResultCode.NewAccount:
                    {
                        CSGlobal.Instance.token            = ack.Token;
                        CSGlobal.Instance.user_id          = ack.UserId;
                        CSGlobal.Instance.game_server_ip   = ack.Ip;
                        CSGlobal.Instance.game_server_port = ack.Port;

                        GD.Print($"[AuthAck] Token : {ack.Token}, UserId : {ack.UserId}, GameServerIp : {ack.Ip}, GameServerPort : {ack.Port}");
                    }
                    break;
            }

            switch (ack.ResultCode)
            {
                case ResultCode.Success:
                    {
                        var changeSceneToSelectResult = GetTree().ChangeSceneToFile("res://scene/CharacterSelect.tscn");
                        if (changeSceneToSelectResult != Error.Ok)
                        {
                            GD.PrintErr($"Failed to change scene to CharacterSelect. Error - {changeSceneToSelectResult}");
                        }
                    }
                    break;
                case ResultCode.NewAccount:
                    {
                        var changeSceneToCreateResult = GetTree().ChangeSceneToFile("res://scene/CharacterCreate.tscn");
                        if (changeSceneToCreateResult != Error.Ok)
                        {
                            GD.PrintErr($"Failed to change scene to CharacterCreate. Error - {changeSceneToCreateResult}");
                        }
                    }
                    break;
                case ResultCode.WrongPassword:
                    {
                        CSGlobal.Instance.MessageBox("message_box", "Wrong password");
                    }
                    break;
                case ResultCode.AlreadyLoggedIn:
                    {
                        CSGlobal.Instance.MessageBox("message_box", "Already logged in");
                    }
                    break;
                default:
                    {
                        CSGlobal.Instance.MessageBox("message_box", $"Wrong result code : {ack.ResultCode}");
                    }
                    break;
            }
        }
    }
}
