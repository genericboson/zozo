using GenericBoson.Zozo;
using Godot;

namespace Zozo
{
    public partial class LobbySocketManager : Node
    {
        public void RecvServerListAck(LobbyMessage gameMessage)
        {
            var ack = gameMessage.PayloadAsServerListAck();
            ConsumeServerListAck(ack);
        }

        private void ConsumeServerListAck(ServerListAck ack)
        {
            switch (ack.ResultCode)
            {
                case ResultCode.Success:
                    using (var lobbyNode = GetNode<Node>("/root/Lobby"))
                    {
                        var servers = new Godot.Collections.Dictionary<int,string>();
                        for (var i = 0; i < ack.ServerInfosLength; ++i)
                        {
                            var serverInfo = ack.ServerInfos(i).GetValueOrDefault();
                            servers.Add(serverInfo.Id, serverInfo.Name);
                        }

                        lobbyNode.Call("_AddServers", servers);
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
