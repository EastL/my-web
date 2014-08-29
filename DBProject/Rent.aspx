<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Rent.aspx.cs" Inherits="RentalService.Rent" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <asp:Label ID="L_School" runat="server" Text="School"></asp:Label>
        <asp:DropDownList ID="DDL_School" runat="server" AutoPostBack="True" OnSelectedIndexChanged="DDL_School_SelectedIndexChanged">
        </asp:DropDownList>
        <asp:Label ID="L_Group" runat="server" Text="Group"></asp:Label>
        <asp:DropDownList ID="DDL_Group" runat="server" AutoPostBack="True" OnSelectedIndexChanged="DDL_Group_SelectedIndexChanged">
        </asp:DropDownList>
        <asp:Button ID="btn_Search" runat="server" Height="21px" OnClick="btn_Search_Click" Text="Search" Width="48px" />
        <br />
        <br />
        <asp:GridView ID="GV_Search" runat="server" OnSelectedIndexChanged="GV_Search_SelectedIndexChanged" OnRowDataBound="GV_Search_RowDataBound">
            <Columns>
                <asp:CommandField ButtonType="Button" ShowSelectButton="True" />
            </Columns>
        </asp:GridView>
        <br />
        <asp:Label ID="L_PropertyName" runat="server" Text="Name"></asp:Label>
        <asp:TextBox ID="TB_PropertyName" runat="server" ReadOnly="True"></asp:TextBox>
        <asp:Label ID="L_PropertyCount" runat="server" Text="Count"></asp:Label>
        <asp:TextBox ID="TB_PropertyCount" runat="server" AutoPostBack="True" OnTextChanged="TB_PropertyCount_TextChanged" TextMode="Number"></asp:TextBox>
        <asp:Label ID="L_RentDate" runat="server" Text="RentDate"></asp:Label>
        <asp:DropDownList ID="DDL_RentDate" runat="server" AutoPostBack="True" OnSelectedIndexChanged="DDL_RentDate_SelectedIndexChanged">
        </asp:DropDownList>
        <asp:Label ID="L_Time" runat="server" Text="Time"></asp:Label>
        <asp:DropDownList ID="DDL_Time" runat="server" AutoPostBack="True" OnSelectedIndexChanged="DDL_Time_SelectedIndexChanged">
        </asp:DropDownList>
        <asp:Label ID="L_RentDays" runat="server" Text="RentDays"></asp:Label>
        <asp:DropDownList ID="DDL_RentDays" runat="server" AutoPostBack="True" OnSelectedIndexChanged="DDL_RentDays_SelectedIndexChanged">
        </asp:DropDownList>
        <asp:Label ID="L_Hours" runat="server" Text="Hours"></asp:Label>
        <asp:DropDownList ID="DDL_Hours" runat="server" AutoPostBack="True" OnSelectedIndexChanged="DDL_Hours_SelectedIndexChanged">
        </asp:DropDownList>
        <asp:Label ID="L_ReturnDate" runat="server" Text="ReturnDate"></asp:Label>
        <asp:TextBox ID="TB_ReturnDate" runat="server" ReadOnly="True"></asp:TextBox>
        <asp:Button ID="btn_Rent" runat="server" Text="Rent" OnClick="btn_Rent_Click" />
        <br />
        <br />
        <asp:GridView ID="GV_History" runat="server">
        </asp:GridView>
        <br />
        <br />
        <asp:Button ID="btn_ShowTables" runat="server" OnClick="btn_ShowTables_Click" Text="ShowTables" />
        <br />
        <asp:GridView ID="GV_RentalRecord" runat="server">
        </asp:GridView>
        <br />
        <br />
    
    </div>
    </form>
</body>
</html>
