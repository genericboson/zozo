using GenericBoson.Zozo;
using Godot;

public partial class CSGlobal : Node
{
    public static CSGlobal Instance { get; private set; }

    public CharacterInfo characterData = new();

    public override void _Ready()
    {
        Instance = this;
    }
}