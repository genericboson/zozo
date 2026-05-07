using Godot;
using System;

namespace Zozo
{
    public partial class AppleTree : Node2D
    {
        private bool hasApple = true;
        private bool playerInArea = false;
        private AnimatedSprite2D treeAnimation;

        public override void _Ready()
        {
            base._Ready();
            treeAnimation = GetNode<AnimatedSprite2D>("TreeAnimation");
        }

        public override void _Process(double delta)
        {
            base._Process(delta);

            if (hasApple)
            {
                treeAnimation.Play("apples");
                if (playerInArea && Input.IsActionJustPressed("e"))
                {
                    hasApple = false;
                }
            }
            else
            {
                treeAnimation.Play("no_apples");
            }
        }

        public void _OnPickableAreaBodyEntered(Node body)
        {
            if (body.HasNode("Controllable"))
            {
                playerInArea = true;
            }
        }

        public void _OnPickableAreaBodyExited(Node body)
        {
            if (body.HasNode("Controllable"))
            {
                playerInArea = false;
            }
        }
    }
}
