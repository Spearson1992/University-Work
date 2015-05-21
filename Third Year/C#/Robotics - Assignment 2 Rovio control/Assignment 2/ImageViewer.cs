using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Workshop_2___Forms
{
    public partial class ImageViewer : Form
    {
        Rovio.Predator robot;
        public ImageViewer()
        {
            InitializeComponent();
        }
        private System.Threading.Thread robot_thread;

        private void ImageViewer_Load(object sender, EventArgs e)
        {
            robot = new Rovio.Predator("http://10.82.0.31/", "user", "password");

            
            this.Text = "Objects";
            this.Show();
            robot.ObjectImage += this.UpdateImage;
            
            //create and start the robot thread
            robot_thread = new System.Threading.Thread(new System.Threading.ThreadStart(robot.RunRobot));
            robot_thread.Start();
        }

        private void ImageViewer_Resize(object sender, EventArgs e)
        {
        }
        private void ImageViewer_FormClosed(object sender, FormClosedEventArgs e)
        {
            robot.terminateRobotThread = true;
            robot.terminateImageThread = true;
        }
        private delegate void UpdateImageValue(Image image);

        //update the picture box content
        public void UpdateImage(Image image, Image image2)
        {
            if (!this.IsDisposed)
            {
                pictureBox1.Image = image;
                pictureBox2.Image = image2;
                if (this.InvokeRequired)
                    this.Invoke(new MethodInvoker(delegate { UpdateImage(image, image2); }));
            }
        }

        //parse keyboard input
        private void ImageViewer_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.D1:
                    robot.imageSlice = Rovio.FilterColour.Red;
                    break;
                case Keys.D2:
                    robot.imageSlice = Rovio.FilterColour.Blue;
                    break;
                case Keys.D3:
                    robot.imageSlice = Rovio.FilterColour.Green;
                    break;
                case Keys.D4:
                    robot.imageSlice = Rovio.FilterColour.Yellow;
                    break;
                default:
                    break;
            }
        }
    }
}
