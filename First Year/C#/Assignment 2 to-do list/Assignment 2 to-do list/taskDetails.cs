using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Assignment_2_to_do_list
{
    public partial class taskDetails : Form
    {
        
        Task currentTask;
        Timer time;


        public taskDetails(Task selectedTask)
        {
            InitializeComponent();
            txt_Name.Text = selectedTask.taskName;
            txt_Description.Text = selectedTask.taskDescription;
            currentTask = selectedTask;
            initialiseTimer();
        }

        

        private void time_Tick(object sender, EventArgs e)
        {
            if (!currentTask.taskComplete)
            {
                
                if (currentTask.due.CompareTo(System.DateTime.Now) < 0)
                {
                    dateTaskDue.Text = "Task Overdue";
                    currentTask.notify();
                    time.Stop();
                    time.Dispose();
                }
                else
                {

                    if ((currentTask.due - System.DateTime.Now).Days < 1)
                    {
                        time.Interval = 1000;//sets timer activation interval to 1 second
                        TimeSpan tt = (currentTask.due - System.DateTime.Now);
                        string ts = tt.Hours + ":" + tt.Minutes + ":" + tt.Seconds;
                        dateTaskDue.Text = ts;
                    }
                    else
                    {
                        dateTaskDue.Text = Convert.ToString((currentTask.due - System.DateTime.Now).Days) + " Days";
                    }
                }
                
            }
            else
            {
                dateTaskDue.Text = "Task Complete";
            }
        }

        private void btn_ok_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btn_completed_Click(object sender, EventArgs e)
        {
            currentTask.taskComplete = true;
            this.Close();

        }

        private void taskDetails_Closing(object sender, EventArgs e)
        {
            if (time != null)
            {
                time.Stop();
                time.Dispose();
            }
        }
        private void initialiseTimer()
        {
            if (currentTask.taskComplete == false && currentTask.due.CompareTo(System.DateTime.Now) >= 0)
            {
                //Starts a time to count down task deadline once per second
                int timerAdjust = 60 - System.DateTime.Now.Second;
                time = new Timer();
                time.Tick += new EventHandler(time_Tick);
                time.Start();
            }
            else
            {
                if (currentTask.taskComplete)
                {
                    dateTaskDue.Text = "Task Complete";
                }
                else
                {
                    dateTaskDue.Text = "Task Overdue";
                    currentTask.notify();
                }
            }
        }
    }
}
