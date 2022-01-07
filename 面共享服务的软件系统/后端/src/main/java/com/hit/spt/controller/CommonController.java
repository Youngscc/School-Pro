package com.hit.spt.controller;

import com.hit.spt.pojo.Equipment;
import com.hit.spt.pojo.User;
import com.hit.spt.service.CommonService;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.swing.*;
import java.util.List;

@Controller
public class CommonController {
    @Autowired
    CommonService service;

    @RequestMapping("getEquipmentIDList")
    @ResponseBody
    public String getEquipmentList() throws JSONException {
        List <Equipment> ret = service.queryEquipmentList();
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
