package com.hit.spt.mapper;

import com.hit.spt.pojo.Event;
import org.apache.ibatis.annotations.Mapper;
import org.springframework.stereotype.Repository;

import java.util.List;

@Mapper
@Repository
public interface EventMapper {

    int insertEvent(Event event);

    List <Event> queryEventByUserStu(Integer user_id_stu);

    List <Event> queryEventByUserPro(Integer user_id_pro);

    List <Event> queryEventByEquipment(Integer eq_id);

    List <Event> queryEventByStatement(Integer statement);

    Event queryEventByID(Integer ev_id);

    Event queryEventByEqID(Integer e_id);

    int maintainEvent(Event event);
}
