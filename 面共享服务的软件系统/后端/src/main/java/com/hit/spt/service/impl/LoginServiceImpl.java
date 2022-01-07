package com.hit.spt.service.impl;

import com.hit.spt.mapper.UserMapper;
import com.hit.spt.pojo.User;
import com.hit.spt.service.LoginService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class LoginServiceImpl implements LoginService {

    @Autowired
    UserMapper userMapper;

    @Override
    public User checkPassword(String u_name , String password) {
        try {
            User user = userMapper.queryUserByName(u_name);
            if (user == null || !user.getPassword().equals(password)) return null;
            else return user;
        } catch (Exception E) {
            return null;
        }
    }

    @Override
    public boolean checkIdentity(Integer u_id , Integer identity) {
        User user = userMapper.queryUserByID(u_id);
        return user.getIdentity().equals(identity);
    }
}
