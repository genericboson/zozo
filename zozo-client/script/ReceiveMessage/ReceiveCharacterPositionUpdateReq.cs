using GenericBoson.Zozo;
using Godot;
using System.Collections.Generic;
using System.Net.Sockets;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
        private PackedScene           m_otherPlayerScene;
        static private Dictionary<int, Node2D> m_otherCharacters;

        public override void _Ready()
        {
            m_otherPlayerScene = ResourceLoader.Load<PackedScene>("res://scene/OtherPlayer.tscn");
        }

        public void ReceiveCharacterPositionUpdateReq(GameMessage gameMessage)
        {
            var updateReq = gameMessage.PayloadAsCharacterPositionUpdateReq();
            ConsumePositionUpdateReq(updateReq);
        }

        private void ConsumePositionUpdateReq(CharacterPositionUpdateReq updateReq)
        {
            if (m_otherCharacters.TryGetValue(updateReq.Id, out var otherCharacter))
            {
                otherCharacter.Position = new Vector2(updateReq.Position.Value.X, updateReq.Position.Value.Y);
                return;
            }

            var newNode = m_otherPlayerScene.Instantiate<Node2D>();
            newNode.Position = new Vector2(updateReq.Position.Value.X, updateReq.Position.Value.Y);
            AddChild(newNode);
        }
    }
}
