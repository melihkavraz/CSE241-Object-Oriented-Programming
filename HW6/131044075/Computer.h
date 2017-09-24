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
#include "CPUProgramDyn.h"
#include "Memory.h"

using namespace std;
using namespace MelihKavraz;

class Computer{
public:
    Computer(CPU& myCPU, CPUProgramDyn& myCPUProgramDyn, Memory& myMemory, int option);
    Computer(int option);
    void execute();
    
    // Setters
    void setCPU(CPU& myCPU);
    void setCPUProgramDyn(CPUProgramDyn& myProg);
    void setMemory(Memory& myMemory);
    
    // Getters
    CPU& getCPU() const;   
    CPUProgramDyn& getCPUProgramDyn() const;
    Memory& getMemory() const;
    
private:
    CPU* cmpCPU;
    CPUProgramDyn* cmpCPUProgramDyn;
    Memory* cmpMemory;
    int opt;
    
};


#endif /* COMPUTER_H */

