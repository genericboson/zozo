using Godot;
using System;

public partial class Lobby : Control
{
    private TextEdit     m_accountInput;
    private TextEdit     m_passwordInput;
    private OptionButton m_serverSelect;

    private Node m_globalNode;

    public override void _Ready()
    {
        m_accountInput  = GetNode<TextEdit>("AccountInput");
        m_passwordInput = GetNode<TextEdit>("PasswordInput");
        m_serverSelect  = GetNode<OptionButton>("ServerSelect");

        m_globalNode = GetNode<Node>("/root/GDGlobal");
        if (m_globalNode == null)
        {
            GD.PrintErr("Global node is null");
            return;
        }

        var startButton = GetNode<Button>("Start");
        var settingButton = GetNode<Button>("Setting");
        var exitButton = GetNode<Button>("Exit");

        startButton.Pressed += _OnStartButtonPressed;
        settingButton.Pressed += _OnSettingButtonPressed;
        exitButton.Pressed += () => m_globalNode.GetTree().Quit();

        m_serverSelect.AddItem("Choose server");

        CSGlobal.Instance.lobbySocketManager.SendServerListReq();
    }

    public void _OnStartButtonPressed()
    {
        CSGlobal.Instance.account =  m_accountInput.Text;
        CSGlobal.Instance.lobbySocketManager.SendAuthReq(
            m_serverSelect.GetSelectedId(),
            m_accountInput.Text,
            m_passwordInput.Text);
    }
    public void _OnSettingButtonPressed()
    {
        m_globalNode.Call("message_box", "개발 예정...");
    }

    public void _AddServers(Godot.Collections.Dictionary<int, string> servers)
    {
        foreach (var server in servers)
        {
            m_serverSelect.AddItem(server.Value, server.Key);
        }
    }
}
