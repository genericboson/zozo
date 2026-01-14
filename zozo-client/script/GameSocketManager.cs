using GenericBoson.Zozo;
using Godot;
using System.Collections.Generic;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
        private GameSocketImpl m_gameImpl = new();

        private string m_gameServerIp   = "";
        private string m_gameServerPort = "";

        static private PackedScene m_playerScene;
        static private Dictionary<int, CharacterBody2D> m_otherCharacters = new();

        public override void _Ready()
        {
            m_playerScene = ResourceLoader.Load<PackedScene>("res://scene/Player.tscn");
        }

        public override void _Process(double delta)
        {
            m_gameImpl.GetStream().Poll();

            if (string.IsNullOrEmpty(m_gameServerIp) || string.IsNullOrEmpty(m_gameServerPort))
            {
                m_gameServerIp   = CSGlobal.Instance.game_server_ip;
                m_gameServerPort = CSGlobal.Instance.game_server_port;

                GD.Print($"Game Server IP: {m_gameServerIp}, Port: {m_gameServerPort}");
            }

            // #todo : Delta check for time interpolation

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
                    case GamePayload.CharacterSelectAck:
                        ReceiveCharacterSelectAck(gameMessage);
                        break;
                    case GamePayload.CharacterPositionUpdateReq:
                        ReceiveCharacterPositionUpdateReq(gameMessage);
                        break;
                    default:
                        GD.PrintErr($"Unknown PayloadType: {gameMessage.PayloadType}");
                        break;
                }
            });
        }
    }
}
