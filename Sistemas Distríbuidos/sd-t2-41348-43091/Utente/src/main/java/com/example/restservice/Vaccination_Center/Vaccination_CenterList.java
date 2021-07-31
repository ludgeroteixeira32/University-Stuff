package com.example.restservice.Vaccination_Center;

import java.util.List;

public class Vaccination_CenterList {

    private List<Vaccination_Center> centers;

    public Vaccination_CenterList(List<Vaccination_Center> centers) {
        this.centers = centers;
    }

    public List<Vaccination_Center> getCenters() {
        return centers;
    }

    public void setCenters(List<Vaccination_Center> centers) {
        this.centers = centers;
    }

    public Vaccination_CenterList() {
        
    }

}
