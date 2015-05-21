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
    class Paddle : Sprite
    {
        public Rectangle boundingBox { get; set; }
        public Paddle(Texture2D newTex, Vector2 newSize, Vector2 newPosition, Vector2 newVelocity, Vector2 newScreenSize)
            : base(newTex, newSize, newPosition, newVelocity, newScreenSize)
        {
            boundingBox = newTex.Bounds;
        }

        public override void Move()
        {
            
            if (position.Y + velocity.Y < 0)
            {
                position = new Vector2(position.X, 0);
            }
            else if (position.Y + size.Y + velocity.Y> screenSize.Y)
            {
                position = new Vector2(position.X, screenSize.Y - spriteTex.Height);
            }
            
            position += velocity;
        }
        public override void Draw(SpriteBatch spriteBatch)
        {
            base.Draw(spriteBatch);
        }
        public bool Collides(Ball a)
        {
            if(this.position.X + this.size.X > a.position.X + a.radius + a.velocity.X &&
                this.position.Y + this.size.Y > a.position.Y + a.radius + a.velocity.Y &&
                this.position.X < a.position.X + a.radius + a.velocity.X &&
                this.position.Y < a.position.Y + a.radius + a.velocity.Y)
            {
                return true;
            }
            return false;
        }
    }
}

