package com.hit.spt.service;

import com.hit.spt.pojo.Category;
import com.hit.spt.pojo.Equipment;
import com.hit.spt.pojo.Event;

import java.util.List;

public interface ProService {

    List<Event> getEventByEquipment (Integer e_id);

    List<Event> getEventByPro(Integer u_id);

    Equipment getEquipment(Integer e_id);

    List<Category> getCategoryList();

    List<Equipment> getEquipmentList(String cate_name);

    List <Event> getEventToMaintain();

    boolean maintain(Integer u_id,Integer ev_id,String text);

}
