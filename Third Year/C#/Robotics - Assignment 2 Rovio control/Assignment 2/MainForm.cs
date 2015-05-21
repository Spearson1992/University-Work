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
    //public partial class MainForm : Form
    //{
    //    Rovio.Predator robot;
    //    public MainForm()
    //    {
    //        InitializeComponent();
    //    }

    //    private System.Threading.Thread robot_thread;

    //    private void MainForm_Load(object sender, EventArgs e)
    //    {
    //        //instantiate the robot object
    //       robot = new Rovio.Predator("http://10.82.0.31/", "user", "password");
            
    //        //initilise the image view window
    //        //ImageViewer source_view = new ImageViewer();
    //        //source_view.Text = "Source";
    //        //source_view.Show();
    //        ////attach the robot event to the image update method
    //        //robot.SourceImage += source_view.UpdateImage;

    //        //repeat the above code to visualise other steps of your image processing algorithm
    //        //for example
    //        //ImageViewer grayscale_view = new ImageViewer();
    //        //grayscale_view.Text = "Grayscale";
    //        //grayscale_view.Show();
    //        //robot.GrayscaleImage += grayscale_view.UpdateImage;

    //        ImageViewer object_view = new ImageViewer();
    //        object_view.Text = "Objects";
    //        object_view.Show();
    //        robot.ObjectImage += object_view.UpdateImage;
    //        //create and start the robot thread: your own implementation in MyRobot class
    //        robot_thread = new System.Threading.Thread(new System.Threading.ThreadStart(robot.RunRobot));
    //        robot_thread.Start();
    //    }

    //    private void MainForm_FormClosed(object sender, FormClosedEventArgs e)
    //    {
    //        //close the robot thread
    //        robot.terminateRobotThread = true;
    //        robot.terminateImageThread = true;
    //    }
    //}
}
