using GenericBoson.Zozo;
using Godot;

namespace Zozo
{
    public partial class SocketManager : Node
    {
        public void ReceiveAuthAck(LobbyMessage lobbyMessage)
        {
            var authAck = lobbyMessage.PayloadAsAuthAck();

            Node gdscriptNode = GetNode<Node>("/root/Lobby");
            if (gdscriptNode != null)
            {
                gdscriptNode.Call("consumeAuthAck", (int)authAck.ResultCode);
            }
            else
            {
                GD.PrintErr("Could not find MyGDScriptNode.");
            }
        }
    }
}
