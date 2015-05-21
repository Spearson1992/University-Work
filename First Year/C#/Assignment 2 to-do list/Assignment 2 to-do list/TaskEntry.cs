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
    public partial class TaskEntry : Form
    {
        
        private bool _okPressed;
        #region Properties
        public bool okPressed
        {
            get
            {
                return _okPressed;
            }
            set
            {
                _okPressed = value;
            }
        }
        public string taskName
        {
            get
            {
                return txt_TaskTitle.Text.ToString();
            }
        }
        public string taskDescription
        {
            get
            {
                return txt_TaskDescription.Text.ToString(); 
            }
        }
        public DateTime due
        {
            get
            {
                return DateEntry.Value.AddMilliseconds(-DateEntry.Value.Millisecond);
            }
        }
        #endregion

        public TaskEntry()
        {
            InitializeComponent();
            _okPressed = false;
            int timerAdjust = 60 - System.DateTime.Now.Second;
        }

        
        private void TaskEntry_Load(object sender, EventArgs e)
        {
        }
        //add task only if information is present
        private void btn_Ok_Click(object sender, EventArgs e)
        {

            string validate = null;
            if (DateEntry.Value < System.DateTime.Now)
            {
                validate = "Date entered cannot be before today\n";
            }
            if (txt_TaskTitle.Text == "")
            {
                validate +=  "Task must have a title\n";
            }
            if (txt_TaskDescription.Text == "")
            {
                validate += "Task must have a description\n";
            }
            if (txt_TaskTitle.Text.StartsWith(" ") || txt_TaskDescription.Text.StartsWith(" "))
            {
                validate += "Task title or description cannot start with a space";
            }
            if (validate != null)
            {
                MessageBox.Show(validate,"Error",MessageBoxButtons.OK,MessageBoxIcon.Error);
            }
            else
            {
                _okPressed = true;
                this.Close();
            }
            
        }
        private void btn_Cancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
