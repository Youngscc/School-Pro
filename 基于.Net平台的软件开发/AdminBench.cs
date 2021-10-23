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
    public partial class AdminBench : Form
    {
        public AdminBench()
        {
            InitializeComponent();
        }

        private void Drop_Click(object sender, EventArgs e)
        {
            DeleteBook deleteUser = new DeleteBook();
            if (deleteUser.ShowDialog() == DialogResult.OK) ;
            else deleteUser.Close();
        }

        private void BookIns_Click(object sender, EventArgs e)
        {
            BookIns bookIns = new BookIns();
            if (bookIns.ShowDialog() == DialogResult.OK) ;
            else bookIns.Close();
        }

        private void BookMgr_Click(object sender, EventArgs e)
        {
            BookQuery bookQuery = new BookQuery();
            if (bookQuery.ShowDialog() == DialogResult.OK) ;
            else bookQuery.Close();
        }

        private void AdminBench_Load(object sender, EventArgs e)
        {

        }
    }
}
