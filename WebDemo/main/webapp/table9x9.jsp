<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>

<head>
<meta charset="UTF-8">
<title>Multiplication Table</title>
</head>

<body>
	<table border="1">
		<%
		int rows = 10;
		int cols = 10;
		for (int x = 0; x < rows; x++)
		{
		%>
		<tr>
			<%
			for (int y = 0; y < cols; y++)
			{
			%>
			<td bgcolor="#eeeeee"><%=x%><%=" * "%><%=y%><%=" = "%><%=x * y%></td>
			<%
			}
			%>
		
		<tr>
			<%
			}
			%>
		
	</table>
</body>

</html>