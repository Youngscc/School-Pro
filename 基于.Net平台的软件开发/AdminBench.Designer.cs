namespace 实验1
{
    partial class AdminBench
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
            this.BookIns = new System.Windows.Forms.Button();
            this.BookMgr = new System.Windows.Forms.Button();
            this.Drop = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // BookIns
            // 
            this.BookIns.Cursor = System.Windows.Forms.Cursors.Hand;
            this.BookIns.Font = new System.Drawing.Font("方正粗黑宋简体", 16.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.BookIns.Location = new System.Drawing.Point(68, 156);
            this.BookIns.Name = "BookIns";
            this.BookIns.Size = new System.Drawing.Size(139, 139);
            this.BookIns.TabIndex = 0;
            this.BookIns.Text = "图书录入";
            this.BookIns.UseVisualStyleBackColor = true;
            this.BookIns.Click += new System.EventHandler(this.BookIns_Click);
            // 
            // BookMgr
            // 
            this.BookMgr.Cursor = System.Windows.Forms.Cursors.Hand;
            this.BookMgr.Font = new System.Drawing.Font("方正粗黑宋简体", 16.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.BookMgr.Location = new System.Drawing.Point(271, 156);
            this.BookMgr.Name = "BookMgr";
            this.BookMgr.Size = new System.Drawing.Size(139, 139);
            this.BookMgr.TabIndex = 1;
            this.BookMgr.Text = "图书查询";
            this.BookMgr.UseVisualStyleBackColor = true;
            this.BookMgr.Click += new System.EventHandler(this.BookMgr_Click);
            // 
            // Drop
            // 
            this.Drop.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Drop.Font = new System.Drawing.Font("方正粗黑宋简体", 16.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Drop.Location = new System.Drawing.Point(465, 156);
            this.Drop.Name = "Drop";
            this.Drop.Size = new System.Drawing.Size(139, 139);
            this.Drop.TabIndex = 2;
            this.Drop.Text = "图书删除";
            this.Drop.UseVisualStyleBackColor = true;
            this.Drop.Click += new System.EventHandler(this.Drop_Click);
            // 
            // AdminBench
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Info;
            this.ClientSize = new System.Drawing.Size(691, 450);
            this.Controls.Add(this.Drop);
            this.Controls.Add(this.BookMgr);
            this.Controls.Add(this.BookIns);
            this.MaximizeBox = false;
            this.Name = "AdminBench";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "AdminBench";
            this.Load += new System.EventHandler(this.AdminBench_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button BookIns;
        private System.Windows.Forms.Button BookMgr;
        private System.Windows.Forms.Button Drop;
    }
}