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
    public partial class UserBench : Form
    {
        public UserBench()
        {
            InitializeComponent();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            BookQuery bookQuery = new BookQuery();
            if (bookQuery.ShowDialog() == DialogResult.OK) ;
            else bookQuery.Close();
        }

        private void borrow_Click(object sender, EventArgs e)
        {
            BookBr bookBr = new BookBr();
            if (bookBr.ShowDialog() == DialogResult.OK) ;
            else bookBr.Close();
        }

        private void UserBench_Load(object sender, EventArgs e)
        {

        }

        private void Return_Click(object sender, EventArgs e)
        {
            BookReturn bookreturn = new BookReturn();
            if (bookreturn.ShowDialog() == DialogResult.OK) ;
            else bookreturn.Close();
        }
    }
}
