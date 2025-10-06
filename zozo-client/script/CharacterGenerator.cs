using Godot;
using System;

public partial class CharacterGenerator : Node
{
    public StreamPeerTcp stream = new();

    public override void _Ready()
    {
        // Called every time the node is added to the scene.
        // Initialization here.
        GD.Print( "Hello from C# to Godot :)" );

        
        stream.SetNoDelay(true);
        GD.Print( $"Connection attempt : {stream.ConnectToHost("127.0.0.1", 8001)}" );
    }

    public override void _Process(double delta)
    {
        // Called every frame. Delta is time since the last frame.
        // Update game logic here.

        stream.Poll();
        var status = stream.GetStatus();
        if ( status != StreamPeerTcp.Status.Connected )
        {
            GD.Print( $"Not connected. Status - {status}" );
            return;
        }

        stream.PutData( System.Text.Encoding.UTF8.GetBytes("Hello from C# to Godot :)") );

        if ( stream.GetAvailableBytes() > 0 )
        {
            var received = stream.GetData( stream.GetAvailableBytes() );
            GD.Print( received.ToString() );
        }
    }
}
