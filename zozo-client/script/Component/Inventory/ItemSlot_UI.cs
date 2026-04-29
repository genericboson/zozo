using Godot;
using System;

namespace Zozo
{
    public partial class ItemSlot_UI : Panel
    {
        public Sprite2D m_itemDisplay;

        public override void _Ready()
        {
            base._Ready();
            m_itemDisplay = GetNode<Sprite2D>("ItemDisplay");
        }

        public void Update(Item item)
        {
            if (item == null)
            {
                m_itemDisplay.Visible = false;
            }
            else
            {
                m_itemDisplay.Visible = true;
                m_itemDisplay.Texture = item.texture;
            }
        }
    }
}
