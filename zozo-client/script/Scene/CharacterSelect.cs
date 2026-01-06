using Godot;
using System;
using System.Runtime.CompilerServices;

public partial class CharacterSelect : Control
{
    private OptionButton m_characterDropDown;
    private Node m_globalNode;

    public override void _Ready()
    {
        base._Ready();

        m_characterDropDown = GetNode<OptionButton>("CharacterDropDown");
        m_characterDropDown.AddItem("Choose your character");

        m_globalNode = GetNode<Node>("/root/GDGlobal");
        if (m_globalNode == null)
        {
            GD.PrintErr("Global node is null");
        }

        m_globalNode.Call("SendCharacterListReq");
    }

    public void _OnBackButtonPressed()
    {
        GetTree().ChangeSceneToFile("res://scene/Lobby.tscn");
    }

    public void _OnSelectButtonPressed()
    {
        m_globalNode.Call("SendCharacterSelectReq", m_characterDropDown.GetSelectedId());
    }

    public void _AddCharacters(Godot.Collections.Dictionary<long, string> characters)
    {
        foreach (var pair in characters)
        {
            m_characterDropDown.AddItem(pair.Value, (int)pair.Key);
        }
    }
}
