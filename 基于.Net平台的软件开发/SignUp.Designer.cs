namespace 实验1
{
    partial class SignUp
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
            this.suID = new System.Windows.Forms.Label();
            this.suName = new System.Windows.Forms.Label();
            this.suPW = new System.Windows.Forms.Label();
            this.suPW2 = new System.Windows.Forms.Label();
            this.insID = new System.Windows.Forms.MaskedTextBox();
            this.insName = new System.Windows.Forms.MaskedTextBox();
            this.insPW = new System.Windows.Forms.MaskedTextBox();
            this.insPW2 = new System.Windows.Forms.MaskedTextBox();
            this.btOK = new System.Windows.Forms.Button();
            this.btCancel = new System.Windows.Forms.Button();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // suID
            // 
            this.suID.AutoSize = true;
            this.suID.Location = new System.Drawing.Point(120, 40);
            this.suID.Name = "suID";
            this.suID.Size = new System.Drawing.Size(68, 15);
            this.suID.TabIndex = 0;
            this.suID.Text = "学  号：";
            // 
            // suName
            // 
            this.suName.AutoSize = true;
            this.suName.Location = new System.Drawing.Point(120, 86);
            this.suName.Name = "suName";
            this.suName.Size = new System.Drawing.Size(68, 15);
            this.suName.TabIndex = 1;
            this.suName.Text = "姓  名：";
            // 
            // suPW
            // 
            this.suPW.AutoSize = true;
            this.suPW.Location = new System.Drawing.Point(120, 132);
            this.suPW.Name = "suPW";
            this.suPW.Size = new System.Drawing.Size(68, 15);
            this.suPW.TabIndex = 2;
            this.suPW.Text = "密  码：";
            // 
            // suPW2
            // 
            this.suPW2.AutoSize = true;
            this.suPW2.Location = new System.Drawing.Point(106, 180);
            this.suPW2.Name = "suPW2";
            this.suPW2.Size = new System.Drawing.Size(82, 15);
            this.suPW2.TabIndex = 3;
            this.suPW2.Text = "确认密码：";
            // 
            // insID
            // 
            this.insID.Location = new System.Drawing.Point(218, 37);
            this.insID.Name = "insID";
            this.insID.Size = new System.Drawing.Size(137, 25);
            this.insID.TabIndex = 4;
            // 
            // insName
            // 
            this.insName.Location = new System.Drawing.Point(218, 83);
            this.insName.Name = "insName";
            this.insName.Size = new System.Drawing.Size(137, 25);
            this.insName.TabIndex = 5;
            // 
            // insPW
            // 
            this.insPW.Location = new System.Drawing.Point(218, 129);
            this.insPW.Name = "insPW";
            this.insPW.PasswordChar = '*';
            this.insPW.Size = new System.Drawing.Size(137, 25);
            this.insPW.TabIndex = 6;
            // 
            // insPW2
            // 
            this.insPW2.Location = new System.Drawing.Point(218, 177);
            this.insPW2.Name = "insPW2";
            this.insPW2.PasswordChar = '*';
            this.insPW2.Size = new System.Drawing.Size(137, 25);
            this.insPW2.TabIndex = 7;
            // 
            // btOK
            // 
            this.btOK.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btOK.Location = new System.Drawing.Point(113, 267);
            this.btOK.Name = "btOK";
            this.btOK.Size = new System.Drawing.Size(75, 23);
            this.btOK.TabIndex = 8;
            this.btOK.Text = "确认";
            this.btOK.UseVisualStyleBackColor = true;
            this.btOK.Click += new System.EventHandler(this.btOK_Click);
            // 
            // btCancel
            // 
            this.btCancel.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btCancel.Location = new System.Drawing.Point(280, 267);
            this.btCancel.Name = "btCancel";
            this.btCancel.Size = new System.Drawing.Size(75, 23);
            this.btCancel.TabIndex = 9;
            this.btCancel.Text = "取消";
            this.btCancel.UseVisualStyleBackColor = true;
            this.btCancel.Click += new System.EventHandler(this.btCancel_Click);
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(141, 231);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(104, 19);
            this.checkBox1.TabIndex = 10;
            this.checkBox1.Text = "管理员账户";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // SignUp
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(484, 337);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.btCancel);
            this.Controls.Add(this.btOK);
            this.Controls.Add(this.insPW2);
            this.Controls.Add(this.insPW);
            this.Controls.Add(this.insName);
            this.Controls.Add(this.insID);
            this.Controls.Add(this.suPW2);
            this.Controls.Add(this.suPW);
            this.Controls.Add(this.suName);
            this.Controls.Add(this.suID);
            this.MaximizeBox = false;
            this.Name = "SignUp";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "SignUp";
            this.Load += new System.EventHandler(this.SignUp_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label suID;
        private System.Windows.Forms.Label suName;
        private System.Windows.Forms.Label suPW;
        private System.Windows.Forms.Label suPW2;
        private System.Windows.Forms.MaskedTextBox insID;
        private System.Windows.Forms.MaskedTextBox insName;
        private System.Windows.Forms.MaskedTextBox insPW;
        private System.Windows.Forms.MaskedTextBox insPW2;
        private System.Windows.Forms.Button btOK;
        private System.Windows.Forms.Button btCancel;
        private System.Windows.Forms.CheckBox checkBox1;
    }
}