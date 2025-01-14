<%@ page contentType="text/html" pageEncoding="utf-8"%>
<jsp:useBean id="simple" scope="page" class="org.test.DemoBean" />
<html>
<head>
<title>Java Bean 测试</title>
</head>
<body>
	<%
	simple.setName("陈青羽");
	simple.setAge(21);
	%>
	<h3>
		姓名：<%=simple.getName()%></h3>
	<h3>
		年龄：<%=simple.getAge()%></h3>
</body>
</html>