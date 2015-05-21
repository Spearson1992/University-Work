using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace Assignment2
{
    class Sprite
    {
        public Texture2D spriteTex { get; set; }
        public Vector2 size { get; set; }
        public Vector2 position { get; set; }
        public Vector2 velocity { get; set; }
        public Vector2 screenSize { get; set; }

        public Sprite(Texture2D spriteTex, Vector2 spriteSize, Vector2 spritePosition, Vector2 spriteVelocity, Vector2 spriteScreenSize)
        {
            this.spriteTex = spriteTex;
            size = spriteSize;
            position = spritePosition;
            velocity = spriteVelocity;
            screenSize = spriteScreenSize;
        }

        public virtual void Move()
        {
            throw new NotImplementedException();
        }

        public virtual void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(spriteTex, position, null, Color.White, 0.0f, Vector2.Zero, 1, SpriteEffects.None, 0.0f);
        }
    }
}
