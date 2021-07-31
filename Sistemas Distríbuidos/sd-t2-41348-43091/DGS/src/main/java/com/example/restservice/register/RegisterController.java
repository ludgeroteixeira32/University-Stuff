package com.example.restservice.register;

import com.example.restservice.appointment.Appointment;
import com.example.restservice.day.Day;
import com.example.restservice.day.DayRepository;
import com.example.restservice.vaccination_center.Vaccination_Center;
import com.example.restservice.vaccinetype.Vaccinetype;
import com.example.restservice.vaccinetype.VaccinetypeRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
public class RegisterController {

    @Autowired
    private RegisterRepository repository;

    @Autowired
    private VaccinetypeRepository vactyperepository;

    /**
     * Save new registers (for Centro de Vacinacao)
     * @param aux RegisterList
     * @return RegisterList
     */
    @PostMapping(value = "/registers")
    public RegisterList saveRegisters(@RequestBody RegisterList aux) {

        // get list of registers from object
        List<Register> list = aux.getRegisters();

        // for each register
        for(Register register: list)
        {
            Vaccinetype vaccinetype = vactyperepository.findByNameAndDate(register.getVaccinetype(), register.getDate());

            // if vaccine type doest exist in that date, create it, else add plus 1 to number of vaccines taken
            if(vaccinetype == null)
                vaccinetype = new Vaccinetype(register.getVaccinetype(), 1, register.getDate());
            else
                vaccinetype.setNum(vaccinetype.getNum() + 1);

            // save register and vaccine type data
            vactyperepository.save(vaccinetype);
            repository.save(register);
        }

        return aux;
    }

}
    
