using GenericBoson.Zozo;
using Godot;
using System.Collections.Generic;

namespace Zozo
{
    public partial class GameSocketManager : Node
    {
        public void RecvCharacterListAck(GameMessage gameMessage)
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
                        var characters = new Godot.Collections.Dictionary<long, string>();
                        for (var i = 0; i < ack.CharacterPairDatasLength; ++i)
                        {
                            var pairData = ack.CharacterPairDatas(i).GetValueOrDefault();
                            characters.Add(pairData.Id, pairData.Name);
                        }

                        GetTree().CurrentScene.Call("_AddCharacters", characters);
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
