package com.mvc.dao;

import com.mvc.vo.User;

public interface IUserDAO
{
    public boolean findLogin(User user) throws Exception;
}
