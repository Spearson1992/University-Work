using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Diagnostics;
using AForge.Imaging;
using AForge.Imaging.Filters;

namespace Rovio
{
    

    abstract class RobotBase : Robot
    {
        public delegate void ImageReady(System.Drawing.Image image, System.Drawing.Image image2);
        public event ImageReady ObjectImage;

        public ImageProcessor imageProcessing;
        public Bitmap image {get;  set;}
        protected Bitmap temp { get; set; }
        
       //camera update thread object
        private System.Threading.Thread cameraUpdateThread;
        
        
        //Image processing thread termination flag
        //Should only be true when thread should be terminated
        public volatile bool terminateImageThread;
        public volatile bool terminateRobotThread;
        public volatile bool updateCamera;
        protected bool imageUpdated = false;

        protected volatile FilterColour[] coloursToProcess;
        public FilterColour imageSlice; //controls which image to display in the second image box in the form

        //distance to red block roughly
        public float redBlockDistance;
        //distance to green block roughly
        public float greenBlockDistance;

       

        public RobotBase(string address, string user, string password)
            : base(address, user, password)
        {
            terminateImageThread = false;
            terminateRobotThread = false;
            updateCamera = true;
            imageProcessing = new ImageProcessor();
            cameraUpdateThread = new System.Threading.Thread(new System.Threading.ThreadStart(UpdateCamera));
            cameraUpdateThread.Start();
            coloursToProcess = new FilterColour[0];
            Camera.Resolution = Rovio.API.Camera.ImageResolution.CGA;
            imageSlice = FilterColour.Green;
        }

        public abstract void RunRobot();

        
        /// <summary>
        /// Drives in straight line for a specified number of repetitions at a specified speed
        /// values are inverted 10 is the fastest speed  is the slowest
        /// </summary>
        /// <param name="velocity">Velocity of robot 1-10</param>
        /// <param name="repetitions">Number of times to execute the command</param>
        public void DriveStraight(int velocity, int repetitions)
        {
            if (velocity != 0)
            {
                if (velocity < -10)
                {
                    velocity = -10;
                }
                else if (velocity > 10)
                {
                    velocity = 10;
                }
                if (velocity < 0 && velocity >= -10)
                {
                    for (int i = 0; i < repetitions; i++)
                    {
                        Drive.Backward(11 - (-velocity));
                    }
                }
                else if (velocity <= 10)
                {
                    for (int i = 0; i < repetitions; i++)
                    {
                        //if (IRSensor.Detection)
                        //    return;
                        Drive.Forward(11 - velocity);
                    }
                }
                else
                    Console.WriteLine("Error: Velocity must be between -10 and 10");
            }
        }
        
        /// <summary>
        /// spins around a specified number of repetitions at a specified speed
        /// values are inverted 10 is the fastest speed  is the slowest
        /// </summary>
        /// <param name="velocity">Velocity of robot 1-10</param>
        /// <param name="repetitions">Number of times to execute the command</param>
        public void Spin(int velocity, int repetitions)
        {
            if (velocity != 0)
            {
                if (velocity < -10)
                {
                    velocity = -10;
                }
                else if (velocity > 10)
                {
                    velocity = 10;
                }

                if (velocity < 0 && velocity >= -10)
                {
                    for (int i = 0; i < repetitions; i++)
                    {
                        Drive.RotateLeft(11 - (-velocity));
                    }
                }
                else if (velocity <= 10)
                {
                    for (int i = 0; i < repetitions; i++)
                    {
                        Drive.RotateRight(11 - velocity);
                    }
                }
                else
                    Console.WriteLine("Error: Velocity must be between -10 and 10");
            }
        }

        /// <summary>
        /// camera update function
        /// </summary>

        private void UpdateCamera()
        {
            Stopwatch watch = new Stopwatch();
            while (!terminateImageThread)
            {

                if (updateCamera && imageUpdated)
                {
                    
                    watch.Start();
                    if (coloursToProcess.Length > 0)
                    {
                        imageProcessing.ProcessImages(temp, coloursToProcess);
                        foreach(FilterColour colour in coloursToProcess)
                        {
                            Rectangle rect = imageProcessing.GetObjectRectangle(colour);
                            Graphics g = Graphics.FromImage(temp);
                            g.DrawRectangle(new Pen(Color.Tomato), rect);
#if DEBUG
                            if(colour == FilterColour.Red)
                                g.DrawString(redBlockDistance.ToString("G2"), new Font(FontFamily.GenericSansSerif, 6.0f, FontStyle.Regular),new SolidBrush(Color.Lime), new Point(rect.Location.X + (rect.Width / 2),rect.Location.Y + (rect.Height / 2)));
#endif
                        }

                        ObjectImage(temp, imageProcessing.GetColourSlicedImage(imageSlice));

                        
                    }
                    
                    watch.Stop();
#if DEBUG
                    Console.WriteLine("Image processing execution time = " + watch.Elapsed.Milliseconds);
#endif
                    watch.Reset();
                    updateCamera = false;
                    
                }
            }
        }
    }
}
