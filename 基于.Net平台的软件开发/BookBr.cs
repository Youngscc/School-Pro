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
    public partial class BookBr : Form
    {

        MySqlConnection sqlconn;
        MySqlDataAdapter adapter;
        DataSet myds;
        public static string conn = "Database=bookmagr;Data Source=127.0.0.1;User Id=root;Password=12345;pooling=false;CharSet=utf8;port=3306";
        public BookBr()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            sqlconn = new MySqlConnection(conn);
            sqlconn.Open();

            String sql = "UPDATE book SET available=0 WHERE idbook=" + BookID.Text + ";";
            //MessageBox.Show(sql);
            adapter = new MySqlDataAdapter(new MySqlCommand(sql, sqlconn));
            new MySqlCommandBuilder(adapter);

            myds = new DataSet();

            adapter.Fill(myds, "book");


            sql = "INSERT INTO borrow VALUE(\"" + User.USERID + "\"," + BookID.Text + ");";
            adapter = new MySqlDataAdapter(new MySqlCommand(sql, sqlconn));
            new MySqlCommandBuilder(adapter);

            myds = new DataSet();

            adapter.Fill(myds, "borrow");

            sqlconn.Close();
            MessageBox.Show("借阅成功", "提示");
        }
    }
}
