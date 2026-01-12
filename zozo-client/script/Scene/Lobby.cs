using Godot;
using System;

public partial class Lobby : Control
{
    private TextEdit     m_accountInput;
    private TextEdit     m_passwordInput;
    private OptionButton m_serverSelect;

    private Node m_globalNode;

    public void _Ready()
    {
        m_accountInput  = GetNode<TextEdit>("AccountInput");
        m_passwordInput = GetNode<TextEdit>("PasswordInput");
        m_serverSelect  = GetNode<OptionButton>("ServerSelect");

        m_globalNode = GetNode<Node>("/root/GDGlobal");
        if (m_globalNode == null)
        {
            GD.PrintErr("Global node is null");
        }
    }

    public void _OnStartButtonPressed()
    {
        m_globalNode.Set("account", m_accountInput.Text);
        m_globalNode.Call("SendAuthReq", 
            m_serverSelect.GetSelectedId(), 
            m_accountInput.Text, 
            m_passwordInput.Text );
    }
    public void _OnSettingButtonPressed()
    {

    }

    public void _AddPassword()
    {

    }

    public void _AddServers()
    {

    }
}
