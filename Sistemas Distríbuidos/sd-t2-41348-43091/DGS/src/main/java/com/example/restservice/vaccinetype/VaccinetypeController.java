package com.example.restservice.vaccinetype;

import com.example.restservice.StartApplication;
import com.example.restservice.appointment.Appointment;
import com.example.restservice.appointment.AppointmentRepository;
import com.example.restservice.day.Day;
import com.example.restservice.day.DayRepository;
import com.example.restservice.vaccination_center.Vaccination_Center;
import com.example.restservice.vaccination_center.Vaccination_CenterRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.List;

@Controller
public class VaccinetypeController {

    @Autowired
    private VaccinetypeRepository vactyperepository;

    private static final Logger log = LoggerFactory.getLogger(StartApplication.class);

    /**
     * List vaccines per type and date
     * @return list-vaccinated
     */
    @GetMapping("/list-vaccinated")
    public String listVaccinated(Model model) {

        List<Vaccinetype> vaccinetypeList= vactyperepository.findAll();

        model.addAttribute("vaccinetypeList", vaccinetypeList);

        return  "list-vaccinated";
    }


}
