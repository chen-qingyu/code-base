<%@ page contentType="text/html" pageEncoding="UTF-8"%>
<%@ page import="java.util.*"%>
<html>
<head>
<title>request对象获取IP地址访问路径等</title>
</head>
<body>
	<%
	String method = request.getMethod();
	String ip = request.getRemoteAddr();
	String path = request.getServletPath();
	String contextPath = request.getContextPath();
	%>
	<h3>
		请求方式：<%=method%></h3>
	<h3>
		IP地址：<%=ip%></h3>
	<h3>
		访问路径：<%=path%></h3>
	<h3>
		上下文名称：<%=contextPath%></h3>
</body>
</html>