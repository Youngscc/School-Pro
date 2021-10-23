namespace 实验1
{
    partial class BookIns
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
            this.Bookname = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.InsName = new System.Windows.Forms.MaskedTextBox();
            this.InsID = new System.Windows.Forms.MaskedTextBox();
            this.btOK = new System.Windows.Forms.Button();
            this.btCancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Bookname
            // 
            this.Bookname.AutoSize = true;
            this.Bookname.Location = new System.Drawing.Point(50, 45);
            this.Bookname.Name = "Bookname";
            this.Bookname.Size = new System.Drawing.Size(68, 15);
            this.Bookname.TabIndex = 0;
            this.Bookname.Text = "书  名：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(50, 97);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(68, 15);
            this.label2.TabIndex = 1;
            this.label2.Text = "编  号：";
            // 
            // InsName
            // 
            this.InsName.Location = new System.Drawing.Point(124, 42);
            this.InsName.Name = "InsName";
            this.InsName.Size = new System.Drawing.Size(107, 25);
            this.InsName.TabIndex = 2;
            // 
            // InsID
            // 
            this.InsID.Location = new System.Drawing.Point(124, 94);
            this.InsID.Name = "InsID";
            this.InsID.Size = new System.Drawing.Size(107, 25);
            this.InsID.TabIndex = 3;
            // 
            // btOK
            // 
            this.btOK.Location = new System.Drawing.Point(53, 145);
            this.btOK.Name = "btOK";
            this.btOK.Size = new System.Drawing.Size(75, 23);
            this.btOK.TabIndex = 4;
            this.btOK.Text = "确认";
            this.btOK.UseVisualStyleBackColor = true;
            this.btOK.Click += new System.EventHandler(this.btOK_Click);
            // 
            // btCancel
            // 
            this.btCancel.Location = new System.Drawing.Point(156, 145);
            this.btCancel.Name = "btCancel";
            this.btCancel.Size = new System.Drawing.Size(75, 23);
            this.btCancel.TabIndex = 5;
            this.btCancel.Text = "取消";
            this.btCancel.UseVisualStyleBackColor = true;
            this.btCancel.Click += new System.EventHandler(this.btCancel_Click);
            // 
            // BookIns
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(294, 214);
            this.Controls.Add(this.btCancel);
            this.Controls.Add(this.btOK);
            this.Controls.Add(this.InsID);
            this.Controls.Add(this.InsName);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.Bookname);
            this.MaximizeBox = false;
            this.Name = "BookIns";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "BookIns";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label Bookname;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.MaskedTextBox InsName;
        private System.Windows.Forms.MaskedTextBox InsID;
        private System.Windows.Forms.Button btOK;
        private System.Windows.Forms.Button btCancel;
    }
}