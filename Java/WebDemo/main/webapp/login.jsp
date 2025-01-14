<%@ page contentType="text/html" pageEncoding="UTF-8"
	import="java.util.*"%>

<html>
<head>

<title>登录页面</title>

</head>

<body>
	<h2>用户登录</h2>
	<%
	request.setCharacterEncoding("utf-8");
	%>
	<%
	List<String> info = (List<String>) request.getAttribute("info");
	if (info != null)
	{
	    Iterator<String> iter = info.iterator();
	    while (iter.hasNext())
	    {
	        out.append(iter.next() + "<br>");
	    }
	}
	%>
	<form action="LoginControlServlet" method="post">

		用户ID: <input type="text" name="userid"><br> 密 码:<input
			type="password" name="userpass"><br> <input
			type="submit" value="登录"> <input type="reset" value="重置">
	</form>
</body>
</html>