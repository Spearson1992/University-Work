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
using Microsoft.Kinect;

namespace Assignment2
{
    class KinectManager
    {
        KinectSensor kinect;
        public Joint leftHand;
        public Joint rightHand;

        bool kincectReady;

        public KinectManager()
        {
            if(!findKinect())
                return;
            kincectReady = InitialiseKinect();
        }

        public void kinectSkeletonFrameReady(object sender, SkeletonFrameReadyEventArgs e)
        {
            using (SkeletonFrame skelFrame = e.OpenSkeletonFrame())
            {
                if (skelFrame != null)
                {
                    Skeleton[] data = new Skeleton[skelFrame.SkeletonArrayLength];
                    skelFrame.CopySkeletonDataTo(data);
                    Skeleton player = (from sk in data where sk.TrackingState == SkeletonTrackingState.Tracked select sk).FirstOrDefault();
                    if (player != null)
                    {
                        rightHand = player.Joints[JointType.HandRight];
                        leftHand = player.Joints[JointType.HandLeft];
                    }
                }
                
            }
        }
        public bool InitialiseKinect()
        {
            kinect.SkeletonStream.Enable(new TransformSmoothParameters()
            {
                Smoothing = 0.5f,
                Correction = 0.5f,
                Prediction = 0.5f,
                JitterRadius = 0.05f,
                MaxDeviationRadius = 0.04f
            });
            kinect.SkeletonFrameReady += new EventHandler<SkeletonFrameReadyEventArgs>(kinectSkeletonFrameReady);
            try
            {
                kinect.Start();
            }
            catch
            {
                return false;
            }
            return true;
        }
        private bool findKinect()
        {
            foreach (KinectSensor sensor in KinectSensor.KinectSensors)
            {
                if (sensor.Status == KinectStatus.Connected)
                {
                    kinect = sensor;
                }
            }
            if (kinect != null)
            {
                return true;
            }
            return false;
        }
    }
}
