package com.hit.spt.service;

import com.hit.spt.pojo.*;

import java.util.List;

public interface AdministerService {

    boolean addUser(String u_name,String password,Integer identity);

    boolean removeUser(String u_name);

    boolean addCategory(String c_name,String text);

    boolean addEquipment(String cate_name, String text);

    boolean removeEquipment(Integer e_id);

    Equipment getEquipment(Integer e_id);

    List<Event> getEventByStu(Integer u_id);

    List<Event> getEventByPro(Integer u_id);

    List<Event> getEventByEquipment (Integer e_id);

    List<Category> getCategoryList();

    List<Equipment> getEquipmentList(String cate_name);


}
