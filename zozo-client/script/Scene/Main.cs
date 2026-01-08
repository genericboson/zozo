using Godot;
using System;

public partial class Main : Node2D
{
    static private CharacterBody2D m_controllablePlayer;

    public override void _Ready()
    {
        base._Ready();

        if (m_controllablePlayer == null)
        {
            var playerScene = ResourceLoader.Load<PackedScene>("res://scene/Player.tscn");
            m_controllablePlayer = playerScene.Instantiate<CharacterBody2D>();

            var ysort = GetTree().CurrentScene.GetNode<Control>("Ysort");
            if (ysort == null)
            {
                GD.PrintErr("Ysort node not found");
                return;
            }

            var controllable = new Controllable();
            m_controllablePlayer.AddChild(controllable);
            ysort.AddChild(m_controllablePlayer);
        }

        var position = CSGlobal.Instance.characterData.Position;
        m_controllablePlayer.Position = new Vector2(position.Value.X, position.Value.Y);
        m_controllablePlayer.Scale = new Vector2(4.0f, 4.0f);
    }
}
