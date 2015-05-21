using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
namespace Assignment_2_to_do_list
{
    public class Task: IAlarm
    {
        private string _taskName;
        private string _taskDescription;
        private DateTime _due;
        private bool _completed;
        private bool warningShown;
        #region Properties
        public string taskName
        {
            get
            {
                return _taskName;
            }
            set
            {
                _taskName = value;
            }
        }
        public string taskDescription
        {
            get
            {
                return _taskDescription;
            }
            set
            {
                _taskDescription = value;
            }
        }
         
        public DateTime due
            {
                get
                {
                    return _due;
                }
                set
                {
                    _due = value;
                }
            }
        public bool taskComplete
        {
            get
            {
                return _completed;
            }
            set
            {
                _completed = value;
            }
        }
            
        #endregion
            public Task() 
            {
                warningShown = false;
            }
            public Task(string name,
                        string description, 
                        DateTime due)
            {
                _taskName = name;
                _taskDescription = description;
                _due = due;
                warningShown = false;
            }
        //notify user that task is overdue
            public void notify()
            {
                //If warning has already been shown don't show it again
                if (!warningShown)
                {
                    if ((_due - System.DateTime.Now).Days == 0 &&
                        (_due - System.DateTime.Now).Hours == 0 && 
                        (_due - System.DateTime.Now).Minutes == 0)
                    {
                        stopAlarm();
                        MessageBox.Show("Warning your task is " + ((_due - System.DateTime.Now).Seconds) * -1
                                         + " seconds overdue", "Task overdue", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        
                    }
                    else if ((_due - System.DateTime.Now).Days == 0 &&
                             (_due - System.DateTime.Now).Hours == 0)
                    {
                        stopAlarm();
                        MessageBox.Show("Warning your task is " + ((_due - System.DateTime.Now).Minutes) * -1 
                                         + " minutes overdue", "Task overdue", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        
                    }
                    else if ((_due - System.DateTime.Now).Days == 0)
                    {
                        stopAlarm();
                        MessageBox.Show("Warning your task is " + ((_due - System.DateTime.Now).Hours) * -1 
                                         + " hours overdue", "Task overdue", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        
                    }
                    else
                    {
                        stopAlarm();
                        //display message box telling user their task is overdue and by how many days
                        MessageBox.Show("Warning your task is overdue by " + ((_due - System.DateTime.Now).Days) * -1
                                         + " days", "Task overdue", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        
                    }
                    
                }
            }
            //stop alarm being shown again during this session
            public void stopAlarm() 
            {
                warningShown = true;
            }
    }

}


