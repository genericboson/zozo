using Godot;
using System;

public partial class Lobby : Control
{
    private TextEdit     m_accountInput;
    private TextEdit     m_passwordInput;
    private OptionButton m_serverSelect;

    public void _Ready()
    {
        m_accountInput  = GetNode<TextEdit>("AccountInput");
        m_passwordInput = GetNode<TextEdit>("PasswordInput");
        m_serverSelect  = GetNode<OptionButton>("ServerSelect");
    }

    public void _OnStartButtonPressed()
    {

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
