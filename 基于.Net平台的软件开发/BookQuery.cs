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
    public partial class BookQuery : Form
    {
        public BookQuery()
        {
            InitializeComponent();
        }

        private void btOK_Click(object sender, EventArgs e)
        {
            MySqlConnection connection = new
 MySqlConnection("Database=bookmagr;Data Source=127.0.0.1;User Id=root;Password=12345;pooling=false;CharSet=utf8;port=3306");
            try
            {
                connection.Open();

                String sql = "select name,available from book where idbook='" + txID.Text + "'";
                MySqlCommand command = new MySqlCommand(sql, connection);
                MySqlDataReader reader = command.ExecuteReader();
                if (reader.Read())
                {
                    string str1 = reader.GetString(0);
                    int ok = reader.GetInt32(1);
                    if (ok == 1) MessageBox.Show("您查询的图书《" + str1 + "》可供借阅");
                    else MessageBox.Show("您查询的图书《" + str1 + "》已被借阅");
                }
                else MessageBox.Show("未查询到该图书", "错误");
            }
            catch (MySqlException ee)
            {
                Console.WriteLine(ee.Message);
            }
            finally
            {
                connection.Close();
            }
        }
    }
}
