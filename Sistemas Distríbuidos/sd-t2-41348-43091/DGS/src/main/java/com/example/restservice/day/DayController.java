package com.example.restservice.day;

import com.example.restservice.StartApplication;
import com.example.restservice.appointment.Appointment;
import com.example.restservice.appointment.AppointmentRepository;
import com.example.restservice.register.RegisterRepository;
import com.example.restservice.vaccination_center.Vaccination_Center;
import com.example.restservice.vaccination_center.Vaccination_CenterRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.web.client.RestTemplateBuilder;
import org.springframework.context.annotation.Bean;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.client.RestTemplate;

import static java.lang.Integer.parseInt;
import java.util.List;

@Controller
public class DayController {

    @Autowired
    private AppointmentRepository Apprepository;

    @Autowired
    private DayRepository Dayrepository;

    @Autowired
    private Vaccination_CenterRepository Vacrepository;

    public static final int CONFIRMED = 1;

    /**
     * Distribute appointments for the day
     * @param vaccines int
     * @param date String
     * @return distribute-vaccines-view
     */
    @GetMapping("/distribute-vaccines")
    public String distributeAppointment(
            @RequestParam(value = "vaccines", defaultValue = "11") int vaccines,
            @RequestParam(value = "date", defaultValue = "2020-07-27") String date) {

        List<Appointment> app = Apprepository.findByDateOrderByAgeDesc(date);

        for(int i=0; i<vaccines & i<app.size() ; i++) {

            Appointment aux = app.get(i);

            // get day, with date and the center
            Day d = Dayrepository.findByDateAndCenter(date,aux.getCenter());

            if(d == null) {

                // if null, it doest exist and app is confirmed
                d = new Day(date, 1, aux.getCenter());
                aux.setStatus(CONFIRMED);
            } else {

                // else see capacity of the center
                Vaccination_Center vac = Vacrepository.findByName(aux.getCenter());

                // if the capacity is not on its limit, confirmed app
                if (vac.getCapacity() > d.getTo_be_vaccinated())
                {
                    d.setTo_be_vaccinated(d.getTo_be_vaccinated()+1);
                    aux.setStatus(CONFIRMED);
                }
            }

            // save day with number update and appointment as confirmed
            Dayrepository.save(d);
            Apprepository.save(aux);
        }

        return  "distribute-vaccines-view";
    }



}