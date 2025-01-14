<%@ page contentType="text/html" pageEncoding="UTF-8"%>
<html>
<head><title>动态包含</title></head>
<body>
	<%
		int x = 100;  
	%>
	<h1>inc_2.jsp -- <%=x%></h1>
	<jsp:include page="include.jsp"/> <%-- 动态包含 --%> 
</body>
</html>