package com.hit.spt.service.impl;

import com.hit.spt.mapper.CategoryMapper;
import com.hit.spt.mapper.EquipmentMapper;
import com.hit.spt.mapper.EventMapper;
import com.hit.spt.mapper.UserMapper;
import com.hit.spt.pojo.Category;
import com.hit.spt.pojo.Equipment;
import com.hit.spt.pojo.Event;
import com.hit.spt.pojo.User;
import com.hit.spt.service.AdministerService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class AdministerServiceImpl implements AdministerService {

    @Autowired
    UserMapper userMapper;

    @Autowired
    CategoryMapper categoryMapper;

    @Autowired
    EquipmentMapper equipmentMapper;

    @Autowired
    EventMapper eventMapper;

    @Override
    public boolean addUser(String u_name , String password , Integer identity) {
        User user = new User();
        user.setU_name(u_name);
        user.setPassword(password);
        user.setIdentity(identity);
        try {
            return userMapper.insertUser(user) > 0;
        } catch (Exception E) {
            return false;
        }
    }

    @Override
    public boolean removeUser(String u_name) {
        try {
            User user = userMapper.queryUserByName(u_name);
            if (user.getIdentity() == 3) return false;
            return userMapper.deleteUser(u_name) > 0;
        } catch (Exception E) {
            return false;
        }
    }

    @Override
    public boolean addCategory(String c_name , String text) {
        Category category = new Category();
        category.setC_name(c_name);
        category.setText(text);
        try {
            return categoryMapper.insertCategory(category)>0;
        } catch (Exception E) {
            return false;
        }
    }

    @Override
    public boolean addEquipment(String cate_name , String text) {
        Equipment equipment = new Equipment();
        equipment.setCate_name(cate_name);
        equipment.setText(text);
        try {
            equipmentMapper.insertEquipment(equipment);
        } catch (Exception E) {
            return false;
        }
        Category category = categoryMapper.queryCategoryByName(equipment.getCate_name());
        category.setE_num(category.getE_num()+1);
        try {
            return categoryMapper.maintainNumber(category) > 0;
        } catch (Exception E) {
            return false;
        }

    }

    @Override
    public boolean removeEquipment(Integer e_id) {
        Equipment equipment = equipmentMapper.queryEquipmentByID(e_id);
        Category category;
        try {
            category = categoryMapper.queryCategoryByName(equipment.getCate_name());
        } catch (Exception E) {
            return false;
        }
        category.setE_num(category.getE_num()-1);
        try {
            equipmentMapper.deleteEquipment(e_id);
        } catch (Exception E) {
            return false;
        }

        try {
            return categoryMapper.maintainNumber(category) > 0;
        } catch (Exception E) {
            return false;
        }
    }

    @Override
    public List<Event> getEventByStu(Integer u_id) {
        try {
            return eventMapper.queryEventByUserStu(u_id);
        } catch (Exception E) {
            return null;
        }
    }

    @Override
    public List<Event> getEventByPro(Integer u_id) {
        try{
            return eventMapper.queryEventByUserPro(u_id);
        } catch (Exception E) {
            return null;
        }
    }

    @Override
    public List<Event> getEventByEquipment(Integer e_id) {
        try {
            return eventMapper.queryEventByEquipment(e_id);
        } catch (Exception E) {
            return null;
        }
    }

    @Override
    public Equipment getEquipment(Integer e_id) {
        try {
            return equipmentMapper.queryEquipmentByID(e_id);
        } catch (Exception E) {
            return null;
        }
    }

    @Override
    public List<Category> getCategoryList() {
        try {
            return categoryMapper.queryCategoryList();
        } catch (Exception E) {
            return null;
        }
    }

    @Override
    public List<Equipment> getEquipmentList(String cate_name) {
        try {
            return equipmentMapper.queryEquipmentByCate(cate_name);
        } catch (Exception E) {
            return null;
        }
    }

}
