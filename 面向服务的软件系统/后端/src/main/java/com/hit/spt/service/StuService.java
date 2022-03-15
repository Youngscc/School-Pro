package com.hit.spt.service;

import com.hit.spt.pojo.*;

import java.util.List;

public interface StuService{

    List<Event> getEventByEquipment (Integer e_id);

    List<Event> getEventByStu(Integer u_id);

    Equipment getEquipment(Integer e_id);

    List<Category> getCategoryList();

    List<Equipment> getEquipmentList(String cate_name);

    String getCategoryText(Integer e_id);

    boolean reportEvent(Integer u_id,Integer e_id,String text);

}
