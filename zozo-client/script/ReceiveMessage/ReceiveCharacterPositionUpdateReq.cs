using GenericBoson.Zozo;
using Godot;
using System.Collections.Generic;
using System.Net.Sockets;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
        private PackedScene                    m_otherPlayerScene;
        static private Dictionary<int, Node2D> m_otherCharacters   = new();

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
            if (updateReq.Position == null)
            {
                GD.PrintErr("Position is null in CharacterPositionUpdateReq");
                return;
            }

            Node2D otherCharacter;
            if (m_otherCharacters.TryGetValue(updateReq.Id, out otherCharacter))
            {
                otherCharacter.Position = new Vector2(updateReq.Position.Value.X, updateReq.Position.Value.Y);
            }
            else
            {
                otherCharacter = m_otherPlayerScene.Instantiate<Node2D>();
                AddChild(otherCharacter);
                m_otherCharacters.Add(updateReq.Id, otherCharacter);
            }

            otherCharacter.Position = new Vector2(updateReq.Position.Value.X, updateReq.Position.Value.Y);
            otherCharacter.Scale = new Vector2(4.0f, 4.0f);

            var otherAnimation = otherCharacter.GetNode<AnimatedSprite2D>("OtherPlayerAnimation");
            if ( otherAnimation == null)
            {
                GD.PrintErr("OtherPlayerAnimation node not found");
                return;
            }

            switch(updateReq.Direction)
            {
                case GenericBoson.Zozo.Direction.Up:
                    if (updateReq.IsMoved)
                        otherAnimation.Play("walk_back");
                    else
                        otherAnimation.Play("idle_back");
                    break;
                case GenericBoson.Zozo.Direction.Down:
                    if (updateReq.IsMoved)
                        otherAnimation.Play("walk_front");
                    else
                        otherAnimation.Play("idle_front");
                    break;
                case GenericBoson.Zozo.Direction.Left:
                    otherAnimation.FlipH = true;
                    if (updateReq.IsMoved)
                        otherAnimation.Play("walk_side");
                    else
                        otherAnimation.Play("idle_side");
                    break;
                case GenericBoson.Zozo.Direction.Right:
                    otherAnimation.FlipH = false;
                    if (updateReq.IsMoved)
                        otherAnimation.Play("walk_side");
                    else
                        otherAnimation.Play("idle_side");
                    break;
            }
        }
    }
}
