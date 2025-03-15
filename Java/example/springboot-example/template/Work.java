package edu.nuist.ceea.entity;

import java.sql.Timestamp;
import org.springframework.data.annotation.CreatedDate;

import com.alibaba.fastjson.JSONObject;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Transient;

import java.sql.Timestamp;


import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder

@Entity
@Table(name = "work")

public class Work {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private long id;
    

    @Column(name="createtime",columnDefinition="TIMESTAMP DEFAULT CURRENT_TIMESTAMP", insertable = false,updatable = false)
    @CreatedDate
    private Timestamp createtime;

    private long cId;
    private long mId;  

    private long wmId; //work的内容本身就是一个材料
    private long weId; 
    @Transient
    private Materials m;

    @Transient
    private ExperimentReport e;

    @Transient
    private Mark mark;


    private long studId;
    private int version;

    private int status; //0没有材料，或者是暂存的，1是已经提交的, 2是老师批改结束的，3是老师要求修改重新提交的, 4.是最终结束的
    
    @Transient
    public static final String[] types = new String[]{"未提交", "已提交","已批改", "待重新提交"};
    
}
