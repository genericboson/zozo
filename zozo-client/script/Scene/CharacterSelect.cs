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

        var backButton = GetNode<Button>("BackButton");
        var selectButton = GetNode<Button>("SelectButton");

        backButton.Pressed += _OnBackButtonPressed;
        selectButton.Pressed += _OnSelectButtonPressed;

        m_globalNode = GetNode<Node>("/root/GDGlobal");
        if (m_globalNode == null)
        {
            GD.PrintErr("Global node is null");
        }

        CSGlobal.Instance.gameSocketManager.SendCharacterListReq();
    }

    public void _OnBackButtonPressed()
    {
        var result = m_globalNode.GetTree().ChangeSceneToFile("res://scene/Lobby.tscn");
        if (result != Error.Ok)
        {
            GD.PrintErr($"Failed to change scene to Lobby. Error - {result}");
        }
    }

    public void _OnSelectButtonPressed()
    {
        CSGlobal.Instance.gameSocketManager.SendCharacterSelectReq(m_characterDropDown.GetSelectedId());
    }

    public void _AddCharacters(Godot.Collections.Dictionary<long, string> characters)
    {
        foreach (var pair in characters)
        {
            m_characterDropDown.AddItem(pair.Value, (int)pair.Key);
        }
    }
}
