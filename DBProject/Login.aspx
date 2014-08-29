<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Login.aspx.cs" Inherits="RentalService.Login" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <asp:Login ID="Login_RS" runat="server" DestinationPageUrl="~/Home.aspx" OnAuthenticate="Login_RS_Authenticate" CreateUserText="註冊" CreateUserUrl="~/Registration.aspx">
        </asp:Login>
        <br />
    
    </div>
    </form>
</body>
</html>
