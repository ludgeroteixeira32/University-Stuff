package com.example.restservice.day;

import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface DayRepository extends CrudRepository<Day, Long> {

    Day findByDate(String date);
    List<Day> findAll();

    Day findByDateAndCenter(String date, String center);

}
