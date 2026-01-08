using Godot;
using System;
using Zozo;

public partial class Controllable : Node
{
    private const int SPEED = 400;

    private CharacterBody2D m_parent;
    private AnimatedSprite2D m_stateAnimation;
    private double m_accumulatedDelta = 0.0;

    public override void _Ready()
    {
        base._Ready();

        m_parent = GetParent<CharacterBody2D>();
        if (m_parent == null)
        {
            GD.PrintErr("parent node not found or not CharacterBody2D");
            return;
        }

        m_stateAnimation = m_parent.GetNode<AnimatedSprite2D>("PlayerAnimation");
        if (m_stateAnimation == null)
        {
            GD.PrintErr("PlayerAnimation node not found");
            return;
        }
        m_stateAnimation.Play("idle_front");
    }

    public override void _PhysicsProcess(double delta)
    {
        base._PhysicsProcess(delta);

        var isMoved   = true;
        var direction = GenericBoson.Zozo.Direction.None;

        if (Input.IsActionPressed("left"))
        {
            m_parent.Position -= new Vector2(SPEED * (float)delta, 0);
            direction = GenericBoson.Zozo.Direction.Left;
            isMoved   = true;

            m_stateAnimation.FlipH = true;
            m_stateAnimation.Play("walk_side");
        }
        else if (Input.IsActionPressed("right"))
        {
            m_parent.Position += new Vector2(SPEED * (float)delta, 0);
            direction = GenericBoson.Zozo.Direction.Right;
            isMoved   = true;

            m_stateAnimation.FlipH = false;
            m_stateAnimation.Play("walk_side");
        }
        else if (Input.IsActionJustReleased("left"))
        {
            direction = GenericBoson.Zozo.Direction.Left;
            isMoved   = false;

            m_stateAnimation.FlipH = true;
            m_stateAnimation.Play("idle_side");
        }
        else if (Input.IsActionJustReleased("right"))
        {
            direction = GenericBoson.Zozo.Direction.Right;
            isMoved   = false;

            m_stateAnimation.FlipH = false;
            m_stateAnimation.Play("idle_side");
        }

        if (Input.IsActionPressed("up"))
        {
            m_parent.Position -= new Vector2(0, SPEED * (float)delta);
            direction = GenericBoson.Zozo.Direction.Up;
            isMoved   = true;

            m_stateAnimation.Play("walk_back");
        }
        else if (Input.IsActionPressed("down"))
        {
            m_parent.Position += new Vector2(0, SPEED * (float)delta);
            direction = GenericBoson.Zozo.Direction.Down;
            isMoved   = true;

            m_stateAnimation.Play("walk_front");
        }
        else if (Input.IsActionJustReleased("up"))
        {
            direction = GenericBoson.Zozo.Direction.Up;
            isMoved   = false;
            m_stateAnimation.Play("idle_back");
        }
        else if (Input.IsActionJustReleased("down"))
        {
            direction = GenericBoson.Zozo.Direction.Down;
            isMoved   = false;
            m_stateAnimation.Play("idle_front");
        }

        m_parent.MoveAndSlide();

        m_accumulatedDelta += delta;
        if (!isMoved || CSGlobal.SECOND_PER_FRAME < m_accumulatedDelta)
        {
            if (isMoved)
            {
                m_accumulatedDelta = 0.0;
            }

            if (direction != GenericBoson.Zozo.Direction.None)
            {
                AfterMove(direction, isMoved);
            }
        }
    }

    private void AfterMove(GenericBoson.Zozo.Direction direction, bool isMoved)
    {
        using (var globalNode = GetNode<Node>("/root/GDGlobal"))
        {
            globalNode.Call("SendCharacterPositionUpdateReq", m_parent.Position.X, m_parent.Position.Y, (int)direction, isMoved);
        }
    }
}
