using GenericBoson.Zozo;
using Godot;
using Zozo;

public partial class CSGlobal : Node
{
    public static CSGlobal Instance { get; private set; }

    public CharacterInfo characterData = new();

    public LobbySocketManager lobbySocketManager = new();
    public GameSocketManager  gameSocketManager = new();

    public string account = "";
    public string token = "";
    public long   user_id = 0;
    public string game_server_ip = "";
    public string game_server_port = "";

    // frame per second = 33.3
    public const double SECOND_PER_FRAME = 0.03;

    public override void _Ready()
    {
        Instance = this;
    }

    public void MessageBox(string msg, string title = "Message")
    {
        var dialog = new AcceptDialog();
        dialog.DialogText = msg;
        dialog.Title = title;
        dialog.GetLabel().HorizontalAlignment = HorizontalAlignment.Center;

        var screenSize = DisplayServer.ScreenGetSize();
        dialog.SetSize(new Godot.Vector2I(screenSize.X / 4, 0));

        var scene_tree = Engine.GetMainLoop() as SceneTree;
        scene_tree.CurrentScene.AddChild(dialog);
        dialog.PopupCentered();
    }
}