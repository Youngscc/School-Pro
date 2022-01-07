package com.hit.spt.pojo;


import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class Equipment { // 具体设备个体
    private Integer e_id; // 设备ID
    private String cate_name;  // 设备所属种类
    private String text; // 地址等其他信息
    private Integer statement;  // 设备状态： 0表示正常  1表示待检修
}
