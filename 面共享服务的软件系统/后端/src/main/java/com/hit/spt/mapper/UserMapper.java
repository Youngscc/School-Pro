package com.hit.spt.mapper;

import com.hit.spt.pojo.User;
import org.apache.ibatis.annotations.Mapper;
import org.springframework.stereotype.Repository;

@Mapper
@Repository
public interface UserMapper {

    int insertUser(User user);

    int deleteUser(String u_name);

    User queryUserByName(String u_name);

    User queryUserByID(Integer u_id);
}
