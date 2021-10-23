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
    public partial class User : Form
    {
        public static string USERID;
        public User()
        {
            InitializeComponent();
        }

        private void User_Load(object sender, EventArgs e)
        {

        }


        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
        }

        public void button1_Click(object sender, EventArgs e)
        {

            MySqlConnection connection = new
 MySqlConnection("Database=bookmagr;Data Source=127.0.0.1;User Id=root;Password=12345;pooling=false;CharSet=utf8;port=3306");
            try
            {
                connection.Open();

                String sql = "select name,password from users where id='" + userName.Text + "'";
                MySqlCommand command = new MySqlCommand(sql, connection);
                MySqlDataReader reader = command.ExecuteReader();
                if (reader.Read())
                {
                    string str1 = reader.GetString(1);

                    if (str1 == userPW.Text)
                    {
                        MessageBox.Show("你好，" + reader.GetString(0) + "！");
                        USERID = userName.Text;
                        UserBench userBench = new UserBench();
                        if (userBench.ShowDialog() == DialogResult.OK) ;
                        else userBench.Close();
                        DialogResult = DialogResult.OK;
                        Close();
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
    }
}
