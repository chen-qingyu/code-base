package com.mvc.dao.proxy;

import com.mvc.dao.IUserDAO;
import com.mvc.dao.impl.UserDAOImpl;
import com.mvc.dbc.DatabaseConnection;
import com.mvc.vo.User;

public class UserDAOProxy implements IUserDAO
{
    private DatabaseConnection dbc = null;
    private IUserDAO dao = null;

    public UserDAOProxy() // 构造方法，实例化连接，同时实例化dao对象
    {
        try // 连接数据库
        {
            this.dbc = new DatabaseConnection();
        } catch (Exception e)
        {
            e.printStackTrace();
        }
        // 实例化真实主题类
        this.dao = new UserDAOImpl(this.dbc.getConnection());
    }

    public boolean findLogin(User user) throws Exception
    {
        boolean flag = false;
        try
        {
            flag = this.dao.findLogin(user);
        } catch (Exception e)
        {
            throw e;
        } finally
        {
            this.dbc.close();
        }
        return flag;
    }
}
