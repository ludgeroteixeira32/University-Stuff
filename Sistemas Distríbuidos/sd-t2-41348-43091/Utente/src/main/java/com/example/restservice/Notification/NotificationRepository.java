package com.example.restservice.Notification;

import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface NotificationRepository extends CrudRepository<Notification, Long> {

    List<Notification> findAll();

    List<Notification> findByUserid(int userid);
}
