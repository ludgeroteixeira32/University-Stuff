package com.example.restservice.vaccination_center;

import com.example.restservice.Notification.Notification;
import com.example.restservice.appointment.Appointment;
import com.example.restservice.appointment.AppointmentList;
import com.example.restservice.day.Day;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Scope;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpMethod;
import org.springframework.mail.javamail.JavaMailSender;
import org.springframework.mail.javamail.MimeMessageHelper;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.client.RestTemplate;

import javax.mail.internet.MimeMessage;
import java.util.Collections;
import java.util.List;

@Controller
@Scope("session")
public class Vaccination_CenterController {

    private String name;

    private static final Logger log = LoggerFactory.getLogger(Vaccination_CenterController.class);

    @Value("${uri.DGS}")
    private String uri_DGS;

    @Value("${uri.Utente}")
    private String uri_Utente;

    @Autowired
    private JavaMailSender sender;

    /**
     * Register or Login the vaccination center (makes a PUT request to DGS)
     * @param name String
     * @param capacity int
     * @return "register-login-view"
     */
    @GetMapping("/register-login")
    public String addVaccination_Center(@RequestParam(name="name", defaultValue="Lisboa") String name,
                                  @RequestParam(name="capacity", defaultValue="0") int capacity){

        // save name of the center
        this.name = name;

        //create objeto vaccination center
        Vaccination_Center aux = new Vaccination_Center(name, capacity);
        RestTemplate restTemplate = new RestTemplate();

        // send request to DGS
        HttpEntity<Vaccination_Center> entity = new HttpEntity<>(aux);
        restTemplate.exchange(uri_DGS+"/vaccination_center", HttpMethod.PUT, entity, Vaccination_Center.class);

        return "register-login-view";
    }

    /**
     * Send Notifications (makes two GET requests to DGS and POST to Utente)
     * @param date String
     * @return "routine-view"
     */
    @GetMapping("/routine")
    public String sendNotifications(@RequestParam(name="date", defaultValue="2020-07-27") String date) throws Exception {

        RestTemplate restTemplate = new RestTemplate();

        //get object with the list from DGS
        AppointmentList response = restTemplate.getForObject(
                uri_DGS +"/appointmentlist/"+date+"/"+name,
                AppointmentList.class);

        // get list of appointments
        assert response != null;
        List<Appointment> appointmentsList = response.getAppointments();

        //get number of vaccines from DGS
        Day day = restTemplate.getForObject(
                uri_DGS +"/numvaccine/"+date+"/"+name,
                Day.class);

        Collections.sort(appointmentsList);

        assert day != null;
        int num = day.getTo_be_vaccinated();

        int i;

        // confirm appointment
        for(i = 0; i < num; i++)
        {
            String mess = "O seu agendamento foi confirmado para o dia: "+ appointmentsList.get(i).getDate();
            Notification aux = new Notification(mess, appointmentsList.get(i).getUserid());

            sendEmail(mess, appointmentsList.get(i).getEmail());
            aux = restTemplate.postForObject(uri_Utente + "/notifications", aux, Notification.class);

        }

        // cancel appointment
        for(i = num; i<appointmentsList.size() ; i++)
        {
            String mess = "O seu agendamento foi cancelado para o dia: "+ appointmentsList.get(i).getDate();
            Notification aux = new Notification(mess, appointmentsList.get(i).getUserid());

            sendEmail(mess, appointmentsList.get(i).getEmail());
            aux = restTemplate.postForObject(uri_Utente + "/notifications", aux, Notification.class);
        }

        return "routine-view";
    }

    private void sendEmail(String mess, String email) throws Exception{
        MimeMessage message = sender.createMimeMessage();
        MimeMessageHelper helper = new MimeMessageHelper(message);

        helper.setTo(email);
        helper.setText(mess);
        helper.setSubject("Agendamento da sua Vacina");

        sender.send(message);
    }

}
