using GenericBoson.Zozo;
using Godot;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
        private GameSocketImpl m_gameImpl = new();

        private string m_gameServerIp   = "";
        private string m_gameServerPort = "";

        public override void _Process(double delta)
        {
            m_gameImpl.GetStream().Poll();

            if (string.IsNullOrEmpty(m_gameServerIp) || string.IsNullOrEmpty(m_gameServerPort))
            {
                var globalNode = GetNode<Node>("/root/Global");
                if (globalNode == null)
                {
                    GD.PrintErr("Global node not found");
                    return;
                }

                m_gameServerIp = globalNode.Get("game_server_ip").AsString();
                m_gameServerPort = globalNode.Get("game_server_port").AsString();

                GD.Print($"Game Server IP: {m_gameServerIp}, Port: {m_gameServerPort}");
            }

            if (!m_gameImpl.CheckConnect(m_gameServerIp, m_gameServerPort))
                return;

            m_gameImpl.SendAllMessage();
            m_gameImpl.ReceiveMessage(bb =>
            {
                var gameMessage = GameMessage.GetRootAsGameMessage(bb);

                switch (gameMessage.PayloadType)
                {
                    case GamePayload.CharacterListAck:
                        ReceiveCharacterListAck(gameMessage);
                        break;
                    default:
                        GD.PrintErr($"Unknown PayloadType: {gameMessage.PayloadType}");
                        break;
                }
            });
        }
    }
}
