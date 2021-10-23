using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 实验1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            User user = new User();
            if (user.ShowDialog() == DialogResult.OK) ;
            else user.Close();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Admin admin = new Admin();
            if (admin.ShowDialog() == DialogResult.OK) ;
            else admin.Close();
        }

        private void signup_Click(object sender, EventArgs e)
        {
            SignUp signup = new SignUp();
            if (signup.ShowDialog() == DialogResult.OK) ;
            else signup.Close();
        }
    }
}
