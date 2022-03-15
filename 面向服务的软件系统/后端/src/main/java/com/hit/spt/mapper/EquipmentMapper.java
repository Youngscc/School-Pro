package com.hit.spt.mapper;

import com.hit.spt.pojo.Equipment;
import org.apache.ibatis.annotations.Mapper;
import org.springframework.stereotype.Repository;

import java.util.List;

@Mapper
@Repository
public interface EquipmentMapper {

    int insertEquipment (Equipment equipment);

    int deleteEquipment (Integer e_id);

    Equipment queryEquipmentByID (Integer e_id);

    List <Equipment> queryEquipmentByCate (String cate_name);

    int setStatement(Equipment equipment);

    List <Equipment> queryEquipmentByStatement (Integer statement);

    List <Equipment> queryEquipmentList();

}
