using GenericBoson.Zozo;
using Godot;
using System.Collections.Generic;

namespace Zozo
{
    public partial class SocketManager : Node
    {
        public void ReceiveLoginAck(LobbyMessage lobbyMessage)
        {
            var loginAck = lobbyMessage.PayloadAsLoginAck();

            var characterNames = new List<string>();
            for (var k = 0; k < loginAck.CharactersLength; ++k)
            {
                var character = loginAck.Characters(k);
                if (character is null)
                    continue;

                characterNames.Add(character.Value.Name);
            }

            Node gdscriptNode = GetNode<Node>("/root/Lobby");

            if (gdscriptNode != null)
            {
                gdscriptNode.Call("_test", characterNames.ToArray());
            }
            else
            {
                GD.PrintErr("Could not find MyGDScriptNode.");
            }
        }
    }
}
