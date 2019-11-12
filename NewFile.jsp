<%@ page import ="java.sql.*" %> 
<%@ page import ="javax.sql.*" %> 
<% 
%>
<html>
<head>
<title>
execute asg2
</title>
</head>
<body bgcolor="pink">
<%
Class.forName("com.mysql.jdbc.Driver"); 

java.sql.Connection con = DriverManager.getConnection("jdbc:mysql://localhost/esdl","root","root"); 

Statement st= con.createStatement(); 


String act=request.getParameter("query1");
if(act.equals("b1"))
{ResultSet rs=st.executeQuery("select * from noplate"); 
	int j=rs.getMetaData().getColumnCount();
	%>
	<table border="1">
<%	while(rs.next())
{
 %>

<tr>
<%
for(int i=1;i<=j;i++)
{
%>
<td>	<%out.println(rs.getString(i)); %></td>


<% }
}%>

</table>
<%
}
%>
<% 
if(act.equals("b3"))
{ResultSet rs=st.executeQuery("select distinct title from book left outer join order1 on book.ISBN=order1.ISBN where qty is null"); 
	int j=rs.getMetaData().getColumnCount();
	%>
	<table border="1">
<%	while(rs.next())
{
 %>

<tr>
<%
for(int i=1;i<=j;i++)
{
%>
<td>	<%out.println(rs.getString(i)); %></td>


<% }
}%>

</table>
<%
}
%>
<% if(act.equals("b2"))
{String act11=request.getParameter("text1");
out.println(act11);
String act22="select b.plateno,a.state_name,a.city_name from stateeandcity a,ourdata b where b.state_code=a.state_code and b.city_code=a.city_code and b.plateno='"+act11+"';";
	ResultSet rs=st.executeQuery(act22); 
int j=rs.getMetaData().getColumnCount();
%>
<table border="1">
<%	while(rs.next())
{
%>

<tr>
<%
for(int i=1;i<=j;i++)
{
%>
<td>	<%out.println(rs.getString(i)); %></td>


<% }
}%>

</table>
<%
}
%>

<% if(act.equals("b4"))
{String act1=request.getParameter("carlist");
String act2=request.getParameter("carlist2");
out.println(act2);
String act4="VEHICLES OF THE SELECTED TYPES ARE:-";
String act3="select a.plateno from ourdata a,noplate b where a.plateno=b.plateno and b.plate_color='"+act1+"' and b.type='"+act2+"';";

ResultSet rs=st.executeQuery(act3); 
int j=rs.getMetaData().getColumnCount();
%>
<table border="1">
<%	while(rs.next())
{
%>

<tr>
<%
for(int i=1;i<=j;i++)
{
%>
<td>	<%out.println(rs.getString(i)); %></td>


<% }
}%>

</table>
<%
}
%>




<% if(act.equals("b5"))
{
	String str1=request.getParameter("text5");
	out.println(str1);
	String str2=" select b.plateno,a.owner_name,a.owner_phone,a.owner_address from owner a,ourdata b,noplate c where b.plateno=c.plateno and c.owner_id=a.owner_id and b.plateno='"+str1+"';";

	ResultSet rs=st.executeQuery(str2); 
int j=rs.getMetaData().getColumnCount();
%>
<table border="1">
<%	while(rs.next())
{
%>

<tr>
<%
for(int i=1;i<=j;i++)
{
%>
<td>	<%out.println(rs.getString(i)); %></td>


<% }
}%>

</table>
<%
}
%>






<% if(act.equals("b6"))
{
	
	String str2=" select state_name,count(ourdata.state_code) from ourdata natural join stateeandcity  group by(ourdata.state_code);";

	ResultSet rs=st.executeQuery(str2); 
int j=rs.getMetaData().getColumnCount();
%>
<table border="1">
<%	while(rs.next())
{
%>

<tr>
<%
for(int i=1;i<=j;i++)
{
%>
<td>	<%out.println(rs.getString(i)); %></td>


<% }
}%>

</table>
<%
}
%>



<% if(act.equals("b7"))
{
	String act71=request.getParameter("text71");
	String act72=request.getParameter("text72");
	String str2="select count(a.plateno)/count(distinct(a.record_date)) from ourdata a where a.record_date >'"+act71+"' and a.record_date <'"+act72+"';";

	ResultSet rs=st.executeQuery(str2); 
int j=rs.getMetaData().getColumnCount();
%>
<table border="1">
<%	while(rs.next())
{
%>

<tr>
<%
for(int i=1;i<=j;i++)
{
%>
<td>	<%out.println(rs.getString(i)); %></td>


<% }
}%>

</table>
<%
}
%>