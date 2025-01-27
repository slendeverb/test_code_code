package edu.nuist.metelog.entity;

import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

import javax.persistence.Entity;
import javax.persistence.Table;

import lombok.Data;
@Entity
@Table(name = "pro_loc_relation")
@Data
public class ProductLocationRelation {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private long id;

    private long pid;
    private long lid;
}
