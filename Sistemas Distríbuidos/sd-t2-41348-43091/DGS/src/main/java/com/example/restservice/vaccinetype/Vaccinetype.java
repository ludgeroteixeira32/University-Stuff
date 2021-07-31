package com.example.restservice.vaccinetype;

import com.example.restservice.day.Day;

import javax.persistence.*;

@Entity
public class Vaccinetype {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;

    private String name;
    private String date;
    private int num;

    public Vaccinetype() {
    }

    public Vaccinetype(String name, int num, String date) {
        this.name = name;
        this.num = num;
        this.date = date;
    }

    @Override
    public String toString() {
        return "Vaccination_Center{" +
                ", name='" + name +
                ", date='" + date +
                ", num='" + num + '\'' +
                '}';
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.name = date;
    }

    public int getNum() {
        return num;
    }

    public void setNum(int num) {
        this.num = num;
    }
}
