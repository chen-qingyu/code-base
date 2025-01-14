package com.mvc.dao.impl;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import com.mvc.dao.IUserDAO;
import com.mvc.vo.User;

public class UserDAOImpl implements IUserDAO
{
    private Connection conn = null;
    private PreparedStatement pst = null;

    public UserDAOImpl(Connection conn)
    {
        this.conn = conn;
    }

    @Override
    public boolean findLogin(User user) throws Exception
    {
        boolean isFind = false;
        String sql = "select adminName from t_admin where adminId=? and adminPassword=?";
        pst = conn.prepareStatement(sql);
        pst.setString(1, user.getAdminId());
        pst.setString(2, user.getAdminPassword());
        ResultSet rs = pst.executeQuery();
        if (rs.next())
        {
            user.setAdminName(rs.getString("adminName"));
            isFind = true;
        }
        pst.close();
        return isFind;
    }

}
