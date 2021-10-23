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
    public partial class Admin : Form
    {
        public Admin()
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

                String sql = "select name,password,isAD from users where id='" + AdName.Text + "'";
                MySqlCommand command = new MySqlCommand(sql, connection);
                MySqlDataReader reader = command.ExecuteReader();
                if (reader.Read())
                {
                    string str1 = reader.GetString(1);

                    if (str1 == AdPW.Text)
                    {
                        if (reader.GetInt32(2) == 1)
                        {
                            MessageBox.Show("你好，" + reader.GetString(0) + "！");
                            DialogResult = DialogResult.OK;
                            AdminBench adminBench = new AdminBench();
                            if (adminBench.ShowDialog() == DialogResult.OK) ;
                            else adminBench.Close();
                        }
                        else MessageBox.Show("对不起，您没有权限","错误");
                        
                    }
                    else MessageBox.Show("用户名或密码错误，请重新输入", "错误");
                }
                else MessageBox.Show("用户名或密码错误，请重新输入", "错误");
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

        private void btCancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
        }
    }
}
