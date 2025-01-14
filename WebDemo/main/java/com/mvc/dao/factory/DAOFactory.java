package com.mvc.dao.factory;

import com.mvc.dao.IUserDAO;
import com.mvc.dao.proxy.UserDAOProxy;

public class DAOFactory
{
    public static IUserDAO getIUserDAOInstance()
    {
        return new UserDAOProxy();
    }
}
