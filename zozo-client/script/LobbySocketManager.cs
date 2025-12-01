using GenericBoson.Zozo;
using Godot;

namespace Zozo
{
    public partial class LobbySocketManager : Node
    {
        public LobbySocketImpl m_lobbyImpl = new();

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
                        ReceiveAuthAck(lobbyMessage);
                        break;
                    case LobbyPayload.ServerListAck:
                        ReceiveServerListAck(lobbyMessage);
                        break;
                    default:
                        GD.PrintErr($"Unknown PayloadType: {lobbyMessage.PayloadType}");
                        break;
                }
            });
        }
    }
}
