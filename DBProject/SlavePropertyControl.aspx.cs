using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;    // SqlConnection SqlCommend SqlDataAdapter
using System.Data;              // DataSet

namespace RentalService
{
    public partial class SlavePropertyControl : System.Web.UI.Page
    {
        SqlConnection sql_connection = new SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=C:\Users\user\Desktop\MyRentalService\RentalService\App_Data\RentalDB.mdf;Integrated Security=True");
        SqlDataAdapter sql_adapter = new SqlDataAdapter();
        SqlCommand sql_cmd = new SqlCommand();
        DataSet g_ds = new DataSet();

        protected void Page_Load(object sender, EventArgs e)
        {
            UnobtrusiveValidationMode = UnobtrusiveValidationMode.None;//如果有用到驗證控制項 須加這行避免錯誤
            Page.MaintainScrollPositionOnPostBack = true;   // PostBack後停留在原畫面
            if (Session["MID"] != null)
            {
                VerifyPermission();

                if (!IsPostBack)
                {
                    /*
                     * Page Load 後，SetData2DDL會將該帳號所參加的所有社團記錄到g_ds.Tables["GroupName"]
                     * 包含：GroupName, GID
                     */
                    SetData2DDL();
                    SetData2GV_PropertyNew();
                    SetData2gv_rent();
                }

            }
            else
            {
                Response.Redirect("SlaveLogin.aspx");
            }
        }

        /*
         * load data to gridview and DropDownList
         */
        protected void VerifyPermission()
        {
            string QueryPermission = "SELECT GM.Permission FROM GM WHERE " + Session["MID"].ToString() + " = GM.MID and GM.Permission >= ( " +
                                     "SELECT RG.ControlPermission FROM RentalGroup RG WHERE " + Session["MID"].ToString() + " = GM.MID and GM.GID = RG.GID )";
            g_ds = GetData(QueryPermission, "ControlPermission");
            if (g_ds.Tables.Count == 1 && g_ds.Tables["ControlPermission"].Rows.Count == 0) // dataset 中的 table 沒有資料時跳回首頁
            {
                Response.Write("<script>alert('您沒有權限執行此功能');location.href='SlaveHome.aspx';</script>");
            }
        }
        protected void SetData2GV_PropertyNew()
        {
            // Declare the query string, and it won't show GID
            string querystring = @"Select RentalGroup.Name '所屬單位', Property.Name '物件名稱', Count '數量', Price '價格', Description '敘述', Property.PID, Property.GID
                                   From GM, RentalGroup, Property 
                                   Where GM.GID = RentalGroup.GID and GM.MID = " + Session["MID"].ToString() + " and GM.GID = Property.GID Order by RentalGroup.Name, Count";

            // run the query and bind the resulting dataset to gridview  control
            g_ds = GetData(querystring, "Total");
            if (g_ds.Tables["Total"].Rows.Count > 0)
            {
                GV_PropertyNew.DataSource = g_ds.Tables["Total"];// 將 data set 里的資料載入到 gridview
                GV_PropertyNew.DataKeyNames = new string[] {"PID", "GID"};
                GV_PropertyNew.DataBind();
            }
            else
            { Response.Write("Unable to connect to the database."); }

        }
        protected void SetData2gv_rent()
        {
            string query = @"Select RentalGroup.Name '租借單位', Property.Name '租借財產', RentalRecord.Count '租借數量', RentalRecord.RentDate '租借日期', RentalRecord.ReturnDate '歸還日期', RentalRecord.PID 'RentPID', RentalRecord.Status '物品狀態'" +
                            "From RentalGroup, Property, RentalRecord, GM " +
                            "Where GM.GID = RentalGroup.GID and GM.MID = " + Session["MID"].ToString() + " and GM.GID = Property.GID and RentalRecord.Status = 'UV' and RentalRecord.PID = Property.PID Order by RentalGroup.Name, RentalRecord.Count";
            g_ds = GetData(query, "Rent");

            gv_rent.DataSource = g_ds.Tables["Rent"];
            gv_rent.DataBind();

        }
        protected void SetData2DDL()
        {
            // Set the DropDownList in the PropertyControl
            string GNameQuery = @"Select RG.Name '所屬單位', RG.GID 'GID' " +
                                 "From GM, RentalGroup RG " +
                                 "Where " + Session["MID"].ToString() + " = GM.MID and GM.GID = RG.GID Order by RG.Name";
            g_ds = GetData(GNameQuery, "GroupName");
            ddl_GName.DataSource = g_ds.Tables["GroupName"];
            ddl_GName.DataTextField = g_ds.Tables["GroupName"].Columns["所屬單位"].ColumnName.ToString();
            ddl_GName.DataValueField = g_ds.Tables["GroupName"].Columns["GID"].ColumnName.ToString();
            ddl_GName.DataBind();
        }
        DataSet GetData(String queryString, String TableName)
        {
            DataSet ds = new DataSet();

            try
            {
                sql_adapter = new SqlDataAdapter(queryString, sql_connection);
                sql_adapter.Fill(ds, TableName);
            }
            catch (Exception ex)
            {
                // the connection failed. Display an error message 
                //Response.Write("Unable to connect to the database in the GetData. \n");
                Response.Write(ex.ToString());
            }
            return ds;
        }

        /*
         * 設定光棒效果 
         */
        private void SetLight(object sender, GridViewRowEventArgs e)
        {
            // Determine the row is data or not
            if (e.Row.RowType == DataControlRowType.DataRow)
            {
                int index = e.Row.RowIndex;
                // Change the background color when the mouse on the row
                e.Row.Attributes.Add("onmouseover", "c = this.style.backgroundColor;this.style.backgroundColor='#AAAAAA'");
                // Recovery the color when the mouse leave
                e.Row.Attributes.Add("onmouseout", "this.style.backgroundColor = c");
            }
        }
        protected void GV_PropertyNew_RowDataBound(object sender, GridViewRowEventArgs e)
        {
            e.Row.Cells[7].Visible = false;
            e.Row.Cells[8].Visible = false;
        }
        protected void gv_rent_RowDataBound(object sender, GridViewRowEventArgs e)
        {
            this.SetLight(sender, e);
        }

        /*
         * 編輯, 取消編輯
         */
        protected void GV_PropertyNew_RowEditing(object sender, GridViewEditEventArgs e)
        {
            this.GV_PropertyNew.EditIndex = e.NewEditIndex;
            SetData2GV_PropertyNew();
            this.GV_PropertyNew.DataBind();
        }
        protected void GV_PropertyNew_RowCancelingEdit(object sender, GridViewCancelEditEventArgs e)
        {
            this.GV_PropertyNew.EditIndex = -1;
            SetData2GV_PropertyNew();
            this.GV_PropertyNew.DataBind();
        }

        /*
         * 更新
         */
        protected void GV_PropertyNew_RowUpdating(object sender, GridViewUpdateEventArgs e)
        {
                Response.Write(e.NewValues[0].ToString());
                Response.Write(e.NewValues[1].ToString());
                Response.Write(e.NewValues[2].ToString());
                Response.Write(e.NewValues[3].ToString());
                Response.Write(e.NewValues[4].ToString());
                Response.Write(e.Keys[0].ToString());
                Response.Write(e.Keys[1].ToString());
            // Get the raw data
            // Trim: 將字串前後空格去掉
            //string str_PName, str_Count, str_Price, str_Description, str_PID;

            //str_PID = ((TextBox)GV_PropertyNew.Rows[e.RowIndex].Cells[0].FindControl("tx_EditPID")).Text;
            //str_PName = ((TextBox)GV_PropertyNew.Rows[e.RowIndex].Cells[0].FindControl("tx_EditPName")).Text;
            //str_Count = ((TextBox)GV_PropertyNew.Rows[e.RowIndex].Cells[0].FindControl("tx_EditCount")).Text;
            //str_Price = ((TextBox)GV_PropertyNew.Rows[e.RowIndex].Cells[0].FindControl("tx_EditPrice")).Text;
            //str_Description = ((TextBox)GV_PropertyNew.Rows[e.RowIndex].Cells[0].FindControl("tx_EditDescription")).Text;
            try
            {
                sql_connection.Open();
                sql_cmd.CommandText = "UPDATE Property SET GID = @GID, Name = @Name, Count = @Count, Price = @Price, Description = @Description WHERE PID = @PID";
                sql_cmd.Connection = sql_connection;

                sql_cmd.Parameters.Clear();
                // e.NewValue[0] = 所屬單位
                sql_cmd.Parameters.AddWithValue("@Name", e.NewValues[1]);
                sql_cmd.Parameters.AddWithValue("@Count", e.NewValues[2]);
                sql_cmd.Parameters.AddWithValue("@Price", e.NewValues[3]);
                sql_cmd.Parameters.AddWithValue("@Description", e.NewValues[4]);
                sql_cmd.Parameters.AddWithValue("@PID", e.Keys[0].ToString());
                sql_cmd.Parameters.AddWithValue("@GID", e.Keys[1].ToString());

                try { sql_cmd.ExecuteNonQuery(); }
                catch (Exception exc) { Response.Write(exc.ToString()); }
                sql_connection.Close();
            }
            catch (Exception ex) { Response.Write(ex.ToString()); }
            GV_PropertyNew.EditIndex = -1;

            SetData2GV_PropertyNew();
        }

        /*
         * 儲存新增資料, 取消儲存
         */



        /*
         * 新增
         */
        protected void btn_AddData_Click(object sender, EventArgs e)
        {
            //this.GV_PropertyNew.ShowFooter = true;
            //this.GV_PropertyNew.DataBind();
            string str_GName_GID, str_PName, str_Count, str_Price, str_Description;

            str_GName_GID = ddl_GName.SelectedValue.ToString();
            str_PName = txb_PName.Text;
            str_Count = txb_Count.Text;
            str_Price = txb_Price.Text;
            str_Description = txb_Description.Text;

            sql_cmd.CommandText = "INSERT INTO [Property] (GID, Name, Count, Price, Description)" +
                                  "VALUES (@GID, @Name, @Count, @Price, @Description)";
            sql_cmd.Connection = sql_connection;

            sql_cmd.Parameters.Clear();
            sql_cmd.Parameters.AddWithValue("@GID", str_GName_GID);
            sql_cmd.Parameters.AddWithValue("@Name", str_PName);
            sql_cmd.Parameters.AddWithValue("@Count", str_Count);
            sql_cmd.Parameters.AddWithValue("@Price", str_Price);
            sql_cmd.Parameters.AddWithValue("@Description", str_Description);

            sql_connection.Open();
            try
            {
                sql_cmd.ExecuteNonQuery();

                txb_PName.Text = "";
                txb_Count.Text = "";
                txb_Price.Text = "";
                txb_Description.Text = "";
            }
            catch (Exception ex)
            {
                Response.Write(ex.ToString());
            }
            SetData2GV_PropertyNew();
            sql_connection.Close();
        }

        /*
         * 刪除
         */
        protected void GV_PropertyNew_RowDeleting(object sender, GridViewDeleteEventArgs e)
        {
            // Verify the RentalRecord Table wheher have data

            // Delete

            sql_cmd.Connection = sql_connection;
            sql_cmd.Parameters.Clear();
            

            sql_cmd.CommandText = "DELETE FROM Property WHERE PID = @PID";
            sql_cmd.Parameters.AddWithValue("@PID", e.Keys[0].ToString());
            sql_connection.Open();
            try { sql_cmd.ExecuteNonQuery(); }
            catch (Exception ex) { ex.ToString(); }
            SetData2GV_PropertyNew();
            sql_connection.Close();
        }

        /*
         * 判斷btn_verify按鈕是否點擊
         */
        protected void gv_rent_RowCommand(object sender, GridViewCommandEventArgs e)
        {
            if (e.CommandName == "Verify")
            {
                // Get the RowIndex
                int index = Convert.ToInt32(e.CommandArgument.ToString());

                // Retrieve the Rows collection
                string PID = ((Label)gv_rent.Rows[index].FindControl("lb_RentPID")).Text;
                sql_cmd.CommandText = "UPDATE RentalRecord SET Status = 'V' WHERE PID = @PID";
                sql_cmd.Parameters.Clear();
                sql_cmd.Parameters.AddWithValue("@PID", PID);

                // Update
                sql_cmd.Connection = sql_connection;
                sql_connection.Open();
                try { sql_cmd.ExecuteNonQuery(); }
                catch (Exception ex) { ex.ToString(); }
                sql_connection.Close();

                SetData2gv_rent();
            }

        }
    }
}