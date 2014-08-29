using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Data.SqlClient;

namespace RentalService
{
    public partial class Home : System.Web.UI.Page
    {
        string s_connection;
        string s_sql_query;
        string s_MID;
        SqlConnection sql_cn;
        SqlCommand sql_cmd;
        SqlDataReader sql_dr;
        SqlDataAdapter sql_da;
        DataSet ds;

        protected void Page_Load(object sender, EventArgs e)
        {
            s_connection = @"Data Source=(LocalDB)\v11.0;AttachDbFilename=C:\Users\user\Desktop\MyRentalService\RentalService\App_Data\RentalDB.mdf;Integrated Security=True";
            sql_cn = new SqlConnection(s_connection);
            ds = new DataSet();

            if (Session["MID"] != null)//確認Session內是否存在MID
            {
                s_MID = Session["MID"].ToString();//取出MID
                if (!IsPostBack)
                {
                    try
                    {
                        sql_cn.Open();

                        s_sql_query = "SELECT * FROM Member WHERE Member.MID = " + s_MID;//取出該MID會員資料的SQL Query
                        sql_cmd = new SqlCommand(s_sql_query, sql_cn);
                        sql_dr = sql_cmd.ExecuteReader();
                        sql_dr.Read();
                        L_test.Text = "Welcome " + sql_dr["UserName"];//將會員名稱加入歡迎標語

                        sql_cn.Close();
                    }
                    catch (Exception excp)
                    {
                        L_test.Text = excp.ToString();
                    }
                }
            }
            else
                if (Session["MID"] == null)
                {
                    Response.Redirect("Login.aspx");
                }
        }
    }
}