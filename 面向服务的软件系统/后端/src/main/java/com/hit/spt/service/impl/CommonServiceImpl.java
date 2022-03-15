package com.hit.spt.service.impl;

import com.hit.spt.mapper.EquipmentMapper;
import com.hit.spt.pojo.Equipment;
import com.hit.spt.service.CommonService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class CommonServiceImpl implements CommonService {

    @Autowired
    EquipmentMapper equipmentMapper;


    @Override
    public List<Equipment> queryEquipmentList() {
        try {
            return equipmentMapper.queryEquipmentList();
        } catch (Exception E) {
            return null;
        }
    }
}
