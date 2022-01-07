package com.hit.spt;

import com.hit.spt.controller.*;
import org.json.JSONException;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
public class ControllerTests {

    @Autowired
    LoginController LoginController;

    @Test
    public void testLoginController() throws JSONException {
        System.out.println(LoginController.login("admin","123456"));
        System.out.println(LoginController.login("Youngsc","11223344"));
        System.out.println(LoginController.login("Ccccpql","324324324"));
        System.out.println(LoginController.login("Ccccpql","123123"));
    }


    @Autowired
    AdministerController administerController;

    @Test
    public void testAdministerController() throws JSONException {
        System.out.println(administerController.getEventByStu(2));
    }
}
