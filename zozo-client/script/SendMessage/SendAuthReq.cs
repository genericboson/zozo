using GenericBoson.Zozo;
using Godot;
using Google.FlatBuffers;
using System;
using System.Diagnostics;

namespace Zozo
{
    public partial class SocketManager : Node
    {
        public void SendAuthReq(string account, string password)
        {
            var fbb = new FlatBufferBuilder(1);
            var accountStr = fbb.CreateString(account);
            var passwordStr = fbb.CreateString(password);
            var authReq = AuthReq.CreateAuthReq(fbb, accountStr, passwordStr);
            var message = LobbyMessage.CreateLobbyMessage(fbb, LobbyPayload.AuthReq, authReq.Value);
            fbb.Finish(message.Value);

            var msg = fbb.SizedByteArray();

            #region for_debugging
            //{
            //    var byteStr = "";
            //    foreach (var b in msg)
            //    {
            //        byteStr += b.ToString() + " ";
            //    }

            //    GD.Print($"SendLogin: {byteStr}");
            //}
            #endregion

            var sizeBytes = BitConverter.GetBytes(msg.Length);
            Debug.Assert(sizeBytes.Length == 4);
            if (sizeBytes.Length != 4)
            {
                GD.PrintErr($"sizeBytes.Length != 4, length - {sizeBytes.Length}");
            }
            EnqueueSend(sizeBytes);
            EnqueueSend(msg);
        }
    }
}
