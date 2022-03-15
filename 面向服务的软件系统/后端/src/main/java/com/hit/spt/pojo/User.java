package com.hit.spt.pojo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class User {
    private Integer u_id; // 用户ID
    private String u_name; // 用户姓名
    private String password; // 用户密码
    private Integer identity; // 用户身份 1：师生 2：维修人员 3:系统管理员
}
