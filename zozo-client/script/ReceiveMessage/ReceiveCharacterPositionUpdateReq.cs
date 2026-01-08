using GenericBoson.Zozo;
using Godot;
using System.Collections.Generic;
using System.Net.Sockets;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
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

            CharacterBody2D otherCharacter;
            if (m_otherCharacters.TryGetValue(updateReq.Id, out otherCharacter))
            {
                otherCharacter.Position = new Vector2(updateReq.Position.Value.X, updateReq.Position.Value.Y);
            }
            else
            {
                otherCharacter = m_playerScene.Instantiate<CharacterBody2D>();
                var ysort = GetTree().CurrentScene.GetNode<Control>("Ysort");
                if (ysort == null)
                {
                    GD.PrintErr("Ysort node not found");
                    return;
                }

                ysort.AddChild(otherCharacter);
                m_otherCharacters.Add(updateReq.Id, otherCharacter);
            }

            otherCharacter.Position = new Vector2(updateReq.Position.Value.X, updateReq.Position.Value.Y);
            otherCharacter.Scale = new Vector2(4.0f, 4.0f);

            var playerAnimation = otherCharacter.GetNode<AnimatedSprite2D>("PlayerAnimation");
            if ( playerAnimation == null)
            {
                GD.PrintErr("OtherPlayerAnimation node not found");
                return;
            }

            switch(updateReq.Direction)
            {
                case GenericBoson.Zozo.Direction.Up:
                    if (updateReq.IsMoved)
                        playerAnimation.Play("walk_back");
                    else
                        playerAnimation.Play("idle_back");
                    break;
                case GenericBoson.Zozo.Direction.Down:
                    if (updateReq.IsMoved)
                        playerAnimation.Play("walk_front");
                    else
                        playerAnimation.Play("idle_front");
                    break;
                case GenericBoson.Zozo.Direction.Left:
                    playerAnimation.FlipH = true;
                    if (updateReq.IsMoved)
                        playerAnimation.Play("walk_side");
                    else
                        playerAnimation.Play("idle_side");
                    break;
                case GenericBoson.Zozo.Direction.Right:
                    playerAnimation.FlipH = false;
                    if (updateReq.IsMoved)
                        playerAnimation.Play("walk_side");
                    else
                        playerAnimation.Play("idle_side");
                    break;
            }
        }
    }
}
