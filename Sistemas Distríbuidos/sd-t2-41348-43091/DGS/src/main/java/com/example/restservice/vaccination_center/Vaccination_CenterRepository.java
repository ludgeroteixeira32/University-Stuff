package com.example.restservice.vaccination_center;

import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface Vaccination_CenterRepository extends CrudRepository<Vaccination_Center, Long> {

    Vaccination_Center findByName(String name);

    List<Vaccination_Center> findAll();

}
