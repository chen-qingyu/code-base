package org.test;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class MySQLServlet extends HttpServlet
{
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        // 解决服务器返回页面中文乱码问题
        response.setContentType("text/html;charset=UTF-8");
        // 解决post方式请求表单参数中文乱码问题
        request.setCharacterEncoding("UTF-8");
        try
        {
            // 1. load driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // 2. connect
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/db_stuscore?serverTimezone=GMT",
                    "root", "123456");

            // 3. exec SQL
            String sql = "select * from student";
            Statement st = con.createStatement();
            ResultSet rs = st.executeQuery(sql);

            // 4. show result
            PrintWriter pw = response.getWriter();
            pw.write("<table border=\"1\">");
            pw.write("<tr><th>姓名</th><th>备注</th></tr>");
            while (rs.next())
            {
                pw.write("<tr>");
                pw.write("<td>" + rs.getString("name") + "</td>");
                pw.write("<td>" + rs.getString("comm") + "</td>");
                pw.write("</tr>");
            }
            pw.write("</table>");

            // 5. close connection
            con.close();

        } catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        doGet(request, response);
    }

}
