/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Computer.h"


Computer::Computer(CPU& myCPU, CPUProgram& myCPUProgram, Memory& myMemory, int option){
    cmpCPU = &myCPU;
    cmpCPUProgram = &myCPUProgram;
    cmpMemory = &myMemory;
    opt = option;
}

Computer::Computer(int option){
    opt = option;
}

void Computer::execute(){
    
    std::string instruction;
    
    while(!cmpCPU->halted()) { 
        instruction = cmpCPUProgram->getLine(cmpCPU->getPC()-1);
        cmpCPU->execute(instruction, *cmpMemory); 
    }
}

void Computer::setCPU(CPU& myCPU){
    cmpCPU = &myCPU;
}


void Computer::setCPUProgram(CPUProgram& myProg){
    cmpCPUProgram = &myProg;
}


void Computer::setMemory(Memory& myMemory){
    cmpMemory = &myMemory;
}


CPU& Computer::getCPU() const{
    return *cmpCPU;
}


CPUProgram& Computer::getCPUProgram() const{
    return *cmpCPUProgram;
}


Memory& Computer::getMemory() const{
    return *cmpMemory;
}