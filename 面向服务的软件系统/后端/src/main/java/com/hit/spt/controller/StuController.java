package com.hit.spt.controller;

import com.hit.spt.pojo.*;
import com.hit.spt.service.*;
import org.json.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.List;

@Controller
@RequestMapping("stu")

public class StuController {

    @Autowired
    StuService service;

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
     * 根据自己的ID查询该用户所有的报修事件记录
     *
     * @param stuID Integer 此处应传入当前登录用户的ID
     * @return 所有的报修记录列表，注：若当前事件的状态为0，即
     * 报修但并未检修，请忽略user_id_pro、end_time、text_pro.
     */
    @RequestMapping("getEventByStu")
    @ResponseBody
    public String getEventByStu(Integer stuID) throws JSONException {
        List<Event> ret = service.getEventByStu(stuID);
        JSONArray temp = new JSONArray();
        for (Event event : ret) {
            JSONObject jo = new JSONObject();
            jo.put("ev_id" , event.getEv_id());
            jo.put("user_id_stu" , event.getUser_id_stu());
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
     * 根据设备个体ID查询该种类设备常见故障及排除方法
     * 主要用于用户在发现故障时先列出常见故障供用户参考
     * @param equipmentID  Integer：当前设备的ID
     * @return 返回该设备个体对应的设备种类的常见故障及排除方式, 如果查询失败（可能是并没有该种类）则返回”Error“。
     */
    @RequestMapping("getCategoryText")
    @ResponseBody
    public String getCategoryText(Integer equipmentID) throws JSONException {
        String text = service.getCategoryText(equipmentID);
        JSONObject temp = new JSONObject();
        temp.put("text",text);
        return temp.toString();
    }

    /**
     * 用于报修。
     * @param userID 应为当前注册用户ID
     * @param equipmentID 应为故障设备个体ID
     * @param text 报修人附加的故障描述
     * @return boolean true为报修成功，否则失败(可能为已经有人报修过了)
     */
    @RequestMapping("reportEvent")
    @ResponseBody
    public String reportEvent (Integer userID,Integer equipmentID,String text) throws JSONException {
        boolean ret = service.reportEvent(userID,equipmentID,text);
        JSONObject temp = new JSONObject();
        temp.put("boolean",ret);
        return temp.toString();
    }
}
