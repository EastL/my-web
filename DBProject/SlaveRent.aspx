<%@ Page Title="" Language="C#" MasterPageFile="~/RentalService.Master" AutoEventWireup="true" CodeBehind="SlaveRent.aspx.cs" Inherits="RentalService.SlaveRent" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
    <style type="text/css">
        .Table_RentableAndRecord {
            width: 693px;
            height: 321px;
        }
        .Column_TB_RentDate {
            height: 51px;
    }
        .Column_Table_Rent {
            width: 527px;
        }
        .Column_Record {
            width: 349px;
        }
        .Column_L_School {
            width: 45px;
        }
    .Column_btn_Rent {
        width: 150px;
        height: 51px;
    }
    .Table_Rent {
        width: 650px;
        height: 172px;
        margin-left: 0px;
    }
    .Column_RentC1 {
        width: 80px;
        text-align: right;
        height: 39px;
    }
    .Column_RentC3 {
        width: 50px;
        text-align: right;
        height: 39px;
    }
    .Column_RentC4 {
        height: 39px;
    }
    .Column_RentC2 {
        width: 140px;
        height: 39px;
    }
        .Column_Rentable {
            width: 600px;
        }
    </style>
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div style="margin: 0px;">
    
        <br />
        <table class="Table_SearchAndRent">
            <tr>
                <td class="Column_L_School" style="text-align: right">
    
        <asp:Label ID="L_School" runat="server" Text="School"></asp:Label>
                </td>
                <td>
        <asp:DropDownList ID="DDL_School" runat="server" AutoPostBack="True" OnSelectedIndexChanged="DDL_School_SelectedIndexChanged">
        </asp:DropDownList>
                </td>
                <td style="text-align: right">
        <asp:Label ID="L_Group" runat="server" Text="Group"></asp:Label>
                </td>
                <td>
        <asp:DropDownList ID="DDL_Group" runat="server" AutoPostBack="True" OnSelectedIndexChanged="DDL_Group_SelectedIndexChanged">
        </asp:DropDownList>
                    <asp:RequiredFieldValidator ID="RFV_Group" runat="server" ControlToValidate="DDL_Group" ErrorMessage="Required Group" ForeColor="Red" ValidationGroup="VG_Rent" Display="Dynamic"></asp:RequiredFieldValidator>
                </td>
                <td>
        <asp:Button ID="btn_Search" runat="server" Height="21px" OnClick="btn_Search_Click" Text="Search" Width="50px" />
                </td>
                <td class="Column_Table_Rent">
                    <table class="Table_Rent">
                        <tr>
                            <td class="Column_RentC1">
        <asp:Label ID="L_PropertyName" runat="server" Text="Name"></asp:Label>
                            </td>
                            <td class="Column_RentC2">
        <asp:TextBox ID="TB_PropertyName" runat="server" ReadOnly="True" Width="120px" Height="20px"></asp:TextBox>
                                <asp:RequiredFieldValidator ID="RFV_PropertyName" runat="server" ControlToValidate="TB_PropertyName" ErrorMessage="Required Name" ForeColor="Red" ValidationGroup="VG_Rent" Display="Dynamic"></asp:RequiredFieldValidator>
                            </td>
                            <td class="Column_RentC3">
        <asp:Label ID="L_PropertyCount" runat="server" Text="Count"></asp:Label>
                            </td>
                            <td class="Column_RentC4" colspan="2">
        <asp:TextBox ID="TB_PropertyCount" runat="server" AutoPostBack="True" OnTextChanged="TB_PropertyCount_TextChanged" TextMode="Number" Width="120px" Height="20px"></asp:TextBox>
                                <asp:Label ID="L_Maximum" runat="server" ForeColor="Red" Text="Maximum"></asp:Label>
                            </td>
                        </tr>
                        <tr>
                            <td class="Column_RentC1">
        <asp:Label ID="L_RentDate" runat="server" Text="RentDate"></asp:Label>
                            </td>
                            <td class="Column_RentC2">
        <asp:DropDownList ID="DDL_RentDate" runat="server" AutoPostBack="True" OnSelectedIndexChanged="DDL_RentDate_SelectedIndexChanged" Height="25px" Width="120px">
        </asp:DropDownList>
                                <asp:RequiredFieldValidator ID="RFV_Date" runat="server" ControlToValidate="DDL_RentDate" ErrorMessage="Required Date" ForeColor="Red" ValidationGroup="VG_Rent" Display="Dynamic"></asp:RequiredFieldValidator>
                            </td>
                            <td class="Column_RentC3">
        <asp:Label ID="L_Time" runat="server" Text="Time"></asp:Label>
                            </td>
                            <td class="Column_RentC4" colspan="2">
        <asp:DropDownList ID="DDL_Time" runat="server" AutoPostBack="True" OnSelectedIndexChanged="DDL_Time_SelectedIndexChanged" Width="120px" Height="25px">
        </asp:DropDownList>
                                <asp:RequiredFieldValidator ID="RFV_Time" runat="server" ControlToValidate="DDL_Time" ErrorMessage="Required Time" ForeColor="Red" ValidationGroup="VG_Rent" Display="Dynamic"></asp:RequiredFieldValidator>
                            </td>
                        </tr>
                        <tr>
                            <td class="Column_RentC1">
        <asp:Label ID="L_RentDays" runat="server" Text="RentDays"></asp:Label>
                            </td>
                            <td class="Column_RentC2">
        <asp:DropDownList ID="DDL_RentDays" runat="server" AutoPostBack="True" OnSelectedIndexChanged="DDL_RentDays_SelectedIndexChanged" Width="120px" Height="25px">
        </asp:DropDownList>
                                <asp:RequiredFieldValidator ID="RFV_Days" runat="server" ControlToValidate="DDL_RentDays" ErrorMessage="Required Days" ForeColor="Red" ValidationGroup="VG_Rent" Display="Dynamic"></asp:RequiredFieldValidator>
                            </td>
                            <td class="Column_RentC3">
        <asp:Label ID="L_Hours" runat="server" Text="Hours"></asp:Label>
                            </td>
                            <td class="Column_RentC4" colspan="2">
        <asp:DropDownList ID="DDL_Hours" runat="server" AutoPostBack="True" OnSelectedIndexChanged="DDL_Hours_SelectedIndexChanged" Width="120px" Height="25px">
        </asp:DropDownList>
                                <asp:RequiredFieldValidator ID="RFV_Hours" runat="server" ControlToValidate="DDL_Hours" ErrorMessage="Required Hours" ForeColor="Red" ValidationGroup="VG_Rent" Display="Dynamic"></asp:RequiredFieldValidator>
                            </td>
                        </tr>
                        <tr>
                            <td class="Column_RentC1">
        <asp:Label ID="L_ReturnDate" runat="server" Text="ReturnDate"></asp:Label>
                            </td>
                            <td class="Column_TB_RentDate" colspan="2">
        <asp:TextBox ID="TB_ReturnDate" runat="server" ReadOnly="True" Width="160px" Height="20px"></asp:TextBox>
                                <asp:RequiredFieldValidator ID="RFV_ReturnDate" runat="server" ControlToValidate="TB_ReturnDate" ErrorMessage="Required Return Date" ForeColor="Red" ValidationGroup="VG_Rent">&nbsp;</asp:RequiredFieldValidator>
                            </td>
                            <td class="Column_btn_Rent">
        <asp:Button ID="btn_Rent" runat="server" Text="Rent" OnClick="btn_Rent_Click" ValidationGroup="VG_Rent" Width="120px" />
                            </td>
                            <td>
                                <asp:ValidationSummary ID="VS_Rent" runat="server" ForeColor="Red" ValidationGroup="VG_Rent" Width="160px" />
                            </td>
                        </tr>
                    </table>
                </td>
            </tr>
        </table>
        <table class="Table_RentableAndRecord">
            <tr>
                <td class="Column_Rentable">
                    <asp:Label ID="L_Rentable" runat="server" Text="Rentable"></asp:Label>
                </td>
                <td class="Column_Record">
                    <asp:Label ID="L_Record" runat="server" Text="Record"></asp:Label>
                </td>
            </tr>
            <tr>
                <td class="Column_Rentable">
        <asp:GridView ID="GV_Search" runat="server" OnSelectedIndexChanged="GV_Search_SelectedIndexChanged" OnRowDataBound="GV_Search_RowDataBound" AllowPaging="True" OnPageIndexChanging="GV_Search_PageIndexChanging">
            <Columns>
                <asp:CommandField ButtonType="Button" ShowSelectButton="True" />
            </Columns>
        </asp:GridView>
                </td>
                <td class="Column_Record">
        <asp:GridView ID="GV_History" runat="server" AllowPaging="True" OnPageIndexChanging="GV_History_PageIndexChanging">
        </asp:GridView>
                </td>
            </tr>
        </table>
        <br />
        <br />
        <br />
        <br />
        <asp:Button ID="btn_ShowTables" runat="server" OnClick="btn_ShowTables_Click" Text="ShowTables" Visible="False" />
        <br />
        <asp:GridView ID="GV_RentalRecord" runat="server">
        </asp:GridView>
        <br />
        <br />
    
    </div>
</asp:Content>
