using GenericBoson.Zozo;
using Godot;
using System.Net.Sockets;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
        public void ReceiveCharacterPositionUpdateReq(GameMessage lobbyMessage)
        {
            var updateReq = gameMessage.PayloadAsReceiveCharacterPositionUpdateReq();
            ConsumePositionUpdateReq(updateReq);
        }

        private void ConsumePositionUpdateReq(CharacterPositionUpdateReq updateReq)
        {
            using (var globalNode = GetNode<Node>("/root/Main"))
            {
                selectNode.Call("_character_position_update", 
                    updateReq.Pos.Value.X, updateReq.Pos.Value.Y);
            }
        }
    }
}
