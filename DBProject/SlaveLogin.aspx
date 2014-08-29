<%@ Page Title="" Language="C#" MasterPageFile="~/RentalService.Master" AutoEventWireup="true" CodeBehind="SlaveLogin.aspx.cs" Inherits="RentalService.SlaveLogin" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
    <style type="text/css">
        .auto-style2 {
            width: 1051px;
        }
        .auto-style6 {
            width: 349px;
        }
        .auto-style7 {
            width: 350px;
        }
        .auto-style8 {
            width: 349px;
            height: 19px;
        }
        .auto-style9 {
            width: 350px;
            height: 19px;
        }
    </style>
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div>
    
        <table class="auto-style2">
            <tr>
                <td class="auto-style6">&nbsp;</td>
                <td class="auto-style7">&nbsp;</td>
                <td class="auto-style7">&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style6">&nbsp;</td>
                <td class="auto-style7">
    
        <asp:Login ID="Login_RS" runat="server" DestinationPageUrl="~/SlaveHome.aspx" OnAuthenticate="Login_RS_Authenticate" CreateUserText="註冊" style="text-align: left">
        </asp:Login>
                </td>
                <td class="auto-style7">&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style8"></td>
                <td class="auto-style9"></td>
                <td class="auto-style9"></td>
            </tr>
        </table>
        <br />
    
    </div>
</asp:Content>
