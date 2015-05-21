namespace Assignment_2_to_do_list
{
    partial class TaskView
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.ListViewGroup listViewGroup3 = new System.Windows.Forms.ListViewGroup("Completed Tasks", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup4 = new System.Windows.Forms.ListViewGroup("Outstanding Tasks", System.Windows.Forms.HorizontalAlignment.Left);
            this.list_Tasks = new System.Windows.Forms.ListView();
            this.cl_taskName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.cl_timeRemaining = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.lbl_Overdue = new System.Windows.Forms.Label();
            this.lbl_oneDayremaining = new System.Windows.Forms.Label();
            this.lbl_plentyOfTime = new System.Windows.Forms.Label();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addTaskToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deleteTaskToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // list_Tasks
            // 
            this.list_Tasks.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.cl_taskName,
            this.cl_timeRemaining});
            listViewGroup3.Header = "Completed Tasks";
            listViewGroup3.Name = "finishedTask";
            listViewGroup4.Header = "Outstanding Tasks";
            listViewGroup4.Name = "unfinishedTasks";
            this.list_Tasks.Groups.AddRange(new System.Windows.Forms.ListViewGroup[] {
            listViewGroup3,
            listViewGroup4});
            this.list_Tasks.Location = new System.Drawing.Point(12, 27);
            this.list_Tasks.MultiSelect = false;
            this.list_Tasks.Name = "list_Tasks";
            this.list_Tasks.Size = new System.Drawing.Size(425, 183);
            this.list_Tasks.TabIndex = 0;
            this.list_Tasks.UseCompatibleStateImageBehavior = false;
            this.list_Tasks.View = System.Windows.Forms.View.Details;
            this.list_Tasks.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.list_Tasks_MouseDoubleClick);
            // 
            // cl_taskName
            // 
            this.cl_taskName.Text = "Task Name";
            this.cl_taskName.Width = 197;
            // 
            // cl_timeRemaining
            // 
            this.cl_timeRemaining.Text = "Time Remaining";
            this.cl_timeRemaining.Width = 256;
            // 
            // lbl_Overdue
            // 
            this.lbl_Overdue.AutoSize = true;
            this.lbl_Overdue.Location = new System.Drawing.Point(44, 213);
            this.lbl_Overdue.Name = "lbl_Overdue";
            this.lbl_Overdue.Size = new System.Drawing.Size(0, 13);
            this.lbl_Overdue.TabIndex = 3;
            // 
            // lbl_oneDayremaining
            // 
            this.lbl_oneDayremaining.AutoSize = true;
            this.lbl_oneDayremaining.Location = new System.Drawing.Point(44, 239);
            this.lbl_oneDayremaining.Name = "lbl_oneDayremaining";
            this.lbl_oneDayremaining.Size = new System.Drawing.Size(0, 13);
            this.lbl_oneDayremaining.TabIndex = 4;
            // 
            // lbl_plentyOfTime
            // 
            this.lbl_plentyOfTime.AutoSize = true;
            this.lbl_plentyOfTime.Location = new System.Drawing.Point(44, 265);
            this.lbl_plentyOfTime.Name = "lbl_plentyOfTime";
            this.lbl_plentyOfTime.Size = new System.Drawing.Size(0, 13);
            this.lbl_plentyOfTime.TabIndex = 5;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.editToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(449, 24);
            this.menuStrip1.TabIndex = 6;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.ShortcutKeyDisplayString = "";
            this.exitToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F4)));
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(134, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // editToolStripMenuItem
            // 
            this.editToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addTaskToolStripMenuItem,
            this.deleteTaskToolStripMenuItem});
            this.editToolStripMenuItem.Name = "editToolStripMenuItem";
            this.editToolStripMenuItem.Size = new System.Drawing.Size(39, 20);
            this.editToolStripMenuItem.Text = "Edit";
            // 
            // addTaskToolStripMenuItem
            // 
            this.addTaskToolStripMenuItem.Name = "addTaskToolStripMenuItem";
            this.addTaskToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F2;
            this.addTaskToolStripMenuItem.Size = new System.Drawing.Size(158, 22);
            this.addTaskToolStripMenuItem.Text = "Add Task";
            this.addTaskToolStripMenuItem.Click += new System.EventHandler(this.addTaskToolStripMenuItem_Click);
            // 
            // deleteTaskToolStripMenuItem
            // 
            this.deleteTaskToolStripMenuItem.Name = "deleteTaskToolStripMenuItem";
            this.deleteTaskToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.Delete;
            this.deleteTaskToolStripMenuItem.Size = new System.Drawing.Size(158, 22);
            this.deleteTaskToolStripMenuItem.Text = "Delete Task";
            this.deleteTaskToolStripMenuItem.Click += new System.EventHandler(this.deleteTaskToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F1;
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(126, 22);
            this.aboutToolStripMenuItem.Text = "About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // TaskView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(449, 309);
            this.Controls.Add(this.lbl_plentyOfTime);
            this.Controls.Add(this.lbl_oneDayremaining);
            this.Controls.Add(this.lbl_Overdue);
            this.Controls.Add(this.list_Tasks);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "TaskView";
            this.Text = "Current Tasks";
            this.Closing += new System.ComponentModel.CancelEventHandler(this.Form1_Close);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListView list_Tasks;
        private System.Windows.Forms.ColumnHeader cl_taskName;
        private System.Windows.Forms.Label lbl_Overdue;
        private System.Windows.Forms.Label lbl_oneDayremaining;
        private System.Windows.Forms.Label lbl_plentyOfTime;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addTaskToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem deleteTaskToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ColumnHeader cl_timeRemaining;
    }
}

