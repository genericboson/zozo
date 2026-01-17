using GenericBoson.Zozo;
using Godot;

namespace Zozo
{
    public partial class LobbySocketManager : Node
    {
        public LobbySocketImpl m_lobbyImpl = new();
        public Node m_globalNode;

        public override void _Ready()
        {
            m_globalNode = GetNode<Node>("/root/GDGlobal");
            if (m_globalNode == null)
            {
                GD.PrintErr("Global node is null");
            }
        }

        public override void _Process(double delta)
        {
            m_lobbyImpl.GetStream().Poll();

            if (!m_lobbyImpl.CheckConnect("127.0.0.1", "8002"))
                return;

            m_lobbyImpl.SendAllMessage();
            m_lobbyImpl.ReceiveMessage(bb => {
                var lobbyMessage = LobbyMessage.GetRootAsLobbyMessage(bb);

                switch (lobbyMessage.PayloadType)
                {
                    case LobbyPayload.AuthAck:
                        RecvAuthAck(lobbyMessage);
                        break;
                    case LobbyPayload.ServerListAck:
                        RecvServerListAck(lobbyMessage);
                        break;
                    default:
                        GD.PrintErr($"Unknown PayloadType: {lobbyMessage.PayloadType}");
                        break;
                }
            });
        }
    }
}
