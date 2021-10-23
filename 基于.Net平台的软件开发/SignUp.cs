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
    public partial class SignUp : Form
    {
        MySqlConnection sqlconn;
        MySqlDataAdapter adapter;
        DataSet myds;
        public static string conn = "Database=bookmagr;Data Source=127.0.0.1;User Id=root;Password=12345;pooling=false;CharSet=utf8;port=3306";
        public SignUp()
        {
            InitializeComponent();
        }

        private void SignUp_Load(object sender, EventArgs e)
        {
            
        }

        private void btOK_Click(object sender, EventArgs e)
        {
            if (insPW.Text != insPW2.Text)
            {
                MessageBox.Show("两次输入的密码不一致，请重新输入","提示");
            }
            else
            {
                int isit = 0;
                if (checkBox1.Checked) isit = 1; 
                string query = "INSERT INTO users VALUE(\""+insID.Text+"\",\""+insName.Text+"\","+isit+","+insPW.Text+");";
                sqlconn = new MySqlConnection(conn);
                sqlconn.Open();

                adapter = new MySqlDataAdapter(new MySqlCommand(query, sqlconn));
                new MySqlCommandBuilder(adapter);

                myds = new DataSet();

                adapter.Fill(myds, "users");
                sqlconn.Close();

                DialogResult = DialogResult.Cancel;
                MessageBox.Show("注册成功", "提示");
            }
        }

        private void btCancel_Click(object sender, EventArgs e)
        {
            sqlconn.Close();
            DialogResult = DialogResult.Cancel;
        }
    }
}
