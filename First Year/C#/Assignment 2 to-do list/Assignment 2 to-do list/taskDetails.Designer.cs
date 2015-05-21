namespace Assignment_2_to_do_list
{
    partial class taskDetails
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
            this.txt_Description = new System.Windows.Forms.RichTextBox();
            this.txt_Name = new System.Windows.Forms.TextBox();
            this.btn_completed = new System.Windows.Forms.Button();
            this.btn_ok = new System.Windows.Forms.Button();
            this.dateTaskDue = new System.Windows.Forms.TextBox();
            this.lbl_timeRemaining = new System.Windows.Forms.Label();
            this.lbl_taskDiscription = new System.Windows.Forms.Label();
            this.lbl_taskTitle = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // txt_Description
            // 
            this.txt_Description.Location = new System.Drawing.Point(12, 64);
            this.txt_Description.MaxLength = 256;
            this.txt_Description.Name = "txt_Description";
            this.txt_Description.Size = new System.Drawing.Size(265, 171);
            this.txt_Description.TabIndex = 3;
            this.txt_Description.Text = "";
            // 
            // txt_Name
            // 
            this.txt_Name.Location = new System.Drawing.Point(12, 25);
            this.txt_Name.MaxLength = 16;
            this.txt_Name.Name = "txt_Name";
            this.txt_Name.Size = new System.Drawing.Size(265, 20);
            this.txt_Name.TabIndex = 4;
            // 
            // btn_completed
            // 
            this.btn_completed.Location = new System.Drawing.Point(202, 280);
            this.btn_completed.Name = "btn_completed";
            this.btn_completed.Size = new System.Drawing.Size(75, 23);
            this.btn_completed.TabIndex = 5;
            this.btn_completed.Text = "Completed";
            this.btn_completed.UseVisualStyleBackColor = true;
            this.btn_completed.Click += new System.EventHandler(this.btn_completed_Click);
            // 
            // btn_ok
            // 
            this.btn_ok.Location = new System.Drawing.Point(127, 280);
            this.btn_ok.Name = "btn_ok";
            this.btn_ok.Size = new System.Drawing.Size(75, 23);
            this.btn_ok.TabIndex = 6;
            this.btn_ok.Text = "Ok";
            this.btn_ok.UseVisualStyleBackColor = true;
            this.btn_ok.Click += new System.EventHandler(this.btn_ok_Click);
            // 
            // dateTaskDue
            // 
            this.dateTaskDue.Location = new System.Drawing.Point(12, 254);
            this.dateTaskDue.Name = "dateTaskDue";
            this.dateTaskDue.Size = new System.Drawing.Size(265, 20);
            this.dateTaskDue.TabIndex = 7;
            // 
            // lbl_timeRemaining
            // 
            this.lbl_timeRemaining.AutoSize = true;
            this.lbl_timeRemaining.Location = new System.Drawing.Point(9, 238);
            this.lbl_timeRemaining.Name = "lbl_timeRemaining";
            this.lbl_timeRemaining.Size = new System.Drawing.Size(78, 13);
            this.lbl_timeRemaining.TabIndex = 8;
            this.lbl_timeRemaining.Text = "Time remaining";
            // 
            // lbl_taskDiscription
            // 
            this.lbl_taskDiscription.AutoSize = true;
            this.lbl_taskDiscription.Location = new System.Drawing.Point(9, 48);
            this.lbl_taskDiscription.Name = "lbl_taskDiscription";
            this.lbl_taskDiscription.Size = new System.Drawing.Size(87, 13);
            this.lbl_taskDiscription.TabIndex = 9;
            this.lbl_taskDiscription.Text = "Task Description";
            // 
            // lbl_taskTitle
            // 
            this.lbl_taskTitle.AutoSize = true;
            this.lbl_taskTitle.Location = new System.Drawing.Point(9, 9);
            this.lbl_taskTitle.Name = "lbl_taskTitle";
            this.lbl_taskTitle.Size = new System.Drawing.Size(54, 13);
            this.lbl_taskTitle.TabIndex = 10;
            this.lbl_taskTitle.Text = "Task Title";
            // 
            // taskDetails
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(285, 307);
            this.Controls.Add(this.lbl_taskTitle);
            this.Controls.Add(this.lbl_taskDiscription);
            this.Controls.Add(this.lbl_timeRemaining);
            this.Controls.Add(this.dateTaskDue);
            this.Controls.Add(this.btn_ok);
            this.Controls.Add(this.btn_completed);
            this.Controls.Add(this.txt_Name);
            this.Controls.Add(this.txt_Description);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "taskDetails";
            this.Text = "taskDetails";
            this.Closing += new System.ComponentModel.CancelEventHandler(this.taskDetails_Closing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RichTextBox txt_Description;
        private System.Windows.Forms.TextBox txt_Name;
        private System.Windows.Forms.Button btn_completed;
        private System.Windows.Forms.Button btn_ok;
        private System.Windows.Forms.TextBox dateTaskDue;
        private System.Windows.Forms.Label lbl_timeRemaining;
        private System.Windows.Forms.Label lbl_taskDiscription;
        private System.Windows.Forms.Label lbl_taskTitle;
    }
}