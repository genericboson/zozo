using GenericBoson.Zozo;
using Godot;
using System.Collections.Generic;

namespace Zozo
{
    public partial class AbstractSocket : Node
    {
        public void ReceiveServerListAck(LobbyMessage gameMessage)
        {
            var ack = gameMessage.PayloadAsServerListAck();
            ConsumeServerListAck(ack);
        }

        private void ConsumeServerListAck(ServerListAck ack)
        {
            switch (ack.ResultCode)
            {
                case ResultCode.Success:
                    using (var selectNode = GetNode<Node>("/root/Lobby"))
                    {
                        var servers = new List<string>();
                        for (var i = 0; i < ack.ServerInfosLength; ++i)
                        {
                            servers.Add(ack.ServerInfos(i).GetValueOrDefault().Name);
                        }

                        selectNode.Call("_add_servers", servers.ToArray());
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
