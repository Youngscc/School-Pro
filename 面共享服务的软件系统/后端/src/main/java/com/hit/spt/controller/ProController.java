package com.hit.spt.controller;

import com.hit.spt.pojo.*;
import com.hit.spt.service.ProService;
import org.json.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.List;

@Controller
@RequestMapping("pro")

public class ProController {

    @Autowired
    ProService service;

    /**
     * 用于根据设备编号查询该设备的所有维修记录 （对应报修人不予返回）
     * @param equipmentID Integer 被查询的设备ID
     * @return 所有的报修记录列表，注：若当前事件的状态为0，即
     *      报修但并未检修，请忽略user_id_pro、end_time、text_pro.
     */
    @RequestMapping("getEventByEquipment")
    @ResponseBody
    public String getEventByEquipment(Integer equipmentID) throws JSONException {
        List<Event> ret = service.getEventByEquipment(equipmentID);
        JSONArray temp = new JSONArray();
        for (Event event: ret) {
            JSONObject jo = new JSONObject();
            jo.put("ev_id",event.getEv_id());
            jo.put("user_id_stu" ,null);
            jo.put("user_id_pro",event.getUser_id_pro());
            jo.put("equipment_id",event.getEq_id());
            jo.put("statement",event.getStatement());
            jo.put("start_time",event.getStart_time());
            jo.put("end_time",event.getEnd_time());
            jo.put("text_stu",event.getText_stu());
            jo.put("text_pro",event.getText_pro());
            temp.put(jo);
        }
        return temp.toString();
    }


    /**
     * 根据自己的ID查询该用户所有的维修事件记录 报修人不予返回
     *
     * @param proID Integer 此处应传入当前登录用户的ID
     * @return 所有的报修记录列表.
     */
    @RequestMapping("getEventByPro")
    @ResponseBody
    public String getEventByStu(Integer proID) throws JSONException {
        List<Event> ret = service.getEventByPro(proID);
        JSONArray temp = new JSONArray();
        for (Event event : ret) {
            JSONObject jo = new JSONObject();
            jo.put("ev_id" , event.getEv_id());
            jo.put("user_id_stu" , null);
            jo.put("user_id_pro" , event.getUser_id_pro());
            jo.put("equipment_id" , event.getEq_id());
            jo.put("statement" , event.getStatement());
            jo.put("start_time" , event.getStart_time());
            jo.put("end_time" , event.getEnd_time());
            jo.put("text_stu" , event.getText_stu());
            jo.put("text_pro" , event.getText_pro());
            temp.put(jo);
        }
        return temp.toString();
    }


    /**
     * 用于根据设备ID获取设备的信息，包括设备类型
     * @param equipmentID Integer 设备ID
     * @return 设备信息组成的结构体，其中text指设备地址或其他备注信息
     */
    @RequestMapping("getEquipment")
    @ResponseBody
    public String getEquipment(Integer equipmentID) throws JSONException {
        Equipment equipment = service.getEquipment(equipmentID);
        JSONObject temp = new JSONObject();
        if (equipment != null) {
            temp.put("e_id", equipment.getE_id());
            temp.put("category_name", equipment.getCate_name());
            temp.put("text",equipment.getText());
            temp.put("statement",equipment.getStatement());
        }
        return temp.toString();
    }


    /**
     * 用于获取所有的设备类型的详细信息
     * @return 结构体category,text指常见故障及排除方式
     */
    @RequestMapping("getCategoryList")
    @ResponseBody
    public String getCategoryList() throws JSONException {
        List<Category> ret = service.getCategoryList();
        JSONArray temp = new JSONArray();
        for (Category category: ret) {
            JSONObject jo = new JSONObject();
            jo.put("c_id",category.getC_id());
            jo.put("c_name",category.getC_name());
            jo.put("text",category.getText());
            jo.put("equipment_num",category.getE_num());
            temp.put(jo);
        }
        return temp.toString();
    }

    /**
     * 用于查询所有类型为categoryName的设备的详细信息
     * @param categoryName String 设备类型名字
     * @return 设备个体列表
     */
    @RequestMapping("getEquipmentList")
    @ResponseBody
    public String getEquipmentList(String categoryName) throws JSONException {
        List<Equipment> ret = service.getEquipmentList(categoryName);
        JSONArray temp = new JSONArray();
        for (Equipment equipment: ret) {
            JSONObject jo = new JSONObject();
            jo.put("e_id",equipment.getE_id());
            jo.put("cate_name",equipment.getCate_name());
            jo.put("text",equipment.getText());
            jo.put("statement",equipment.getStatement());
            temp.put(jo);
        }
        return temp.toString();
    }


    /**
     * 用于维修人员获得所有已报修未修理的事件列表
     * @return event 列表
     */
    @RequestMapping("getEventToMaintain")
    @ResponseBody
    public String getEventToMaintain() throws JSONException {
        List<Event> ret = service.getEventToMaintain();
        JSONArray temp = new JSONArray();
        for (Event event: ret) {
            JSONObject jo = new JSONObject();
            jo.put("ev_id" , event.getEv_id());
            jo.put("user_id_stu" , null);
            jo.put("user_id_pro" , null);
            jo.put("equipment_id" , event.getEq_id());
            jo.put("statement" , event.getStatement());
            jo.put("start_time" , event.getStart_time());
            jo.put("end_time" , null);
            jo.put("text_stu" , event.getText_stu());
            jo.put("text_pro" , null);
            temp.put(jo);
        }
        return temp.toString();
    }


    /**
     * 用于维修人员维修完毕后对事件和设备信息进行维护
     * @param userID Integer 当前登录的维修人员的ID
     * @param equipmentID Integer 被维修设备的编号
     * @param text String 维修人员的维修备注（维修人员自行填写内同）
     * @return Boolean true表示成功，否则失败
     */
    @RequestMapping("maintain")
    @ResponseBody
    public String maintain(Integer userID,Integer equipmentID,String text) throws JSONException {
        boolean ret = service.maintain(userID,equipmentID,text);
        JSONObject temp = new JSONObject();
        temp.put("boolean", ret);
        return temp.toString();
    }

}
