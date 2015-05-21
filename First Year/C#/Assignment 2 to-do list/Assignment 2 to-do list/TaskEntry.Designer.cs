namespace Assignment_2_to_do_list
{
    partial class TaskEntry
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
            this.txt_TaskTitle = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.btn_Ok = new System.Windows.Forms.Button();
            this.btn_Cancel = new System.Windows.Forms.Button();
            this.DateEntry = new System.Windows.Forms.DateTimePicker();
            this.txt_TaskDescription = new System.Windows.Forms.TextBox();
            this.lbl_taskDeadline = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // txt_TaskTitle
            // 
            this.txt_TaskTitle.Location = new System.Drawing.Point(98, 37);
            this.txt_TaskTitle.MaxLength = 16;
            this.txt_TaskTitle.Name = "txt_TaskTitle";
            this.txt_TaskTitle.Size = new System.Drawing.Size(357, 20);
            this.txt_TaskTitle.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(38, 40);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(54, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Task Title";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 79);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(87, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Task Description";
            // 
            // btn_Ok
            // 
            this.btn_Ok.Location = new System.Drawing.Point(296, 132);
            this.btn_Ok.Name = "btn_Ok";
            this.btn_Ok.Size = new System.Drawing.Size(75, 23);
            this.btn_Ok.TabIndex = 4;
            this.btn_Ok.Text = "Ok";
            this.btn_Ok.UseVisualStyleBackColor = true;
            this.btn_Ok.Click += new System.EventHandler(this.btn_Ok_Click);
            // 
            // btn_Cancel
            // 
            this.btn_Cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btn_Cancel.Location = new System.Drawing.Point(380, 132);
            this.btn_Cancel.Name = "btn_Cancel";
            this.btn_Cancel.Size = new System.Drawing.Size(75, 23);
            this.btn_Cancel.TabIndex = 5;
            this.btn_Cancel.Text = "Cancel";
            this.btn_Cancel.UseVisualStyleBackColor = true;
            this.btn_Cancel.Click += new System.EventHandler(this.btn_Cancel_Click);
            // 
            // DateEntry
            // 
            this.DateEntry.CustomFormat = "dd/MM/yyyy HH:mm";
            this.DateEntry.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.DateEntry.Location = new System.Drawing.Point(98, 105);
            this.DateEntry.Name = "DateEntry";
            this.DateEntry.Size = new System.Drawing.Size(192, 20);
            this.DateEntry.TabIndex = 6;
            // 
            // txt_TaskDescription
            // 
            this.txt_TaskDescription.Location = new System.Drawing.Point(98, 72);
            this.txt_TaskDescription.MaxLength = 256;
            this.txt_TaskDescription.Name = "txt_TaskDescription";
            this.txt_TaskDescription.Size = new System.Drawing.Size(357, 20);
            this.txt_TaskDescription.TabIndex = 7;
            // 
            // lbl_taskDeadline
            // 
            this.lbl_taskDeadline.AutoSize = true;
            this.lbl_taskDeadline.Location = new System.Drawing.Point(15, 111);
            this.lbl_taskDeadline.Name = "lbl_taskDeadline";
            this.lbl_taskDeadline.Size = new System.Drawing.Size(76, 13);
            this.lbl_taskDeadline.TabIndex = 8;
            this.lbl_taskDeadline.Text = "Task Deadline";
            // 
            // TaskEntry
            // 
            this.AcceptButton = this.btn_Ok;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.btn_Cancel;
            this.ClientSize = new System.Drawing.Size(480, 169);
            this.Controls.Add(this.lbl_taskDeadline);
            this.Controls.Add(this.txt_TaskDescription);
            this.Controls.Add(this.DateEntry);
            this.Controls.Add(this.btn_Cancel);
            this.Controls.Add(this.btn_Ok);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txt_TaskTitle);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "TaskEntry";
            this.Text = "Add a task";
            this.Load += new System.EventHandler(this.TaskEntry_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txt_TaskTitle;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btn_Cancel;
        private System.Windows.Forms.DateTimePicker DateEntry;
        private System.Windows.Forms.Button btn_Ok;
        private System.Windows.Forms.TextBox txt_TaskDescription;
        private System.Windows.Forms.Label lbl_taskDeadline;
    }
}