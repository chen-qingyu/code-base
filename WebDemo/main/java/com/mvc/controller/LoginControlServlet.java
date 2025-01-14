package com.mvc.controller;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.mvc.dao.factory.DAOFactory;
import com.mvc.vo.User;

public class LoginControlServlet extends HttpServlet
{

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        String path = "login.jsp";
        String userid = request.getParameter("userid"); // 接收userid的内容
        String userpass = request.getParameter("userpass"); // 接收userpass的内容
        List<String> info = new ArrayList<String>(); // 保存返回信息
        // 判断输入为空的情况
        if (userid == null || "".equals(userid))
        {
            info.add("用户id不能为空");
        }
        if (userpass == null || "".equals(userpass))
        {
            info.add("密码不能为空");
        }
        // 用户名密码验证通过
        if (info.size() == 0)
        {
            User user = new User(); // 实例化vo
            user.setAdminId(userid); // 设置userid
            user.setAdminPassword(userpass); // 设置userpass
            try
            {
                if (DAOFactory.getIUserDAOInstance().findLogin(user))
                { // 验证通过
                    info.add(user.getAdminName() + "已登录");
                }
                else
                {
                    info.add("登录失败");
                }
            } catch (Exception e)
            {
                e.printStackTrace();
            }
        }
        request.setAttribute("info", info);
        request.getRequestDispatcher(path).forward(request, response); // 跳转}
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        doGet(request, response);
    }

}
