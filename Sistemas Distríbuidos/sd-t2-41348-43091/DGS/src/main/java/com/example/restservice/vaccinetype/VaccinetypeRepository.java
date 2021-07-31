package com.example.restservice.vaccinetype;

import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface VaccinetypeRepository extends CrudRepository<Vaccinetype, Long> {

    Vaccinetype findByName(String name);

    List<Vaccinetype> findAll();

    Vaccinetype findByNameAndDate(String name, String date);
}
