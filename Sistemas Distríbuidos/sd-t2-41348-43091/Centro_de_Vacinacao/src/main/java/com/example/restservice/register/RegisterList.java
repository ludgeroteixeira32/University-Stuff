package com.example.restservice.register;

import java.util.List;

public class RegisterList {

    private List<Register> registers;

    public RegisterList(List<Register> centers) {
        this.registers = centers;
    }

    public List<Register> getRegisters() {
        return registers;
    }

    public void setRegisters(List<Register> centers) {
        this.registers = centers;
    }

    public RegisterList() {

    }

}
