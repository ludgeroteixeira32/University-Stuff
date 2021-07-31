package com.example.restservice.appointment;

import com.example.restservice.vaccination_center.Vaccination_Center;

import java.util.List;

public class AppointmentList {

    private List<Appointment> appointments;

    public AppointmentList(List<Appointment> appointments) {
        this.appointments = appointments;
    }

    public List<Appointment> getAppointments() {
        return appointments;
    }

    public void setAppointments(List<Appointment> appointments) {
        this.appointments = appointments;
    }
}
