package com.example.restservice.register;

import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface RegisterRepository extends CrudRepository<Register, Long> {

    List<Register> findAll();


}
