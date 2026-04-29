using Godot;
using System;

namespace Zozo
{
    public partial class Inventory_UI : Control
    {
        public bool is_open = false;

        [Export] public Inventory inventory {  get; set; }
        public Godot.Collections.Array<Node> m_inventorySlots = new Godot.Collections.Array<Node>();

        public override void _Ready()
        {
            base._Ready();

            m_inventorySlots = GetNode<NinePatchRect>("InventoryWindow").GetNode<GridContainer>("SlotContainer").GetChildren();

            UpdateSlots();
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

        private void UpdateSlots()
        {
            for (int i = 0; i < m_inventorySlots.Count; i++)
            {
                if (m_inventorySlots[i] is ItemSlot_UI slot && i < inventory.items.Count)
                {
                    slot.Update(inventory.items[i]);
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
