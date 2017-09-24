/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Computer.h
 * Author: melih5295
 *
 * Created on November 3, 2016, 6:43 PM
 */

#ifndef COMPUTER_H
#define COMPUTER_H

#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"

class Computer{
public:
    Computer(CPU& myCPU, CPUProgram& myCPUProgram, Memory& myMemory, int option);
    Computer(int option);
    void execute();
    
    // Setters
    void setCPU(CPU& myCPU);
    void setCPUProgram(CPUProgram& myProg);
    void setMemory(Memory& myMemory);
    
    // Getters
    CPU& getCPU() const;   
    CPUProgram& getCPUProgram() const;
    Memory& getMemory() const;
    
private:
    CPU* cmpCPU;
    CPUProgram* cmpCPUProgram;
    Memory* cmpMemory;
    int opt;
    
};


#endif /* COMPUTER_H */

