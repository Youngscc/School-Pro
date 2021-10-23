namespace 实验1
{
    partial class UserBench
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
            this.Return = new System.Windows.Forms.Button();
            this.borrow = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Return
            // 
            this.Return.Font = new System.Drawing.Font("方正粗黑宋简体", 16.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Return.Location = new System.Drawing.Point(65, 123);
            this.Return.Name = "Return";
            this.Return.Size = new System.Drawing.Size(139, 139);
            this.Return.TabIndex = 0;
            this.Return.Text = "归还图书";
            this.Return.UseVisualStyleBackColor = true;
            this.Return.Click += new System.EventHandler(this.Return_Click);
            // 
            // borrow
            // 
            this.borrow.Font = new System.Drawing.Font("方正粗黑宋简体", 16.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.borrow.Location = new System.Drawing.Point(249, 123);
            this.borrow.Name = "borrow";
            this.borrow.Size = new System.Drawing.Size(139, 139);
            this.borrow.TabIndex = 1;
            this.borrow.Text = "借阅图书";
            this.borrow.UseVisualStyleBackColor = true;
            this.borrow.Click += new System.EventHandler(this.borrow_Click);
            // 
            // button3
            // 
            this.button3.Font = new System.Drawing.Font("方正粗黑宋简体", 16.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button3.Location = new System.Drawing.Point(432, 123);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(139, 139);
            this.button3.TabIndex = 2;
            this.button3.Text = "查询图书";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // UserBench
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(635, 425);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.borrow);
            this.Controls.Add(this.Return);
            this.MaximizeBox = false;
            this.Name = "UserBench";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "UserBench";
            this.Load += new System.EventHandler(this.UserBench_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button Return;
        private System.Windows.Forms.Button borrow;
        private System.Windows.Forms.Button button3;
    }
}