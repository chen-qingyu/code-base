<%@ page contentType="text/html" pageEncoding="UTF-8"%>
<%@ page import="java.util.Enumeration"%>
<html>
<head>
<title>request对象获取头信息</title>
</head>
<body>
	<%
	Enumeration<String> enu = request.getHeaderNames(); // 取得全部的头信息
	while (enu.hasMoreElements())
	{
	    String headerName = (String) enu.nextElement();
	    String headerValue = request.getHeader(headerName);
	%>
	<h5><%=headerName%>
		-->
		<%=headerValue%></h5>
	<%
	}
	%>
</body>
</html>