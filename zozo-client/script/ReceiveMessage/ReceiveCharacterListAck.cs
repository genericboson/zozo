using GenericBoson.Zozo;
using Godot;
using System.Collections.Generic;

namespace Zozo
{
    public partial class AbstractSocket : Node
    {
        public void ReceiveCharacterListAck(GameMessage gameMessage)
        {
            var ack = gameMessage.PayloadAsCharacterListAck();
            ConsumeCharacterListAck(ack);
        }

        private void ConsumeCharacterListAck(CharacterListAck ack)
        {
            switch (ack.ResultCode)
            {
                case ResultCode.Success:
                    using (var selectNode = GetNode<Node>("/root/CharacterSelect"))
                    {
                        var characters = new List<string>();
                        for (var i = 0; i < ack.CharacterNamesLength; ++i)
                        {
                            characters.Add(ack.CharacterNames(i));
                        }

                        selectNode.Call("_add_characters", characters.ToArray());
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
