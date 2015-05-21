using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using Microsoft.Kinect;

namespace Assignment2
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class Assignment2 : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        Texture2D background;
        Ball[] ballArray;
        Paddle leftPaddle;
        Paddle rightPaddle;
        SpriteFont hudText;
        SpriteFont timer;

        TimeSpan explodeTimer;
        TimeSpan startTimer;

        int bounces;
        public static int lives;
        int ballsDrawn;
        int timeToStart;

        enum GameState { notStarted, playing, paused, gameOver, starting };
        GameState state = GameState.notStarted;

        MouseState lms;
        KinectManager kM;

        SoundEffect bounce;
        SoundEffect explode;
        public Assignment2()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            // TODO: Add your initialization logic here
            ballArray = new Ball[3];
            bounces = 0;
            lives = 3;
            timeToStart = 3;
            ballsDrawn = 0;
            kM = new KinectManager();
            base.Initialize();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            // Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = new SpriteBatch(GraphicsDevice);
            Texture2D Ball = Content.Load<Texture2D> ("ball2");
            Texture2D paddle = Content.Load<Texture2D>("Paddle");
            background = Content.Load<Texture2D>("StarBackground");
            Random rand =  new Random();
            hudText = Content.Load<SpriteFont>("HUD");
            timer = Content.Load<SpriteFont>("Timerfont");
            bounce = Content.Load<SoundEffect>("Bounce");
            explode = Content.Load<SoundEffect>("explode");
            for (int i = 0; i < ballArray.Length; i++)
            {
                ballArray[i] = new Ball(Ball,
                            new Vector2(32, 32),
                            new Vector2(graphics.PreferredBackBufferWidth / 2, graphics.PreferredBackBufferHeight / 2),
                            new Vector2(0, 0),
                            new Vector2(graphics.PreferredBackBufferWidth, graphics.PreferredBackBufferHeight));
            }

            leftPaddle = new Paddle(paddle,
                                    new Vector2(paddle.Width, paddle.Height),
                                    new Vector2(32, 32),
                                    new Vector2(0,0f),
                                    new Vector2(graphics.PreferredBackBufferWidth, graphics.PreferredBackBufferHeight));
            rightPaddle = new Paddle(paddle,
                                    new Vector2(paddle.Width, paddle.Height),
                                    new Vector2(graphics.PreferredBackBufferWidth - 32 - paddle.Width, 32),
                                    new Vector2(0, 0f),
                                    new Vector2(graphics.PreferredBackBufferWidth, graphics.PreferredBackBufferHeight));
                                    
            // TODO: use this.Content to load your game content here
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            explodeTimer += gameTime.ElapsedGameTime;
            startTimer += gameTime.ElapsedGameTime;
            if (Keyboard.GetState().IsKeyDown(Keys.Escape))
                this.Exit();
            switch(state)
            {
                case GameState.playing:
                    
                    //Scaling method from http://stackoverflow.com/questions/13495402/how-to-do-joint-tracking-in-kinect-with-a-scaled-image
                    leftPaddle.position = new Vector2(leftPaddle.position.X, (leftPaddle.spriteTex.Height/2) + (((-1f * (kM.leftHand.Position.Y/(graphics.PreferredBackBufferHeight/480))) + 0.5f) * (graphics.PreferredBackBufferHeight)));
                    rightPaddle.position = new Vector2(rightPaddle.position.X, (rightPaddle.spriteTex.Height / 2) + (((-1f * (kM.rightHand.Position.Y/(graphics.PreferredBackBufferHeight/480)) + 0.5f) * (graphics.PreferredBackBufferHeight))));
                   
                    if (bounces > 30)
                    {
                        ballsDrawn = 3;
                    }
                    else if (bounces > 20)
                    {
                        ballsDrawn = 2;
                    }
                    else
                    {
                        ballsDrawn = 1;
                    }
                    int ballsOnScreen = 0;
                    foreach (Ball b in ballArray)
                    {
                        if (b.drawn && (b.explodingLeft || b.explodingRight))
                        {
                            if (explodeTimer > TimeSpan.FromMilliseconds(100))
                            {
                                b.currentFrame++;
                            }
                        }
                        if (b.drawn)
                            ballsOnScreen++;
                    }
                    if (ballsOnScreen == 0 || lives == 0)
                        state = GameState.gameOver;
                    CheckCollisions();
                    for (int i = 0; i < ballsDrawn; i++)
                    {
                        ballArray[i].Move();
                    }
                    leftPaddle.Move();
                    rightPaddle.Move();
                break;
                case GameState.notStarted:
                if (Mouse.GetState().LeftButton == ButtonState.Released && lms.LeftButton == ButtonState.Pressed)
                {
                    state = GameState.starting;
                    lms = new MouseState();
                    break;
                }
                lms = Mouse.GetState();
                break;
                case GameState.paused:
                break;
                case GameState.gameOver:
                if (Mouse.GetState().LeftButton == ButtonState.Released && lms.LeftButton == ButtonState.Pressed)
                {
                    state = GameState.starting;
                    lms = new MouseState();
                    Initialize();
                    break;
                }
                lms = Mouse.GetState();
                
                break;
                case GameState.starting:
                startTimer += gameTime.ElapsedGameTime;
                if (startTimer > TimeSpan.FromSeconds(1))
                {
                    startTimer = TimeSpan.Zero;
                    timeToStart--;
                }
                if (timeToStart == 0)
                {
                    state = GameState.playing;
                    startTimer = TimeSpan.Zero;
                }
                break;
            }
            
            // TODO: Add your update logic here

            base.Update(gameTime);
        }

        private void CheckCollisions()
        {
            for (int i = 0; i < ballsDrawn; i++)
            {
                if (leftPaddle.Collides(ballArray[i]))
                {
                    ballArray[i].velocity = new Vector2(-ballArray[i].velocity.X, ballArray[i].velocity.Y);
                    bounces++;
                    if (bounce != null)
                    {
                        bounce.Play();
                    }
                }
                else if (ballArray[i].position.X < leftPaddle.position.X)
                {
                    ballArray[i].explodingLeft = true;
                    explode.Play();
                }
                if (rightPaddle.Collides(ballArray[i]))
                {
                    ballArray[i].velocity = new Vector2(-ballArray[i].velocity.X, ballArray[i].velocity.Y);
                    bounces++;
                    if (bounce != null)
                    {
                        bounce.Play();
                    }
                    else
                    {
                        bounce.Play();
                    }
                }
                else if (ballArray[i].position.X > rightPaddle.position.X)
                {
                    ballArray[i].explodingRight = true;
                    explode.Play();
                }
                if (ballArray[i].velocity == Vector2.Zero)
                {
                    ballArray[i].velocity = new Vector2(-5f, -2.5f);
                }
                    
                //ballArray[i].Move();
            }
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);
            spriteBatch.Begin(SpriteSortMode.Immediate, BlendState.NonPremultiplied);
            spriteBatch.Draw(background, GraphicsDevice.PresentationParameters.Bounds, Color.White);
            switch(state)
            {
                case GameState.playing:
                Color ball1Colour = new Color(255, 255, 255, (byte)MathHelper.Clamp((float)(255 / 20) * bounces, 0, 255));
                Color ball2Colour = new Color(255, 255, 255, (byte)MathHelper.Clamp((float)(255 / 30) * bounces, 0, 255));
                Color ball3Colour = new Color(255, 255, 255, (byte)MathHelper.Clamp((float)(255 / 40) * bounces, 0, 255));
                Color ball4Colour = new Color(255, 255, 255, (byte)MathHelper.Clamp((float)(255 / 50) * bounces, 0, 255));
#region drawCalls
                spriteBatch.DrawString(hudText,"Score: " + bounces.ToString(), new Vector2(0, 0), Color.LightBlue);
                spriteBatch.DrawString(hudText, "Lives: " + lives.ToString(), new Vector2((graphics.PreferredBackBufferWidth/2) - (hudText.MeasureString("Lives: ").X/2), 0), Color.LightBlue);
                if (ballsDrawn == 3)
                {
                    if (!(ballArray[2].explodingLeft || ballArray[2].explodingRight))
                    if (!ballArray[2].drawn)
                        ballArray[2].drawn = true;
                    ballArray[0].Draw(spriteBatch);
                    ballArray[1].Draw(spriteBatch);
                    ballArray[2].Draw(spriteBatch);
                }
                else if (ballsDrawn == 2)
                {
                    if (!(ballArray[1].explodingLeft || ballArray[1].explodingRight))
                    if (!ballArray[1].drawn)
                        ballArray[1].drawn = true;
                    ballArray[0].Draw(spriteBatch);
                    ballArray[1].Draw(spriteBatch);
                    spriteBatch.Draw(ballArray[2].spriteTex, ballArray[2].position, new Rectangle(0, 0, 32, 32), ball2Colour, 0.0f, Vector2.Zero, 1, SpriteEffects.None, 0.0f);
                }
                else
                {
                    if(!(ballArray[0].explodingLeft || ballArray[0].explodingRight))
                    if (!ballArray[0].drawn)
                        ballArray[0].drawn = true;
                    ballArray[0].Draw(spriteBatch);
                    spriteBatch.Draw(ballArray[1].spriteTex, ballArray[1].position, new Rectangle(0, 0, 32, 32), ball1Colour, 0.0f, Vector2.Zero, 1, SpriteEffects.None, 0.0f);
                }
                leftPaddle.Draw(spriteBatch);
                rightPaddle.Draw(spriteBatch);
#endregion
                break;
                case GameState.notStarted:
                spriteBatch.DrawString(hudText, "Click Anywhere To Start", new Vector2((graphics.PreferredBackBufferWidth / 2) - (hudText.MeasureString("Click Anywhere To Start").X / 2), (graphics.PreferredBackBufferHeight / 2) - (hudText.MeasureString("Click To Start").Y / 2)), Color.White);
                break;
                case GameState.paused:
                break;
                case GameState.gameOver:
                    spriteBatch.DrawString(hudText, "Game over", new Vector2((graphics.PreferredBackBufferWidth / 2) - (hudText.MeasureString("Game over").X/2), (graphics.PreferredBackBufferHeight / 2) - (hudText.MeasureString("Game over").Y/2)), Color.White);
                    spriteBatch.DrawString(hudText, "Click anywhere to restart", new Vector2((graphics.PreferredBackBufferWidth / 2) - (hudText.MeasureString("Click anywhere to restart").X / 2), ((graphics.PreferredBackBufferHeight / 2) - 30) - (hudText.MeasureString("Click to restart").Y / 2)), Color.White);
                break;
                case GameState.starting:
                spriteBatch.DrawString(timer, timeToStart.ToString(), new Vector2((graphics.PreferredBackBufferWidth / 2) - (hudText.MeasureString(timeToStart.ToString()).X / 2), ((graphics.PreferredBackBufferHeight / 2) - 30) - (hudText.MeasureString(timeToStart.ToString()).Y / 2)), Color.Red);
                break;
            }
            spriteBatch.End();
            // TODO: Add your drawing code here

            base.Draw(gameTime);
        }
    }
}
