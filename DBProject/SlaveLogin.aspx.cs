using System;
using System.Collections.Generic;
using System.Linq;
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
    public partial class SlaveLogin : System.Web.UI.Page
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
            s_connection = @"Data Source=(LocalDB)\v11.0;AttachDbFilename=C:\Users\Eric\Desktop\MyRentalService\RentalService\App_Data\RentalDB.mdf;Integrated Security=True";
            sql_cn = new SqlConnection(s_connection);
            ds = new DataSet();

            UnobtrusiveValidationMode = UnobtrusiveValidationMode.None;//如果有用到驗證控制項 須加這行避免錯誤
            
            if (!IsPostBack)
            {
            }
        }

        protected void Login_RS_Authenticate(object sender, AuthenticateEventArgs e)
        {
            try
            {
                sql_cn.Open();//開啟連接

                s_sql_query = "SELECT * FROM Member WHERE Member.UserName = @Member_UserName AND Member.Password = @Member_Password";//用來找出登入者是否存在DB的SQL Query
                sql_cmd = new SqlCommand(s_sql_query, sql_cn);//執行SQL Query的物件
                sql_cmd.Parameters.AddWithValue("@Member_UserName", Login_RS.UserName);
                sql_cmd.Parameters.AddWithValue("@Member_Password", Login_RS.Password);
                sql_dr = sql_cmd.ExecuteReader();//讀取SQL Query執行結果的物件
                e.Authenticated = sql_dr.HasRows;//如果讀到的Row >= 1 身份驗證為true
                if (e.Authenticated)//身份驗證成功時 儲存使用者MID
                {
                    sql_dr.Read();//讀取一列資料
                    Session["MID"] = sql_dr["MID"];//將讀取到的MID存到 Session
                    //Server.Transfer("Home.aspx");
                    //Response.Redirect("Home.aspx");

                    //Response.Redirect("GridViewTest.aspx");
                    Response.Redirect("SlaveRent.aspx");
                }

                sql_cn.Close();//關閉連結
            }
            catch(Exception excp)
            {
               Login_RS.FailureText = excp.ToString();
            }
        }
    }
}