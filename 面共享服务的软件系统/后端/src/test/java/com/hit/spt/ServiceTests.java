package com.hit.spt;

import com.hit.spt.pojo.Category;
import com.hit.spt.pojo.Equipment;
import com.hit.spt.service.*;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import java.util.List;

@SpringBootTest
class ServiceTests {

    @Autowired
    LoginService loginService;

    @Test
    public void testLoginService() {

        System.out.println(loginService.checkPassword("admin","123456"));
        System.out.println(loginService.checkPassword("Youngsc","11223344"));
        System.out.println(loginService.checkPassword("Ccccpql","123123"));
        System.out.println(loginService.checkPassword("Ccccpql","324324324"));
    }


    @Autowired
    AdministerService administerService;

    @Test
    public void testAdministerService() {
        System.out.println(administerService.addUser("ppp","5678",2));
        System.out.println(administerService.addCategory("Computer", "You can remake."));
        System.out.println(administerService.addCategory("Ipad", "You can remake."));
        System.out.println(administerService.addEquipment("Computer", "Zhengxin 3F"));
        System.out.println(administerService.addEquipment("Computer", "Zhengxin 4F"));
        System.out.println(administerService.addEquipment("Ipad", "Zhengxin 3F"));
        System.out.println(administerService.addEquipment("Ipad", "Zhengxin 4F"));
        System.out.println(administerService.getCategoryList());
        List<Category> now = administerService.getCategoryList();
        System.out.println(administerService.getEquipmentList(now.get(0).getC_name()));
        System.out.println(administerService.getEquipmentList(now.get(1).getC_name()));
        List <Equipment> now1 = administerService.getEquipmentList(now.get(0).getC_name());
        System.out.println(administerService.getEquipment(now1.get(0).getE_id()));
        System.out.println(administerService.removeUser("Ccccpql"));
        System.out.println(administerService.removeEquipment(now1.get(1).getE_id()));
        System.out.println(administerService.getEquipmentList(now.get(0).getC_name()));

    }


    @Autowired
    StuService stuService;

    @Test
    public void testStuService() {
        System.out.println(stuService.reportEvent(2, 4, "aaa"));
        System.out.println(stuService.reportEvent(2, 7, "aaa"));
        System.out.println(stuService.getEventByEquipment(4));
        System.out.println(stuService.getEventByStu(2));
        System.out.println(stuService.getCategoryList());
        System.out.println(stuService.getEquipment(7));
        System.out.println(stuService.getEquipmentList("Ipad"));
    }
}
