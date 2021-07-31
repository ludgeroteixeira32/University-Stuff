package com.example.restservice;

import com.example.restservice.Appointment.Appointment;
import com.example.restservice.Notification.NotificationRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Scope;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpMethod;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.stereotype.Controller;
import org.springframework.web.client.RestTemplate;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.ui.Model;
import com.example.restservice.Vaccination_Center.*;


import java.util.List;

import static java.lang.Integer.parseInt;

@Controller
@Scope("session")
public class UserController {

    private int id;

    @Autowired
    private NotificationRepository repository;

    public static final int TO_BE_CONFIRM = 0;

    private static final Logger log = LoggerFactory.getLogger(UserController.class);

    @Value("${uri.DGS}")
    private String uri_DGS;


    /**
     * Saves the id of the user and display his notifications
     * @param id int
     * @return options-view
     */
    @PostMapping("/options")
    public String saveUser(@RequestParam(name="id", defaultValue="1") int id, Model model) {
        // save id
        this.id = id;

       // pass to view the notification list of the user
       model.addAttribute("notificationslist",repository.findByUserid(id));

       return "options-view";
    }


    /**
     * Saves a new appointment to DGS (PUT request)
     * @param name String
     * @param age int
     * @param email String
     * @param center String
     * @param date String
     * @return agendamentoconcluido
     */
    @GetMapping("/agendamento")
    public String addAppointment(@RequestParam(name="name", defaultValue="0") String name,
                                                @RequestParam(name="age", defaultValue="0") int age,
                                                @RequestParam(name="email", defaultValue="0") String email,
                                                @RequestParam(name="center", defaultValue="0") String center,
                                                @RequestParam(name="date", defaultValue="2020-07-27") String date, Model model){

        // create appointment
        Appointment aux = new Appointment(date, age, center, name, email, id, TO_BE_CONFIRM);
        RestTemplate restTemplate = new RestTemplate();
        HttpEntity<Appointment> entity = new HttpEntity<>(aux);

        // do PUT request to DGS
        ResponseEntity<Appointment> update = restTemplate.exchange(uri_DGS + "/appointment", HttpMethod.PUT, entity, Appointment.class);

        // pass codX to view
        model.addAttribute("codX",update.getBody().getId());
        return "agendamentoconcluido";
    }


    /**
     * Get Vaccination Centers from DGS (GET request)
     * @param model Model
     * @return centers
     */
    @GetMapping("/centers")
    public String getCenters(Model model) {

        RestTemplate restTemplate = new RestTemplate();

        //get object with the list of centers from DGS
        Vaccination_CenterList response = restTemplate.getForObject(
                uri_DGS +"/vaccination_center",
                Vaccination_CenterList.class);

        // get list of centers
        assert response != null;
        List<Vaccination_Center> centersList = response.getCenters();

        // add list as attribute to model
        model.addAttribute("centerList", centersList);

        return "centers";
    }


}
