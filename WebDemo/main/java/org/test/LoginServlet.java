package org.test;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class LoginServlet extends HttpServlet
{
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        // 解决服务器返回页面中文乱码问题
        response.setContentType("text/html;charset=UTF-8");
        // 解决post方式请求表单参数中文乱码问题
        request.setCharacterEncoding("UTF-8");
        String user = request.getParameter("user");
        String passwd = request.getParameter("passwd");
        if (user.equals("yu") && passwd.equals("123456"))
        {
            response.getWriter().append("登陆成功！");
        }
        else
        {
            response.getWriter().append("登陆失败！");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        doGet(request, response);
    }
}
