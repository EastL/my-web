<%@ Page Title="" Language="C#" MasterPageFile="~/RentalService.Master" AutoEventWireup="true" CodeBehind="SlavePropertyControl.aspx.cs" Inherits="RentalService.SlavePropertyControl" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
            <div>
            <h1>財產管理</h1>
        </div>
        <div>
            <div>
               
                <asp:GridView ID="GV_PropertyNew" runat="server" OnRowCancelingEdit="GV_PropertyNew_RowCancelingEdit" OnRowDataBound="GV_PropertyNew_RowDataBound" OnRowDeleting="GV_PropertyNew_RowDeleting" OnRowEditing="GV_PropertyNew_RowEditing" OnRowUpdating="GV_PropertyNew_RowUpdating">
                    <Columns>
                        <asp:CommandField ShowEditButton="True" />
                        <asp:CommandField ShowDeleteButton="True" />
                    </Columns>
                </asp:GridView>
            </div>
            <div>
                <br />
                <asp:Label ID="lb_GName" runat="server" Text="所屬單位: "></asp:Label>
                <asp:DropDownList ID="ddl_GName" runat="server" AutoPostBack="True" AppendDataBoundItems="True">
                    <asp:ListItem Value="-1">---請選擇---</asp:ListItem>
                </asp:DropDownList>
                <br />
                <asp:Label ID="lb_PName" runat="server" Text="物件名稱: "></asp:Label>
                <asp:TextBox ID="txb_PName" runat="server"></asp:TextBox>
                <asp:Label ID="lb_Count" runat="server" Text="數量: "></asp:Label>
                <asp:TextBox ID="txb_Count" runat="server"></asp:TextBox>
                <asp:Label ID="lb_Price" runat="server" Text="價格: "></asp:Label>
                <asp:TextBox ID="txb_Price" runat="server"></asp:TextBox>
                <asp:Label ID="lb_Description" runat="server" Text="敘述: "></asp:Label>
                <asp:TextBox ID="txb_Description" runat="server"></asp:TextBox>
                <br />
                <br />
                <asp:Button ID="btn_AddData" runat="server" Text="新增資料" Width="75px" OnClick="btn_AddData_Click" />
            </div>
        </div>
        <div>
            <h1>租借許可</h1>
        </div>
        <div>
            <asp:GridView ID="gv_rent" runat="server" CellPadding="4" ForeColor="#333333" GridLines="None"
                OnRowDataBound="gv_rent_RowDataBound"
                OnRowCommand="gv_rent_RowCommand"
                AutoGenerateColumns="False">
                <Columns>
                    <asp:ButtonField ButtonType="Button" CommandName="Verify" HeaderText="確認租借" Text="確認" />
                    <asp:TemplateField HeaderText="租借單位">
                        <ItemTemplate>
                            <asp:Label ID="lb_RentGName" runat="server" Text='<%#Bind("租借單位") %> '></asp:Label>
                        </ItemTemplate>
                    </asp:TemplateField>
                    <asp:TemplateField HeaderText="租借財產">
                        <ItemTemplate>
                            <asp:Label ID="lb_RentPName" runat="server" Text='<%#Bind("租借財產") %> '></asp:Label>
                        </ItemTemplate>
                    </asp:TemplateField>
                    <asp:TemplateField HeaderText="租借數量">
                        <ItemTemplate>
                            <asp:Label ID="lb_RentCount" runat="server" Text='<%#Bind("租借數量") %> '></asp:Label>
                        </ItemTemplate>
                    </asp:TemplateField>
                    <asp:TemplateField HeaderText="租借日期">
                        <ItemTemplate>
                            <asp:Label ID="lb_RentDate" runat="server" Text='<%#Bind("租借日期") %> '></asp:Label>
                        </ItemTemplate>
                    </asp:TemplateField>
                    <asp:TemplateField HeaderText="歸還日期">
                        <ItemTemplate>
                            <asp:Label ID="lb_ReturnDate" runat="server" Text='<%#Bind("歸還日期") %> '></asp:Label>
                        </ItemTemplate>
                    </asp:TemplateField>
                    <asp:TemplateField HeaderText="RentPID" Visible="false">
                        <ItemTemplate>
                            <asp:Label ID="lb_RentPID" runat="server" Text='<%#Bind("RentPID") %> '></asp:Label>
                        </ItemTemplate>
                    </asp:TemplateField>
                    <asp:TemplateField HeaderText="物品狀態" Visible="false">
                        <ItemTemplate>
                            <asp:Label ID="lb_RentStatus" runat="server" Text='<%#Bind("物品狀態") %> '></asp:Label>
                        </ItemTemplate>
                    </asp:TemplateField>
                </Columns>
                <AlternatingRowStyle BackColor="White" />
                <FooterStyle BackColor="#990000" Font-Bold="True" ForeColor="White" />
                <HeaderStyle BackColor="#990000" Font-Bold="True" ForeColor="White" />
                <PagerStyle BackColor="#FFCC66" ForeColor="#333333" HorizontalAlign="Center" />
                <RowStyle BackColor="#FFFBD6" ForeColor="#333333" />
                <SelectedRowStyle BackColor="#FFCC66" Font-Bold="True" ForeColor="Navy" />
                <SortedAscendingCellStyle BackColor="#FDF5AC" />
                <SortedAscendingHeaderStyle BackColor="#4D0000" />
                <SortedDescendingCellStyle BackColor="#FCF6C0" />
                <SortedDescendingHeaderStyle BackColor="#820000" />
            </asp:GridView>
        </div>
</asp:Content>
