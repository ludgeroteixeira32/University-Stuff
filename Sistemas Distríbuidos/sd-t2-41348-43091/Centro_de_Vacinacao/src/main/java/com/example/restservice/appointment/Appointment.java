package com.example.restservice.appointment;

import javax.persistence.*;

@Entity
public class Appointment implements Comparable<Appointment>{
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String date;
    private int age;
    private String center;
    private String name;
    private String email;
    private int userid;
    private int status;


    public Appointment() {
    }

    public Appointment(String date, int age, String center, String name, String email, int userid, int status) {
        this.date = date;
        this.age = age;
        this.center = center;
        this.name = name;
        this.email = email;
        this.userid = userid;
        this.status = status;
    }

    @Override
    public String toString() {
        return "Appointment{" +
                "id=" + id +
                ", date='" + date +
                ", age='" + age +
                ", center='" + center +
                ", name='" + name +
                ", email='" + email +
                ", userid='" + userid +
                ", status='" + status + '\'' +
                '}';
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public String getCenter() {
        return center;
    }

    public void setCenter(String center) {
        this.center = center;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public int getUserid() {
        return userid;
    }

    public void setUserid(int userId) {
        this.userid = userId;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    @Override
    public int compareTo(Appointment o) {
        if(o.age > this.age)
            return -1;
        else
            return 1;
    }
}
