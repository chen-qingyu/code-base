package org.test;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class LifeCycleServlet extends HttpServlet
{

    public LifeCycleServlet()
    {
        System.out.println("1、构造 Servlet---LifeCycleServlet()");
    }

    public void init() throws ServletException
    {
        System.out.println("2、初始化 Servlet---init()");
    }

    public void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        System.out.println("3、服务方法 Servlet---service()");
    }

//    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
//    {
//        System.out.println("3、服务方法 Servlet---doGet()");
//    }

    public void destroy()
    {
        System.out.println("4、销毁 Servlet---destroy()");
    }

}
