package com.hit.spt.mapper;

import com.hit.spt.pojo.Category;
import org.apache.ibatis.annotations.Mapper;
import org.springframework.stereotype.Repository;

import java.util.List;

@Mapper
@Repository
public interface CategoryMapper {

    int insertCategory(Category category);

    Category queryCategoryByName(String c_name);

    int maintainNumber(Category category);

    List <Category> queryCategoryList();

}
