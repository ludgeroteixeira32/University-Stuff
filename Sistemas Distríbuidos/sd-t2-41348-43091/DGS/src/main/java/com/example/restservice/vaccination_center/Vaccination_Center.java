package com.example.restservice.vaccination_center;

import com.example.restservice.appointment.Appointment;

import javax.persistence.*;
import java.util.List;

@Entity
@Table(name="VACCINATION_CENTER")
public class Vaccination_Center {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String name;
    private int capacity;

    public Vaccination_Center() {
    }

    public Vaccination_Center(String name, int capacity) {
        this.name = name;
        this.capacity = capacity;
    }

    @Override
    public String toString() {
        return "Vaccination_Center{" +
                "id=" + id +
                ", name='" + name +
                ", capacity='" + capacity + '\'' +
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

    public int getCapacity() {
        return capacity;
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }
}
