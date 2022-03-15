package com.hit.spt.service.impl;

import com.hit.spt.mapper.*;
import com.hit.spt.pojo.*;
import com.hit.spt.service.StuService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class StuServiceImpl implements StuService {

    @Autowired
    CategoryMapper categoryMapper;

    @Autowired
    EquipmentMapper equipmentMapper;

    @Autowired
    EventMapper eventMapper;

    @Override
    public List<Event> getEventByEquipment(Integer e_id) {
        try {
            return eventMapper.queryEventByEquipment(e_id);
        } catch (Exception E) {
            return null;
        }
    }

    @Override
    public List<Event> getEventByStu(Integer u_id) {
        try {
            return eventMapper.queryEventByUserStu(u_id);
        } catch ( Exception E) {
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

    @Override
    public String getCategoryText(Integer e_id) {
        try {
            Equipment equipment = equipmentMapper.queryEquipmentByID(e_id);
            if (equipment == null) return "Error";
            Category category = categoryMapper.queryCategoryByName(equipment.getCate_name());
            if (category == null) return "Error";
            return category.getText();
        } catch (Exception E ){
            return "Error";
        }

    }

    @Override
    public boolean reportEvent(Integer u_id , Integer e_id, String text) {
        try {
            Equipment equipment = equipmentMapper.queryEquipmentByID(e_id);
            if (equipment == null || equipment.getStatement() == 1) return false;
            equipment.setStatement(1);
            equipmentMapper.setStatement(equipment);
            Event event = new Event();
            event.setUser_id_stu(u_id);
            event.setEq_id(e_id);
            event.setText_stu(text);
            return eventMapper.insertEvent(event) > 0;
        } catch (Exception E) {
            return false;
        }
    }
}
