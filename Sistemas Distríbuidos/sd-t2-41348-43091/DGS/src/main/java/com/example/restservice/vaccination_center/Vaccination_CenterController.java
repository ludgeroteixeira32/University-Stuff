package com.example.restservice.vaccination_center;


import com.example.restservice.appointment.Appointment;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.client.RestTemplate;

import java.util.List;

import static java.lang.Integer.parseInt;

@RestController
public class Vaccination_CenterController {

    @Autowired
    private Vaccination_CenterRepository repository;

    /**
     * Display the object Vaccination_CenterList that has a list of all vaccination centers (for Utente)
     * @return Vaccination_CenterList
     */
    @GetMapping("/vaccination_center")
    public Vaccination_CenterList getVaccination_Center() {
        return new Vaccination_CenterList(repository.findAll());
    }


    /**
     * Save/Update vaccination center (for Centro de Vacinacao)
     * @param aux Vaccination_Center
     * @return
     */
    @PutMapping(value = "/vaccination_center")
    public void updateVaccinationCenter(@RequestBody Vaccination_Center aux) {

        Vaccination_Center vac = repository.findByName(aux.getName());

        // if the user dont exist, a user with the same id, update user
        if(vac == null)
            aux = new Vaccination_Center(aux.getName(), aux.getCapacity());
        else
            aux.setId(vac.getId());

        repository.save(aux);
    }

}