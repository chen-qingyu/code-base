<%@ page contentType="text/html" pageEncoding="UTF-8"%>
<html>
<head>
<title>response对象设置相应头</title>
</head>
<body>
	<%!// 定义全局变量
    int count = 0;%>
	<%
	response.setHeader("refresh", "1"); // 页面1秒一刷新
	%>
	<h3>
		已经访问了<%=count++%>次！
	</h3>
</body>
</html>