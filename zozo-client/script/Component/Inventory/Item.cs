using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Godot;

namespace Zozo
{
    [GlobalClass]
    public partial class Item : Resource
    {
        [Export] public string name = "";
        [Export] public Texture2D texture;
    }
}
