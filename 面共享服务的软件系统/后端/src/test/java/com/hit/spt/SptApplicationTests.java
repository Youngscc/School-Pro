package com.hit.spt;

import com.hit.spt.mapper.*;
import com.hit.spt.pojo.*;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class SptApplicationTests {

    @Autowired
    CategoryMapper categoryMapper;


    @Test
    public void testCategoryMapper(){
//     System.out.println(categoryMapper.insertCategory(new Category(0, "a", "aaa", 0)));
//     System.out.println(categoryMapper.insertCategory(new Category(0, "b", "bbb", 0)));
//     Category A = categoryMapper.queryCategoryByName("a");
//     Category B = categoryMapper.queryCategoryByName("b");
//     System.out.println(A);
//     System.out.println(B);
//     categoryMapper.maintainNumber(new Category(4, "a", "aaa", 1));
//     categoryMapper.maintainNumber(new Category(5, "b", "bbb", 2));
        System.out.println(categoryMapper.queryCategoryList());
    }

    @Autowired
    EquipmentMapper equipmentMapper;


    @Test
    public void testEquipmentMapper() {
//        System.out.println(equipmentMapper.insertEquipment(new Equipment(0, "a", "aaaaa", 0)));
//        System.out.println(equipmentMapper.insertEquipment(new Equipment(0, "b", "bbbbb", 0)));
//        System.out.println(equipmentMapper.insertEquipment(new Equipment(0, "b", "ccccc", 0)));
//        System.out.println(equipmentMapper.queryEquipmentByCate("b"));
//        System.out.println(equipmentMapper.deleteEquipment(3));
//        System.out.println(equipmentMapper.queryEquipmentByCate("b"));
//        System.out.println(equipmentMapper.queryEquipmentByCate("a"));
//        System.out.println(equipmentMapper.queryEquipmentByID(1));
//        System.out.println(equipmentMapper.queryEquipmentByID(2));
//        equipmentMapper.setStatement(new Equipment(1,"a", "aaaaa", 1));
//        System.out.println(equipmentMapper.queryEquipmentByID(1));
//        System.out.println(equipmentMapper.queryEquipmentByID(2));
        System.out.println(equipmentMapper.queryEquipmentByStatement(1));
    }

    @Autowired
    UserMapper userMapper;

    @Test
    public void testUserMapper() {
        System.out.println(userMapper.insertUser(new User(0, "Youngsc", "11223344", 1)));
        System.out.println(userMapper.insertUser(new User(0, "Ccccpql", "123123", 2)));
        System.out.println(userMapper.insertUser(new User(0, "sc", "11223344", 1)));
        System.out.println(userMapper.queryUserByName("Youngsc"));
        System.out.println(userMapper.queryUserByName("sc"));
        System.out.println(userMapper.deleteUser("sc"));
        System.out.println(userMapper.queryUserByID(1));
    }

    @Autowired
    EventMapper eventMapper;

    @Test
    public void testEventMapper() {
//        System.out.println(eventMapper.insertEvent(new Event(0, 2, 2, 1, 1, "", "", "aaaaa","")));
//        System.out.println(eventMapper.insertEvent(new Event(0, 2, 2, 2, 1, "", "", "bbbbb","")));
//        System.out.println(eventMapper.queryEventByEquipment(1));
//        System.out.println(eventMapper.queryEventByUserStu(2));
//        System.out.println(eventMapper.maintainEvent(new Event(1, 3, 3, 2, 1, "", "", "bbbbb","ccccc")));
//        System.out.println(eventMapper.queryEventByUserPro(3));
//        System.out.println(eventMapper.queryEventByStatement(0));
//        System.out.println(eventMapper.maintainEvent(new Event(0, 2, 5, 4, 1, "", "", "aaaaa","bbbb")));
//        System.out.println(eventMapper.insertEvent(new Event(0, 2, 5, 4, 1, "", "", "aaaaa","bbbb")));
        System.out.println(eventMapper.queryEventByEqID(4));
    }


}
