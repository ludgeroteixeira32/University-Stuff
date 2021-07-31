package com.example.restservice.appointment;

import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface AppointmentRepository extends CrudRepository<Appointment, Long> {

    List<Appointment> findAll();

    List<Appointment> findByDateOrderByAgeDesc(String date);

    List<Appointment> findByDateAndCenter(String date,String center);

    Appointment findByUserid(int userid);

}
