/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Memory.h
 * Author: melih5295
 *
 * Created on November 3, 2016, 6:42 PM
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include "CPUProgramDyn.h"

using namespace std;
using namespace MelihKavraz;

class Memory{
public:
    Memory(int option);
    void setMem(int index, uint8_t number);
    int getMem(int index)const;
    const void printAll();
    
private:
    uint8_t memory[50];
    
};


#endif /* MEMORY_H */

