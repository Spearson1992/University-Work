using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using AForge.Imaging;
using System.Diagnostics;
using System.Threading;

namespace Rovio
{
    class Predator : RobotBase
    {
        public enum robotState
        {
            Searching,
            Chasing,
            LostBlock,
            SearchingBehindObstacle,
            AvoidBox
        }

        Rectangle redBlockDetection = new Rectangle();
        Rectangle lastRedBlockDetection = new Rectangle();
        Rectangle greenBoxDetection = new Rectangle();
        Rectangle lastGreenBoxDetection = new Rectangle();
        private int searchSpins;

        public Predator(string address, string user, string password)
            : base(address, user, password)
        {
            state = robotState.Searching;
            redBlockDistance = 0;
            greenBlockDistance = 0;
            searchSpins = 0;
        }

        private robotState state;

        public override void  RunRobot()
        {
            //Initial code that was provided
            //check if we can receive responses from the robot
            if (imageUpdated)
            {
                try { API.Movement.GetLibNSVersion(); } // a dummy request
                catch (Exception)
                {
                    //simple way of getting feedback in the form mode
                    System.Windows.Forms.MessageBox.Show("Could not connect to the robot");
                    return;
                }
            }

            //endless loop
            while (!terminateRobotThread)
            {
                //poll camera input
                imageUpdated = false;
                    image = Camera.Image;
                    temp = (Bitmap)image.Clone();
                imageUpdated = true;
                
                if (!imageProcessing.swappingBuffers && imageUpdated && !updateCamera)
                {
                    
                    int width = image.Width;
                    redBlockDetection = imageProcessing.GetObjectRectangle(FilterColour.Red);
                    greenBoxDetection = imageProcessing.GetObjectRectangle(FilterColour.Green);

                    //store last know loaction of obstacle and red block for use in navigating
                    if (redBlockDetection != Rectangle.Empty)
                    {
                        lastRedBlockDetection = redBlockDetection;
                        redBlockDistance = (float)ObjectSizes.redBlockwidth / redBlockDetection.Width;
                    }
                    if (greenBoxDetection != Rectangle.Empty)
                    {
                        greenBlockDistance = (float)ObjectSizes.greenBoxwidth / greenBoxDetection.Width;
                        lastGreenBoxDetection = greenBoxDetection;
                    }

                    //state machine
                    switch (state)
                    {
                        case robotState.Searching:
                            Search();
                            Console.WriteLine("Searching");
                            break;


                        case robotState.Chasing:
                            ChaseBlock(width);
                            Console.WriteLine("Chasing");
                        break;

                        case robotState.LostBlock:
                            RelocateBlock(width);
                            Console.WriteLine("Relocating block");
                        break;

                        case robotState.SearchingBehindObstacle:
                        SearchAroundBlock(width);
                        Console.WriteLine("Searching around block");

                        break;
                        case robotState.AvoidBox:
                        AvoidBox(width);
                        Console.WriteLine("avoiding box");

                        break;
                    }

                    updateCamera = true; 
                    
                      
                }
            }
        }

        private void AvoidBox(int width)
        {
            coloursToProcess = new FilterColour[] { FilterColour.Red, FilterColour.Green };
            Rectangle obstacle = imageProcessing.GetObjectRectangle(FilterColour.Green);

            //if redblock has been located strafe away from the obstacle befor swittching states to chasing
            if (redBlockDetection != Rectangle.Empty)
            {
                if (greenBoxDetection.Location.X + (greenBoxDetection.Width / 2) > (width / 2))
                {
                    Drive.StraightLeft(1);
                }
                else if (greenBoxDetection.Location.X + (greenBoxDetection.Width / 2) < (width / 2))
                {
                    Drive.StraightRight(1);
                }
                state = robotState.Chasing;
            }
                //if obstacle is in the way and no red block is seen move in the opposite direction 
                //to its last known direction of travel
            else if (obstacle != Rectangle.Empty &&
                ((obstacle.Location.X + (obstacle.Width / 2)) > 50 &&
                (obstacle.Location.X + (obstacle.Width / 2)) < width - 50)
                || IRSensor.Detection == true)
            {
                if (lastRedBlockDetection.Location.X + (lastRedBlockDetection.Width / 2) >= (width / 2))
                {
                    Drive.StraightLeft(5);
                }
                else if (lastRedBlockDetection.Location.X + (lastRedBlockDetection.Width / 2) <= (width / 2))
                {
                    Drive.StraightRight(5);
                }
            }
                //if still not found go back to searching
            else
            {
                state = robotState.Searching;
            }
        }

        private void SearchAroundBlock(int width)
        {
            coloursToProcess = new FilterColour[] { FilterColour.Red, FilterColour.Green };
            if (greenBoxDetection == Rectangle.Empty && lastGreenBoxDetection != Rectangle.Empty && redBlockDetection == Rectangle.Empty) //if red and green blocks not seen and green block has been detected before spin towards and centre it in view 
            {
                CentreGreenBlock(width);
            }
            else if (greenBoxDetection != Rectangle.Empty && redBlockDetection == Rectangle.Empty) //If greenblock detected and no red block detected
            {
                //if the green block is within ir sensor detection range or roughly 0.5 meteres away
                //strafe right
                if (greenBlockDistance < 0.5 || IRSensor.Detection) // avoid box if close
                {
                    Drive.StraightRight(1);
                }
                else //close distance if far
                {
                    DriveStraight(6, 1);
                }
            }
            else if (redBlockDetection != Rectangle.Empty)//if red block located
            {
                state = robotState.Chasing;
            }
            else //if no obstacle and no red block
            {
                state = robotState.Searching;
            }
        }

        private void CentreGreenBlock(int width)
        {
            float greenBlockLocationX = lastGreenBoxDetection.Location.X + (lastGreenBoxDetection.Width / 2);
            //if the block is within 200 pixels of sceen centre don't bother chasing it
                double tempDriveVelocity = ((greenBlockLocationX - (width / 2)) * 0.001f);
                if (tempDriveVelocity == 0.0f) //prevent robot getting stuck
                    tempDriveVelocity = 1.0f;
                if (tempDriveVelocity > 0)
                {
                    int driveVelocity = (int)Math.Ceiling(tempDriveVelocity);
                    Spin(driveVelocity, 1);
                }
                else
                {
                    int driveVelocity = (int)Math.Floor(tempDriveVelocity);
                    Spin(driveVelocity, 1);
                }
            
        }

        private void RelocateBlock(int width)
        {
            coloursToProcess = new FilterColour[] { FilterColour.Red, FilterColour.Green };
            if (redBlockDetection == Rectangle.Empty) //if robot can't see red block
            {
                
                //Rotate in the direction of the red block
                    float xLocation = lastRedBlockDetection.Location.X + (lastRedBlockDetection.Width / 2);
                    double tempDriveVelocity = ((xLocation - (width / 2)) * 0.003f);
                    if (tempDriveVelocity > 0)
                    {
                        int driveVelocity = (int)Math.Ceiling(tempDriveVelocity);
                        Spin(driveVelocity, 1);
                    }
                    else
                    {
                        int driveVelocity = (int)Math.Floor(tempDriveVelocity);
                        Spin(driveVelocity, 1);
                    }

                    //if obstacle in the way  got to avoid box
                    if (imageProcessing.GetObjectRectangle(FilterColour.Green) != Rectangle.Empty)
                    {
                        state = robotState.AvoidBox;
                        return;
                    }
                    
                    
            }
            else //if robot can see red block
            {
                Drive.Stop();
                state = robotState.Chasing;
            }
        }

        //Heads towards red block whilst keeping it roughly centred in robots view
        private void ChaseBlock(int width)
        {
            coloursToProcess = new FilterColour[] { FilterColour.Red, FilterColour.Green };
            if (redBlockDetection != Rectangle.Empty) //If red block can be seen
            {
                    
                float redBlockLocationX = redBlockDetection.Location.X + (redBlockDetection.Width / 2);
                //if the block is within 200 pixels of sceen centre don't bother chasing it
                if (Math.Abs(redBlockLocationX) < 50 || Math.Abs(redBlockLocationX) > 250)
                {
                    double tempDriveVelocity = ((redBlockLocationX - (width / 2)) * 0.003f); //Calculate drive velocity
                    if (tempDriveVelocity > 0)
                    {
                        int driveVelocity = (int)Math.Ceiling(tempDriveVelocity); //Prevent values lower than 0.5 being rounded to 0
                        Spin(driveVelocity, 1);
                    }
                    else
                    {
                        int driveVelocity = (int)Math.Floor(tempDriveVelocity); //Prevent values greater than -0.5 being rounded to 0
                        Spin(driveVelocity, 1);
                    }
                }
                else if (redBlockDistance > 0.6) //Close distance to red block
                {
                    DriveStraight(10, 1);
                }
                else //stop if red block is close
                {
                    Drive.Stop();
                }
                
            }
            else//If block not in view
            {
                Drive.Stop();
                state = robotState.LostBlock;
            }
        }

        //spin around searching for the block
        private void Search()
        {
            coloursToProcess = new FilterColour[] { FilterColour.Red, FilterColour.Green };
            if (redBlockDetection == Rectangle.Empty) //If red lock isn't within field of view
            {
                Spin(3, 1);
                searchSpins++;
                Thread.Sleep(1);
                if (searchSpins == 40)//Just over 1 turn
                {
                    state = robotState.SearchingBehindObstacle;
                    searchSpins = 0;
                }
                

            }
            else //If red block has been found
            {
                Drive.Stop();
                state = robotState.Chasing;
            }
        }






    }
        
}
