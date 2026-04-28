using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Godot;

namespace Zozo
{
    [GlobalClass]
    public partial class Inventory : Resource
    {
        [Export] public Godot.Collections.Array<Item> items = new Godot.Collections.Array<Item>();
    }
}
