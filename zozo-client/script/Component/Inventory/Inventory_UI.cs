using Godot;
using System;

namespace Zozo
{
    public partial class Inventory_UI : Control
    {
        public bool is_open = false;

        public override void _Ready()
        {
            base._Ready();
        }

        public override void _Process(double delta)
        {
            base._Process(delta);

            if (Input.IsActionJustPressed("i"))
            {
                if (is_open)
                {
                    Close();
                }
                else
                {
                    Open();
                }
            }
        }

        private void Close()
        {
            is_open = false;
            Visible = false;
        }

        private void Open()
        {
            is_open = true;
            Visible = true;
        }
    }
}
