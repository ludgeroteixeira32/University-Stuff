package com.example.restservice.register;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.client.RestTemplate;

@Controller
public class RegisterController {

    @Autowired
    private RegisterRepository repository;


    @Value("${uri.DGS}")
    private String uri_DGS;

    /**
     * Send new Registers to DGS (POST request), delete them after
     * @return register-login-view
     */
    @GetMapping("/send-list")
    public String sendRegisters() {

        // create object with the list of registers
        RegisterList aux = new RegisterList(repository.findAll());
        RestTemplate restTemplate = new RestTemplate();

        // send to DGS with POST request
        aux = restTemplate.postForObject(uri_DGS + "/registers", aux, RegisterList.class);

        repository.deleteAll();
        return "send-list";
    }


    /**
     * Saves a new register
     * @param codX int
     * @param date String
     * @param vaccinetype String
     * @return register-vaccine-view
     */
    @GetMapping("/register-vaccine")
    public String addRegister(@RequestParam(value = "codX", defaultValue = "1") int codX,
                              @RequestParam(value = "date", defaultValue = "27-07-20") String date ,
                              @RequestParam(value = "vaccinetype", defaultValue = "0") String vaccinetype) {

        // save register in database
        repository.save(new Register(vaccinetype, codX, date));

        return "register-vaccine-view";
    }
}
