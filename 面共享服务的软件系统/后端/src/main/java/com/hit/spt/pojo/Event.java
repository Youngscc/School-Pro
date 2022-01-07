package com.hit.spt.pojo;


import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class Event { // 报修事件
    private Integer ev_id; // 报修事件编号
    private Integer user_id_stu; // 报修学生ID
    private Integer user_id_pro; // 修理人员ID， 如果未检修则为空
    private Integer eq_id; // 被维修设备编号
    private Integer statement; // 该事件状态： 0表示已报修未检修， 1表示检修完成
    private String start_time; // 报修时间：年月日时分秒
    private String end_time; // 修理时间：年月日时分秒
    private String text_stu; // 故障描述
    private String text_pro; // 维修备注

}
