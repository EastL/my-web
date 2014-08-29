<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="GridViewTest.aspx.cs" Inherits="RentalService.GridViewTest" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <asp:GridView ID="GV_Test" runat="server" OnRowCancelingEdit="GV_Test_RowCancelingEdit" OnRowEditing="GV_Test_RowEditing" OnRowUpdating="GV_Test_RowUpdating">
            <Columns>
                <asp:CommandField ShowEditButton="True" />
            </Columns>
        </asp:GridView>
    
    </div>
    </form>
</body>
</html>
