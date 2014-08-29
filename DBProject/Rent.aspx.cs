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
    public partial class Rent : System.Web.UI.Page
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
                try
                {
                    sql_cn.Open();

                    s_sql_query = "SELECT Property.Name 'PropertyName', RentalGroup.Name 'GroupName', RentalRecord.Count, RentalRecord.Status, RentalRecord.RentDate, RentalRecord.ReturnDate "
                        + "FROM RentalRecord, Property, RentalGroup "
                        + "WHERE RentalRecord.MID = @RentalRecord_MID AND Property.PID = RentalRecord.PID AND RentalGroup.GID = Property.GID ";
                    sql_da = new SqlDataAdapter(s_sql_query, sql_cn);
                    sql_da.SelectCommand.Parameters.AddWithValue("@RentalRecord_MID", s_MID);
                    sql_da.Fill(ds, "History");
                    GV_History.DataSource = ds.Tables["History"];
                    GV_History.DataBind();

                    sql_cn.Close();
                }
                catch (Exception excp)
                {
                    Response.Write(excp.ToString());
                }

                if (!IsPostBack)
                {
                    try
                    {
                        sql_cn.Open();

                        s_sql_query = "SELECT School.* FROM School";
                        sql_da = new SqlDataAdapter(s_sql_query, sql_cn);
                        sql_da.Fill(ds, "School");
                        DDL_School.DataSource = ds.Tables["School"];
                        DDL_School.DataTextField = ds.Tables["School"].Columns["Name"].ToString();
                        DDL_School.DataValueField = ds.Tables["School"].Columns["SID"].ToString();
                        DDL_School.DataBind();

                        s_sql_query = "SELECT Member.* FROM Member WHERE Member.MID = @Member_MID";
                        sql_cmd = new SqlCommand(s_sql_query, sql_cn);
                        sql_cmd.Parameters.AddWithValue("@Member_MID", s_MID);
                        sql_dr = sql_cmd.ExecuteReader();
                        sql_dr.Read();
                        DDL_School.SelectedValue = sql_dr["SID"].ToString();
                        //DDL_School.Items.FindByValue(sql_dr["SID"].ToString()).Selected = true;
                        sql_dr.Close();


                        s_sql_query = "SELECT RentalGroup.* FROM RentalGroup WHERE RentalGroup.SID = @RentalGroup_SID";
                        sql_da = new SqlDataAdapter(s_sql_query, sql_cn);
                        sql_da.SelectCommand.Parameters.AddWithValue("@RentalGroup_SID", DDL_School.SelectedValue);
                        sql_da.Fill(ds, "Group");
                        DDL_Group.DataSource = ds.Tables["Group"];
                        DDL_Group.DataTextField = ds.Tables["Group"].Columns["Name"].ToString();
                        DDL_Group.DataValueField = ds.Tables["Group"].Columns["GID"].ToString();
                        DDL_Group.DataBind();
                        DDL_Group.Items.Insert(0, new ListItem("Select Group", "-1"));

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

        protected void DDL_School_SelectedIndexChanged(object sender, EventArgs e)
        {

                try
                {
                    sql_cn.Open();

                    s_sql_query = "SELECT RentalGroup.* FROM RentalGroup WHERE RentalGroup.SID = @RentalGroup_SID";
                    sql_da = new SqlDataAdapter(s_sql_query, sql_cn);
                    sql_da.SelectCommand.Parameters.AddWithValue("@RentalGroup_SID", DDL_School.SelectedValue);
                    sql_da.Fill(ds, "Group");
                    DDL_Group.DataSource = ds.Tables["Group"];
                    DDL_Group.DataTextField = ds.Tables["Group"].Columns["Name"].ToString();
                    DDL_Group.DataValueField = ds.Tables["Group"].Columns["GID"].ToString();
                    DDL_Group.DataBind();
                    DDL_Group.Items.Insert(0, new ListItem("Select Group", "-1"));

                    sql_cn.Close();
                }
                catch (Exception excp)
                {
                    Response.Write(excp.ToString());
                }

        }

        protected void btn_Search_Click(object sender, EventArgs e)
        {

                try
                {
                    sql_cn.Open();

                    s_sql_query = "SELECT Property.* FROM Property WHERE Property.GID = @Property_GID";
                    sql_da = new SqlDataAdapter(s_sql_query, sql_cn);
                    sql_da.SelectCommand.Parameters.AddWithValue("@Property_GID", DDL_Group.SelectedValue);
                    sql_da.Fill(ds, "Property");
                    GV_Search.DataSource = ds.Tables["Property"];
                    string[] DKN = {"PID"};
                    GV_Search.DataKeyNames = DKN;
                    GV_Search.DataBind();

                    sql_cn.Close();
                }
                catch (Exception excp)
                {
                    Response.Write(excp.ToString());
                }

        }

        protected void GV_Search_SelectedIndexChanged(object sender, EventArgs e)
        {

                TB_PropertyCount.Text = "0";
                TB_ReturnDate.Text = "";
                try
                {
                    sql_cn.Open();

                    s_sql_query = "SELECT Property.* FROM Property WHERE Property.PID = @Property_PID";
                    sql_cmd = new SqlCommand(s_sql_query, sql_cn);
                    sql_cmd.Parameters.AddWithValue("@Property_PID", GV_Search.SelectedValue);
                    sql_dr = sql_cmd.ExecuteReader();
                    sql_dr.Read();
                    TB_PropertyName.Text = sql_dr["Name"].ToString();
                    sql_dr.Close();

                    s_sql_query = "SELECT GETDATE()";
                    sql_cmd = new SqlCommand(s_sql_query, sql_cn);
                    sql_dr = sql_cmd.ExecuteReader();
                    sql_dr.Read();
                    DateTime dt_now = sql_dr.GetDateTime(0);
                    sql_dr.Close();

                    DDL_RentDate.Items.Clear();
                    DDL_RentDate.Items.Add(new ListItem("Select Date", "-1"));
                    for (int i = 0; i < 7; i++)
                    {
                        DDL_RentDate.Items.Add(new ListItem(dt_now.AddDays(i).AddHours(-dt_now.Hour).AddMinutes(-dt_now.Minute).ToString("D"), dt_now.AddDays(i).AddHours(-dt_now.Hour).AddMinutes(-dt_now.Minute).ToString("f")));
                    }

                    sql_cn.Close();
                }
                catch (Exception excp)
                {
                    Response.Write(excp.ToString());
                }

        }

        protected void GV_Search_RowDataBound(object sender, GridViewRowEventArgs e)
        {
            e.Row.Cells[e.Row.Cells.Count - ds.Tables["Property"].Columns.Count + ds.Tables["Property"].Columns.IndexOf("PID")].Visible = false;
            e.Row.Cells[e.Row.Cells.Count - ds.Tables["Property"].Columns.Count + ds.Tables["Property"].Columns.IndexOf("GID")].Visible = false;
        }

        protected void DDL_RentDate_SelectedIndexChanged(object sender, EventArgs e)
        {
            DDL_Time.Items.Clear();
            DDL_RentDays.Items.Clear();

            if (DDL_RentDate.SelectedValue != "-1")
            {
                DateTime dt_RentDate = DateTime.Parse(DDL_RentDate.SelectedValue);

                DDL_Time.Items.Add(new ListItem("Select Time", "0"));
                for (int i = 0; i < 24; i++)
                {
                    DDL_Time.Items.Add(new ListItem(dt_RentDate.AddHours(i).ToString("t"), dt_RentDate.AddHours(i).ToString()));
                }

                DateTime dt_Latest = DateTime.Parse(DDL_RentDate.Items[7].Value);

                for (int i = 0; i <= dt_Latest.Subtract(dt_RentDate).Days; i++)
                {
                    DDL_RentDays.Items.Add(new ListItem(i.ToString(), i.ToString()));
                }
            }

        }

        protected void DDL_RentDays_SelectedIndexChanged(object sender, EventArgs e)
        {
            DateTime dt_ReturnDate = DateTime.Parse(DDL_Time.SelectedValue);
            TB_ReturnDate.Text = dt_ReturnDate.AddDays(Convert.ToDouble(DDL_RentDays.SelectedValue)).AddHours(Convert.ToDouble(DDL_Hours.SelectedValue)).ToString("f");
        }

        protected void DDL_Hours_SelectedIndexChanged(object sender, EventArgs e)
        {
            DateTime dt_ReturnDate = DateTime.Parse(DDL_Time.SelectedValue);
            TB_ReturnDate.Text = dt_ReturnDate.AddDays(Convert.ToDouble(DDL_RentDays.SelectedValue)).AddHours(Convert.ToDouble(DDL_Hours.SelectedValue)).ToString("f");
        }

        protected void DDL_Time_SelectedIndexChanged(object sender, EventArgs e)
        {
            DDL_Hours.Items.Clear();
            if (DDL_RentDate.SelectedValue != "0" && DDL_Time.SelectedValue != "0")
            {
                DateTime dt_Time = DateTime.Parse(DDL_Time.SelectedValue);
                for (int i = 0; i < 24 - dt_Time.Hour; i++)
                {
                    DDL_Hours.Items.Add(new ListItem(i.ToString(), i.ToString()));
                }
            }

        }

        protected void TB_PropertyCount_TextChanged(object sender, EventArgs e)
        {
            try
            {
                sql_cn.Open();

                s_sql_query = "SELECT Property.* FROM Property WHERE Property.PID = @Property_PID";
                sql_cmd = new SqlCommand(s_sql_query, sql_cn);
                sql_cmd.Parameters.AddWithValue("@Property_PID", GV_Search.SelectedValue);
                sql_dr = sql_cmd.ExecuteReader();
                sql_dr.Read();
                int PropertyCount = Convert.ToInt32(sql_dr["Count"].ToString());
                sql_dr.Close();

                s_sql_query = "SELECT SUM(RentalRecord.Count) FROM RentalRecord WHERE RentalRecord.PID = @RentalRecord_PID AND RentalRecord.Status = 'V'";
                sql_cmd = new SqlCommand(s_sql_query, sql_cn);
                sql_cmd.Parameters.AddWithValue("@RentalRecord_PID", GV_Search.SelectedValue);
                sql_dr = sql_cmd.ExecuteReader();
                int LendCount = 0;
                sql_dr.Read();
                if (sql_dr[0].ToString() != "")
                {
                    LendCount = Convert.ToInt32(sql_dr[0].ToString());
                }

                if (Convert.ToInt32(TB_PropertyCount.Text) < 0)
                {
                    TB_PropertyCount.Text = "0";
                }
                else
                    if (Convert.ToInt32(TB_PropertyCount.Text) > PropertyCount - LendCount)
                    {
                        TB_PropertyCount.Text = (PropertyCount - LendCount).ToString();
                    }
                sql_dr.Close();

                sql_cn.Close();
            }
            catch (Exception excp)
            {
                Response.Write(excp.ToString());
            }
        }

        protected void btn_Rent_Click(object sender, EventArgs e)
        {
            try
            {
                sql_cn.Open();

                s_sql_query = "INSERT INTO RentalRecord (MID, PID, Count, RentDate, ReturnDate, Status) VALUES (@MID, @PID, @Count, @RentDate, @ReturnDate, @Status)";
                sql_cmd = new SqlCommand(s_sql_query, sql_cn);
                /*
                sql_cmd.Parameters.Add("@MID", SqlDbType.Int);
                sql_cmd.Parameters.Add("@PID", SqlDbType.Int);
                sql_cmd.Parameters.Add("@Count", SqlDbType.Int);
                sql_cmd.Parameters.Add("@RentDate", SqlDbType.DateTime);
                sql_cmd.Parameters.Add("@ReturnDate", SqlDbType.DateTime);
                sql_cmd.Parameters.Add("@Status", SqlDbType.Char, 4);
                sql_cmd.Parameters["@MID"].Value = Convert.ToInt32(s_MID);
                sql_cmd.Parameters["@PID"].Value = Convert.ToInt32(GV_Search.SelectedValue.ToString());
                sql_cmd.Parameters["@Count"].Value = Convert.ToInt32(TB_PropertyCount.Text);
                sql_cmd.Parameters["@RentDate"].Value = DateTime.Parse(DDL_Time.SelectedValue);
                sql_cmd.Parameters["@ReturnDate"].Value = DateTime.Parse(TB_ReturnDate.Text);
                sql_cmd.Parameters["@Status"].Value = "UV";
                 */
                sql_cmd.Parameters.AddWithValue("@MID", s_MID);
                sql_cmd.Parameters.AddWithValue("@PID", GV_Search.SelectedValue);
                sql_cmd.Parameters.AddWithValue("@Count", TB_PropertyCount.Text);
                sql_cmd.Parameters.AddWithValue("@RentDate", DateTime.Parse(DDL_Time.SelectedValue));
                sql_cmd.Parameters.AddWithValue("@ReturnDate", DateTime.Parse(TB_ReturnDate.Text));
                sql_cmd.Parameters.AddWithValue("@Status", "UV");
                sql_cmd.ExecuteNonQuery();

                sql_cn.Close();
            }
            catch (Exception excp)
            {
                Response.Write(excp.ToString());
            }
        }

        protected void btn_ShowTables_Click(object sender, EventArgs e)
        {
            try
            {
                sql_cn.Open();

                s_sql_query = "SELECT RentalRecord.* FROM RentalRecord";
                sql_da = new SqlDataAdapter(s_sql_query, sql_cn);
                sql_da.Fill(ds, "RentalRecord");
                GV_RentalRecord.DataSource = ds.Tables["RentalRecord"];
                GV_RentalRecord.DataBind();

                sql_cn.Close();
            }
            catch (Exception excp)
            {
                Response.Write(excp.ToString());
            }
        }

        protected void DDL_Group_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                TB_PropertyName.Text = "";
                sql_cn.Open();

                s_sql_query = "SELECT Property.* FROM Property WHERE Property.GID = @Property_GID";
                sql_da = new SqlDataAdapter(s_sql_query, sql_cn);
                sql_da.SelectCommand.Parameters.AddWithValue("@Property_GID", DDL_Group.SelectedValue);
                sql_da.Fill(ds, "Property");
                GV_Search.DataSource = ds.Tables["Property"];
                string[] DKN = { "PID" };
                GV_Search.DataKeyNames = DKN;
                GV_Search.DataBind();

                sql_cn.Close();
            }
            catch (Exception excp)
            {
                Response.Write(excp.ToString());
            }
        }

    }
}