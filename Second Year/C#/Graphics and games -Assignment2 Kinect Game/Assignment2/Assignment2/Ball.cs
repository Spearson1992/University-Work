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
    class Ball : Sprite
    {
        public float radius;
        public bool drawn;
        public bool explodingLeft;
        public bool explodingRight;
        public int currentFrame;
        public bool takeLife;

        public Ball(Texture2D newTex, Vector2 newSize, Vector2 newPosition, Vector2 newVelocity, Vector2 newScreenSize)
            : base(newTex, newSize, newPosition, newVelocity, newScreenSize)
        {
            radius = 16;
            explodingRight = false;
            explodingLeft = false;
            currentFrame = 0;
            drawn = false;
            takeLife = true;
        }
        public override void Move()
        {
            if (drawn)
            {
                if (position.X + size.X > screenSize.X)
                {
                    if (takeLife)
                    {
                        if (Assignment2.lives < 0)
                            Assignment2.lives = 0;
                        else
                            Assignment2.lives--;
                        drawn = false;
                        takeLife = false;
                    }
                }
                if (position.Y + size.Y + velocity.Y > screenSize.Y)
                    velocity = new Vector2(velocity.X, -velocity.Y);
                if (position.X < 0)
                {
                    if (takeLife)
                    {

                        if (Assignment2.lives < 0)
                            Assignment2.lives = 0;
                        else
                            Assignment2.lives--;
                        drawn = false;
                        takeLife = false;
                    }
                }
                if (position.Y + velocity.Y < 0)
                    velocity = new Vector2(velocity.X, -velocity.Y);

                position += velocity;
            }

        }
        public override void Draw(SpriteBatch spriteBatch)
        {
            if (drawn && (explodingLeft || explodingRight))
            {
                spriteBatch.Draw(spriteTex, position, new Rectangle(32*currentFrame, 0, 32, 32), Color.White, 0.0f, Vector2.Zero, 1, SpriteEffects.None, 0.0f);
            }
            else if (drawn)
                spriteBatch.Draw(spriteTex, position, new Rectangle(0,0,32,32), Color.White, 0.0f, Vector2.Zero, 1, SpriteEffects.None, 0.0f);
        }
        public bool Collides(Paddle a)
        {
            if (this.position.X - this.radius < a.position.X &&
                this.position.Y > a.position.Y &&
                this.position.Y < a.position.Y + a.size.Y)
            {
                return true;
            }

            return false;
        }
        public bool Collides(Ball a)
        {
            float dist = Vector2.Distance(this.position, a.position);
            float radius = this.radius + a.radius;
            if (dist < radius)
                return true;
            return false;
        }
    }
}
