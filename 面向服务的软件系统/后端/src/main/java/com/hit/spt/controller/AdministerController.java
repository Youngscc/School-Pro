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
@RequestMapping("administer")
public class AdministerController {

    @Autowired
    AdministerService service;

    /**
     * 用于添加新的设备种类
     *
     * @param categoryName 新添加的设备种类的名字，相互之间不能重复
     * @param text         添加该种设备的常见故障及排除方式
     * @return true指添加成功 否则添加失败（命名重复）
     */
    @RequestMapping("addCategory")
    @ResponseBody
    public String addCategory(String categoryName , String text) throws JSONException {
        boolean ret = service.addCategory(categoryName , text);
        JSONObject temp = new JSONObject();
        temp.put("boolean" , ret);
        return temp.toString();
    }

    /**
     * 用于添加新的用户
     *
     * @param userName String用户名，不可重复
     * @param password String密码，可为空
     * @param identity Integer身份 1表示普通用户，2表示维修人员，3表示系统管理员
     * @return 返回一个boolean变量，为true表示添加成功，否则添加失败
     */
    @RequestMapping("addUser")
    @ResponseBody
    public String addUser(String userName , String password , Integer identity) throws JSONException {
        boolean ret = service.addUser(userName , password , identity);
        JSONObject temp = new JSONObject();
        temp.put("boolean" , ret);
        return temp.toString();
    }

    /**
     * 用户根据用户名删除用户，注：若被删除用户为管理员则删除失败
     *
     * @param userName String 用户名
     * @return 返回一个boolean变量，为true表示删除成功，否则删除失败
     */
    @RequestMapping("removeUser")
    @ResponseBody
    public String removeUser(String userName) throws JSONException {
        boolean ret = service.removeUser(userName);
        JSONObject temp = new JSONObject();
        temp.put("boolean" , ret);
        return temp.toString();
    }

    /**
     * 用于添加新的设备个体，同时所属的设备种类的设备数量加1
     *
     * @param categoryName 表示新的设备个体的所属设备类型
     * @param text         设备的具体位置（或其他备注信息）
     * @return 返回一个boolean变量 , true为成功，否则为失败
     */
    @RequestMapping("addEquipment")
    @ResponseBody
    public String addEquipment(String categoryName , String text) throws JSONException {
        boolean ret = service.addEquipment(categoryName , text);
        JSONObject temp = new JSONObject();
        temp.put("boolean" , ret);
        return temp.toString();
    }

    /**
     * 用于删除现有的设备个体，同时所属的设备种类的设备数量减1
     *
     * @param equipmentID 需要删除的；设备的ID
     * @return 返回一个boolean变量 , true为成功，否则为失败
     */

    @RequestMapping("removeEquipment")
    @ResponseBody
    public String removeEquipment(Integer equipmentID) throws JSONException {
        boolean ret = service.removeEquipment(equipmentID);
        JSONObject temp = new JSONObject();
        temp.put("boolean" , ret);
        return temp.toString();
    }

    /**
     * 根据报修人（师生）的ID查询该用户所有的报修事件记录
     *
     * @param stuID Integer 报修人ID
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
     * 用于根据维修人员的ID查询该维修人员所有的维修事件记录
     *
     * @param proID Integer 维修人员ID
     * @return 事件列表，且所有时间的statement显然均为1
     */
    @RequestMapping("getEventByPro")
    @ResponseBody
    public String getEventByPro(Integer proID) throws JSONException {
        List<Event> ret = service.getEventByPro(proID);
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
     * 用于根据设备编号查询该设备的所有维修记录
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
            jo.put("user_id_stu",event.getUser_id_stu());
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
     * 根基设备ID获取设备的信息，包括设备类型
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
}
