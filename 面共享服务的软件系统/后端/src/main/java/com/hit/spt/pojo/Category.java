package com.hit.spt.pojo;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class Category { // 设备类型
    private Integer c_id; // 设备类型编号
    private String c_name; // 类型名称
    private String text; // 相关文字性描述，如常见故障及修理方法等
    private Integer e_num; // 该类型下的设备数量
}
