package com.hit.spt.service.impl;

import com.hit.spt.mapper.CategoryMapper;
import com.hit.spt.mapper.EquipmentMapper;
import com.hit.spt.mapper.EventMapper;
import com.hit.spt.pojo.Category;
import com.hit.spt.pojo.Equipment;
import com.hit.spt.pojo.Event;
import com.hit.spt.service.ProService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class ProServiceImpl implements ProService {
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
    public List<Event> getEventByPro(Integer u_id) {
        try {
            return eventMapper.queryEventByUserPro(u_id);
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

    @Override
    public List<Event> getEventToMaintain() {
        try {
            return eventMapper.queryEventByStatement(0);
        } catch (Exception E) {
            return null;
        }
    }

    @Override
    public boolean maintain(Integer u_id, Integer eq_id, String text) {
        try {
            Event event = eventMapper.queryEventByEqID(eq_id);
            Equipment equipment = equipmentMapper.queryEquipmentByID(eq_id);
            event.setStatement(1);
            event.setText_pro(text);
            event.setUser_id_pro(u_id);
            if (eventMapper.maintainEvent(event) <= 0) return false;
            equipment.setStatement(0);
            return equipmentMapper.setStatement(equipment) > 0;
        } catch (Exception E) {
            return false;
        }
    }
}
