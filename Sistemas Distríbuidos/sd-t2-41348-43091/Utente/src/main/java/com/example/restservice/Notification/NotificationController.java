package com.example.restservice.Notification;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
public class NotificationController {

    @Autowired
    private NotificationRepository repository;

    /**
     * Add Notification as POST request (from Centro de Vacinacao)
     * @param aux Notification
     * @return aux Notification
     */
    @PostMapping("/notifications")
    public Notification addNotification(@RequestBody Notification aux) {

        repository.save(new Notification(aux.getMessage(), aux.getUserid()));
        return aux;
    }
}
