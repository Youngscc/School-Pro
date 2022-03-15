package com.hit.spt.service;

import com.hit.spt.pojo.User;

public interface LoginService {

    User checkPassword(String u_name, String password);

    boolean checkIdentity(Integer u_id, Integer identity);

}
