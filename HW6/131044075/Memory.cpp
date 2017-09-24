/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Memory.h"
#include <iostream>

Memory::Memory(int option){
    for(int i=0; i<50; i++)
        memory[i]=0;
}

int Memory::getMem(int index) const{
    return memory[index];
}

void Memory::setMem(int index, uint8_t number){
    memory[index] = number;
}

const void Memory::printAll(){
    
    std::cout<<"Memory Values:\n";
    
    for(int i=0; i<50; i++){
        std::cout << " [" << i << "]->" << (int)getMem(i);
        if((i+1)%10==0)
            std::cout << std::endl;
    }
    
    std::cout << std::endl << std::endl;
    
}

