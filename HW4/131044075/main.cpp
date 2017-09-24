/* 
 * File:   main.cpp
 * Author: Muhammet Melih Kavraz
 *
 * Created on October 26, 2016, 11:45 PM
 */

#include <iostream>
#include "Computer.h"
#include "CPUProgram.h"
#include "CPU.h"
#include "Memory.h"


using namespace std;


int main(int argc, char** argv) {
    
    int option = atoi(argv[2]);   
    const char* filename = argv[1];
    
    if(argc != 3){
        cerr<<"Missing command line argument"<<endl;
        return -1;
    } 
    
    Memory myMemory(option);
    CPU myCPU(option);
    CPUProgram myCPUProgram(option);
    myCPUProgram.ReadFile(filename);
     
//    //Testing class Memory    
//    Memory myMemory(option);
//    myMemory.setMem(0, 100);
//    cout << myMemory.getMem(0) << endl;
//    myMemory.printAll();  
//    
//    //Testing class CPU CPU
//    CPU myCPU(option);
//    myCPU.execute("MOV #0, R1", myMemory);
//    myCPU.execute("MOV R1, #1", myMemory);
//    myCPU.print();
//    
//    //Testing class CPUProgram CPUProgram
//    CPUProgram myCPUProgram(option);
//    myCPUProgram.ReadFile(filename);
//    cout << myCPUProgram.getLine(0) << endl; 
//    cout << myCPUProgram.getLine(myCPUProgram.size() - 1) << endl;
    
    //Testing class Computer
    Computer myComputer1(myCPU, myCPUProgram, myMemory, option);
    Computer myComputer2(option);
    myComputer2.setCPU( myComputer1.getCPU() );
    myComputer2.setCPUProgram(myComputer1.getCPUProgram());
    myComputer2.setMemory(myComputer1.getMemory() );
    myComputer2.execute();
    

    return 0;
}

