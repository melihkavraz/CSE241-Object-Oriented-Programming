/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Computer.h"


Computer::Computer(CPU& myCPU, CPUProgramDyn& myCPUProgramDyn, Memory& myMemory, int option){
    cmpCPU = &myCPU;
    cmpCPUProgramDyn = &myCPUProgramDyn;
    cmpMemory = &myMemory;
    opt = option;
}

Computer::Computer(int option){
    opt = option;
}

void Computer::execute(){
    
    std::string instruction;
    
    while(!cmpCPU->halted()) { 
        instruction = cmpCPUProgramDyn->getLine(cmpCPU->getPC()-1);
        cmpCPU->execute(instruction, *cmpMemory); 
    }
}

void Computer::setCPU(CPU& myCPU){
    cmpCPU = &myCPU;
}


void Computer::setCPUProgramDyn(CPUProgramDyn& myProg){
    cmpCPUProgramDyn = &myProg;
}


void Computer::setMemory(Memory& myMemory){
    cmpMemory = &myMemory;
}


CPU& Computer::getCPU() const{
    return *cmpCPU;
}


CPUProgramDyn& Computer::getCPUProgramDyn() const{
    return *cmpCPUProgramDyn;
}


Memory& Computer::getMemory() const{
    return *cmpMemory;
}
