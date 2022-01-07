package com.hit.spt.controller;

import com.hit.spt.pojo.*;
import com.hit.spt.service.*;
import org.json.JSONException;
import org.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller

public class LoginController {

    @Autowired
    LoginService service;

    /**
     * @param username 用户名：String类型
     * @param password 用户密码：String类型，可为空
     * @return 返回一个User结构体或者null，null为用户名或密码错误，登陆失败。 否则为当前登录用户的相关信息。
     */
    @RequestMapping("login")
    @ResponseBody
    public String login(String username, String password) throws JSONException {
        User ret = service.checkPassword(username, password);
        JSONObject temp = new JSONObject();
        if (ret != null) {
            temp.put("u_id",ret.getU_id().intValue());
            temp.put("u_name",ret.getU_name());
            temp.put("identity",ret.getIdentity());
        }
        return temp.toString();
    }
}
