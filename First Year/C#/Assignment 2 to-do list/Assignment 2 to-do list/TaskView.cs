using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace Assignment_2_to_do_list
{
    public partial class TaskView : Form
    {
        int taskCount = 0;
        Timer updateTimeRemaining;      

        
        //Constructor
        public TaskView()
        {
            InitializeComponent();
            updateTimeRemaining = new Timer();
            updateTimeRemaining.Tick += new EventHandler(updateTimeRemaining_Tick);
            updateTimeRemaining.Start();
            fileIo tl = new fileIo();
            if (File.Exists("Tasks.userdata"))//prevent the program from loading a file which does not exist
            {
                //Add saved tasks back into the list view on initialisation
                ListViewItem[] loadedVals = tl.load();
                taskCount = loadedVals.Length;
                //add group information to the list view items
                foreach (ListViewItem li in loadedVals)
                {
                    Task t = (Task)li.Tag;
                    if (t.taskComplete)
                    {
                        li.Group = list_Tasks.Groups[0];
                    }
                    else
                    {
                        li.Group = list_Tasks.Groups[1];
                    }
                    if (!t.taskComplete && t.due.CompareTo(System.DateTime.Now) >= 0)
                    {
                        TimeSpan tt = (t.due - System.DateTime.Now);
                        string tr = tt.Days + ":" + tt.Hours + ":" + tt.Seconds;
                        li.SubItems.Add(tr);
                    }
                    else if (t.taskComplete)
                    {

                        li.SubItems.Add("Task Completed");
                    }
                    else
                    {
                        
                        li.SubItems.Add("Task Overdue");
                    }
                }
                list_Tasks.Items.AddRange(loadedVals);
            }

            displayTaskStatus();
        }
       
        //Bring up a window showing details of the selected task
        private void list_Tasks_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            Task temp= (Task) list_Tasks.Items[list_Tasks.FocusedItem.Index].Tag;
            taskDetails details = new taskDetails(temp);
            details.ShowDialog();
        }

        //updates time remaining column in list_tasks once per second
        private void updateTimeRemaining_Tick(object sender, EventArgs e)
        {
            updateTimeRemaining.Interval = 1000;
            updateListViewTimeRemaining();
        }

        //Uses a foreach loop to iterate through each item in the list view and updates
        // the time remaining column
        private void updateListViewTimeRemaining()
        {
            list_Tasks.BeginUpdate();//Prevents flickering when the list view updates
            foreach (ListViewItem li in list_Tasks.Items)
            {

                Task t = (Task)li.Tag;
                if ((t.due - System.DateTime.Now).Days < 1)
                {
                    if (!t.taskComplete && t.due.CompareTo(System.DateTime.Now) >= 0)
                    {
                        TimeSpan tt = (t.due - System.DateTime.Now);
                        string tr = tt.Hours + ":" + tt.Minutes + ":" + tt.Seconds;
                        li.SubItems[1].Text = tr;
                    }
                    else if (t.taskComplete)
                    {

                        li.SubItems[1].Text = "Task Completed";
                        li.Group = list_Tasks.Groups[0];
                        displayTaskStatus();
                    }
                    else
                    {

                        li.SubItems[1].Text = "Task Overdue";
                        displayTaskStatus();
                    }
                }

                else
                {
                    if (t.taskComplete)
                    {
                        li.SubItems[1].Text = "Task Completed";
                        li.Group = list_Tasks.Groups[0];
                        displayTaskStatus();
                    }
                    else
                    {
                        li.SubItems[1].Text = Convert.ToString((t.due - System.DateTime.Now).Days) + " Days";
                    }
                }
            

            }
            list_Tasks.EndUpdate();// allows form to be redrawn after update
        }

        //Saves Tasks if the user presses yes on form close
        private void Form1_Close(object sender, EventArgs e)
        {
            DialogResult dlg = MessageBox.Show("Would you like to save your tasks before quitting?", "Save Tasks", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (dlg == DialogResult.Yes)
            {
                fileIo ts = new fileIo();
                ts.save(list_Tasks);
            }
        }
        //update the labels on the main page
        private void displayTaskStatus()
        {
            int timeLeft = 0;
            int overdue = 0;
            int lessThanOneDay = 0;
            foreach (ListViewItem lv in list_Tasks.Items)
            {
                
                Task temp = (Task) lv.Tag;
                if (!temp.taskComplete)
                {
                    if ((temp.due - System.DateTime.Now).Days > 1)
                    {
                        timeLeft++;
                    }
                    else if ((temp.due - System.DateTime.Now).Hours > 0 && (temp.due - System.DateTime.Now).Hours <= 24)
                    {
                        lessThanOneDay++;
                    }
                    else if((temp.due - System.DateTime.Now).Minutes > 0 && (temp.due - System.DateTime.Now).Minutes <= 60)
                    {
                        lessThanOneDay++;
                    }
                    else if((temp.due - System.DateTime.Now).Seconds > 0 && (temp.due - System.DateTime.Now).Seconds <= 60)
                    {
                        lessThanOneDay++;
                    }
                    else { overdue++; }
                }
            }
            lbl_Overdue.Text = "Tasks Overdue: " + overdue;
            lbl_oneDayremaining.Text = "Tasks with one day or less remaining: " + lessThanOneDay;
            lbl_plentyOfTime.Text = "Tasks with more than one day remaining: " + timeLeft;
        }
       
        //adds a task to the listview
        private void addTask()
        {
            TaskEntry addedTask = new TaskEntry();
            addedTask.ShowDialog();
            if (addedTask.okPressed)
            {
                Task temp = new Task(addedTask.taskName, addedTask.taskDescription, addedTask.due);
                ListViewItem tempStore = new ListViewItem(temp.taskName);
                TimeSpan tt = (temp.due - System.DateTime.Now);
                string tr =tt.Days + ":" + tt.Hours + ":" + tt.Seconds;
                tempStore.Name = temp.taskName;
                tempStore.Tag = temp;
                tempStore.Group = list_Tasks.Groups[1];
                tempStore.SubItems.Add(tr);
                list_Tasks.Items.Add(tempStore);
                displayTaskStatus();//updates labels on main window

            }
        }

        //Creates a new task entry window for the user to add a task
        //also contains validation to prevent use from entering too many tasks at once
        private void addTaskToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (taskCount < 5)
            {
                addTask();
                taskCount++;
            }
            else
            {
                MessageBox.Show("Error you may only enter 5 tasks", "Too many tasks entered", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        //Deletes tasks only if there are tasks present
        private void deleteTaskToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (list_Tasks.Items.Count > 0)
            {
                if (list_Tasks.SelectedItems.Count > 0)
                {
                    list_Tasks.Items.RemoveAt(list_Tasks.FocusedItem.Index);
                    taskCount--;
                }
                else
                {
                    MessageBox.Show("You must select an item to delete", "No item selected", MessageBoxButtons.OK);
                }
            }
            
        }
        //close window
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        //show about message box
        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Task Organiser\nVersion 1.0\nCreator Sam Pearson", "About", MessageBoxButtons.OK);
        }
    }
}
