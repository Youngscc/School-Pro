using MySql.Data.MySqlClient;
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
    public partial class BookIns : Form
    {
        MySqlConnection sqlconn;
        MySqlDataAdapter adapter;
        DataSet myds;
        public static string conn = "Database=bookmagr;Data Source=127.0.0.1;User Id=root;Password=12345;pooling=false;CharSet=utf8;port=3306";
        public BookIns()
        {
            InitializeComponent();
        }

        private void btOK_Click(object sender, EventArgs e)
        {
            string query = "INSERT INTO book VALUE(\"" + InsID.Text + "\",\"" + InsName.Text + "\",1);";
            sqlconn = new MySqlConnection(conn);
            sqlconn.Open();

            adapter = new MySqlDataAdapter(new MySqlCommand(query, sqlconn));
            new MySqlCommandBuilder(adapter);

            myds = new DataSet();

            adapter.Fill(myds, "book");
            sqlconn.Close();

            DialogResult = DialogResult.Cancel;
            MessageBox.Show("录入《"+ InsName.Text + "》成功", "提示");
        }

        private void btCancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
        }
    }
}
