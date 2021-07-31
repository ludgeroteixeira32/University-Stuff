package com.example.restservice.day;

import javax.persistence.*;

@Entity
public class Day {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String date;
    private int to_be_vaccinated;
    private String center;

    public Day() {
    }

    public Day(String date, int to_be_vaccinated, String center) {
        this.date = date;
        this.to_be_vaccinated = to_be_vaccinated;
        this.center = center;
    }

    public Day(Long id, String date, int to_be_vaccinated, String center) {
        this.id = id;
        this.date = date;
        this.to_be_vaccinated = to_be_vaccinated;
        this.center = center;
    }

    @Override
    public String toString() {
        return "Day{" +
                "id=" + id +
                ", date='" + date +
                ", to_be_vaccinated='" + to_be_vaccinated +
                ", center='" + center +'\'' +
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

    public int getTo_be_vaccinated() {
        return to_be_vaccinated;
    }

    public void setTo_be_vaccinated(int to_be_vaccinated) {
        this.to_be_vaccinated = to_be_vaccinated;
    }

    public String getCenter() {
        return center;
    }

    public void setCenter(String center) {
        this.center = center;
    }

}
