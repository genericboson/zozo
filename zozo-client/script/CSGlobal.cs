using GenericBoson.Zozo;
using Godot;

public partial class CSGlobal : Node
{
    public static CSGlobal Instance { get; private set; }

    public CharacterInfo characterData = new();

    // FPS = 33.3...
    public const double SECOND_PER_FRAME = 0.03;

    public override void _Ready()
    {
        Instance = this;
    }
}