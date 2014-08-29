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
    public partial class GridViewTest : System.Web.UI.Page
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

                        s_sql_query = "SELECT * FROM Member";
                        sql_cmd = new SqlCommand(s_sql_query, sql_cn);
                        /*
                        sql_da = new SqlDataAdapter(s_sql_query, sql_cn);
                        sql_da.Fill(ds, "Member");
                        GV_Test.DataSource = ds;
                        */
                        sql_dr = sql_cmd.ExecuteReader();
                        GV_Test.DataSource = sql_dr;
                        GV_Test.DataBind();

                        sql_cn.Close();
                    }
                    catch (Exception excp)
                    {
                        Response.Write(excp.ToString());
                    }
                }
            }
            else
                if (Session["MID"] == null)
                {
                    Response.Redirect("Login.aspx");
                }
        }

        protected void GV_Test_RowEditing(object sender, GridViewEditEventArgs e)
        {
            GV_Test.EditIndex = e.NewEditIndex;
            try
            {
                sql_cn.Open();

                s_sql_query = "SELECT * FROM Member";
                sql_da = new SqlDataAdapter(s_sql_query, sql_cn);
                sql_da.Fill(ds, "Member");
                GV_Test.DataSource = ds.Tables["Member"];
                GV_Test.DataBind();

                sql_cn.Close();
            }
            catch (Exception excp)
            {
                Response.Write(excp.ToString());
            }
        }

        protected void GV_Test_RowCancelingEdit(object sender, GridViewCancelEditEventArgs e)
        {
            GV_Test.EditIndex = -1;
            try
            {
                sql_cn.Open();

                s_sql_query = "SELECT * FROM Member";
                sql_da = new SqlDataAdapter(s_sql_query, sql_cn);
                sql_da.Fill(ds, "Member");
                GV_Test.DataSource = ds.Tables["Member"];
                GV_Test.DataBind();

                sql_cn.Close();
            }
            catch (Exception excp)
            {
                Response.Write(excp.ToString());
            }
        }

        protected void GV_Test_RowUpdating(object sender, GridViewUpdateEventArgs e)
        {
            try
            {
                sql_cn.Open();

                s_sql_query = "UPDATE Member SET Member.SID = @Member_SID, Member.UserName = @Member_UserName, Member.Password = @Member_Password, Member.Name = @Member_Name, Member.Email = @Member_Email, Member.id = @Member_id, Member.PhoneNumber = @Member_PhoneNumber WHERE Member.MID = @Member_MID";
                sql_cmd = new SqlCommand(s_sql_query, sql_cn);
                sql_cmd.Parameters.AddWithValue("@Member_MID", e.NewValues[0]);
                sql_cmd.Parameters.AddWithValue("@Member_SID", e.NewValues[1]);
                sql_cmd.Parameters.AddWithValue("@Member_UserName", e.NewValues[2]);
                sql_cmd.Parameters.AddWithValue("@Member_Password", e.NewValues[3]);
                sql_cmd.Parameters.AddWithValue("@Member_Name", e.NewValues[4]);
                sql_cmd.Parameters.AddWithValue("@Member_Email", e.NewValues[5]);
                sql_cmd.Parameters.AddWithValue("@Member_id", e.NewValues[6]);
                sql_cmd.Parameters.AddWithValue("@Member_PhoneNumber", e.NewValues[7]);
                sql_cmd.ExecuteNonQuery();

                sql_cn.Close();
            }
            catch (Exception excp)
            {
                Response.Write(excp.ToString());
            }
            GV_Test.EditIndex = -1;
            try
            {
                sql_cn.Open();

                s_sql_query = "SELECT * FROM Member";
                sql_da = new SqlDataAdapter(s_sql_query, sql_cn);
                sql_da.Fill(ds, "Member");
                GV_Test.DataSource = ds.Tables["Member"];
                GV_Test.DataBind();

                sql_cn.Close();
            }
            catch (Exception excp)
            {
                Response.Write(excp.ToString());
            }
        }
    }
}