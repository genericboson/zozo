using Godot;
using System;
using Zozo;

public partial class Player : CharacterBody2D
{
    private const int SPEED = 400;

    private AnimatedSprite2D m_stateAnimation;
    private double m_accumulatedDelta = 0.0;

    public override void _Ready()
    {
        base._Ready();

        m_stateAnimation = GetNode<AnimatedSprite2D>("PlayerAnimation");
    }

    public override void _PhysicsProcess(double delta)
    {
        base._PhysicsProcess(delta);

        var direction = GenericBoson.Zozo.Direction.None;

        if (Input.IsActionPressed("left"))
        {
            Position -= new Vector2(SPEED * (float)delta, 0);
            direction = GenericBoson.Zozo.Direction.Left;

            m_stateAnimation.FlipH = true;
            m_stateAnimation.Play("walk_side");
        }
        else if (Input.IsActionPressed("right"))
        {
            Position += new Vector2(SPEED * (float)delta, 0);
            direction = GenericBoson.Zozo.Direction.Right;

            m_stateAnimation.FlipH = false;
            m_stateAnimation.Play("walk_side");
        }
        else if (Input.IsActionJustReleased("left"))
        {
            m_stateAnimation.FlipH = true;
            m_stateAnimation.Play("idle_side");
        }
        else if (Input.IsActionJustReleased("right"))
        {
            m_stateAnimation.FlipH = false;
            m_stateAnimation.Play("idle_side");
        }

        if (Input.IsActionPressed("up"))
        {
            Position -= new Vector2(0, SPEED * (float)delta);
            direction = GenericBoson.Zozo.Direction.Up;

            m_stateAnimation.Play("walk_back");
        }
        else if (Input.IsActionPressed("down"))
        {
            Position += new Vector2(0, SPEED * (float)delta);
            direction = GenericBoson.Zozo.Direction.Down;

            m_stateAnimation.Play("walk_front");
        }
        else if (Input.IsActionJustReleased("up"))
        {
            m_stateAnimation.Play("idle_back");
        }
        else if (Input.IsActionJustReleased("down"))
        {
            m_stateAnimation.Play("idle_front");
        }

        MoveAndSlide();

        m_accumulatedDelta += delta;
        if (CSGlobal.SECOND_PER_FRAME < m_accumulatedDelta)
        {
            m_accumulatedDelta = 0.0;

            if (direction != GenericBoson.Zozo.Direction.None)
            {
                AfterMove(direction);
            }
        }
    }

    private void AfterMove(GenericBoson.Zozo.Direction direction)
    {
        using (var globalNode = GetNode<Node>("/root/GDGlobal"))
        {
            globalNode.Call("SendCharacterPositionUpdateReq", Position.X, Position.Y, (int)direction);
        }
    }
}
