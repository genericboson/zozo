using GenericBoson.Zozo;
using Godot;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
        private GameSocketImpl m_gameImpl = new();

        public override void _Process(double delta)
        {
            m_gameImpl.GetStream().Poll();

            if (!m_gameImpl.CheckConnect())
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
