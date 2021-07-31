package com.example.restservice.appointment;

import com.example.restservice.StartApplication;
import com.example.restservice.day.Day;
import com.example.restservice.day.DayRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.List;


@RestController
public class AppointmentController {

    @Autowired
    private AppointmentRepository repository;

    @Autowired
    private DayRepository Dayrepository;

    public static final int TO_BE_CONFIRM = 0;

    /**
     * Save/Update appointment (for Utente)
     * @param aux Appointment
     * @return
     */
    @PutMapping(value = "/appointment")
    public Appointment updateAppointment(@RequestBody Appointment aux) {

        Appointment app = repository.findByUserid(aux.getUserid());

         // if the user dont exist, a user with the same id, update user
        if(app == null)
            aux = new Appointment(aux.getDate(), aux.getAge(), aux.getCenter(), aux.getName(), aux.getEmail(), aux.getUserid(), TO_BE_CONFIRM);
        else
            aux.setId(app.getId());

        repository.save(aux);
        return aux;
    }

    /**
     * List Appointment by date and center (for Vaccination Center)
     * @param date String
     * @param center String
     * @return List<Appointment>
     */
    @GetMapping("/appointmentlist/{date}/{center}")
    public AppointmentList listAppointment(@PathVariable String date, @PathVariable String center) {
        return new AppointmentList(repository.findByDateAndCenter(date, center));
    }

    /**
     * Number of vaccines for center by date (for Vaccination Center)
     * @param date String
     * @param center String
     * @return int
     */
    @GetMapping("/numvaccine/{date}/{center}")
    public Day num_to_be_Vaccinated(@PathVariable String date, @PathVariable String center) {
        return Dayrepository.findByDateAndCenter(date, center);
    }

}
