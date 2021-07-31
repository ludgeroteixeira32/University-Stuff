package com.example.restservice.register;


import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
public class Register {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String vaccinetype;
    private int codX;
    private String date;




    public Register() {
    }
    public Register(String vaccinetype, int codX, String date) {
        this.vaccinetype = vaccinetype;
        this.codX = codX;
        this.date = date;
    }

    @Override
    public String toString() {
        return "Register{" +
                "id=" + id +
                ", vaccinetype='" + vaccinetype +
                ", codX='" + codX +
                ", date='" + date + '\'' +
                '}';
    }

    public int getCodX() {
        return codX;
    }

    public void setCodX(int codX) {
        this.codX = codX;
    }

    public String getVaccinetype() {
        return vaccinetype;
    }

    public void setVaccinetype(String vaccinetype) {
        this.vaccinetype = vaccinetype;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

}
