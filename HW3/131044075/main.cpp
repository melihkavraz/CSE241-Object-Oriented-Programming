/* 
 * File:   main.cpp
 * Author: Muhammet Melih Kavraz
 *
 * Created on October 26, 2016, 11:45 PM
 */

#include <iostream>
#include "CPUProgram.h"
#include "CPU.h"


using namespace std;


int main(int argc, char** argv) {
    
    string filename(argv[1]);
    
    if(argc != 3){
        cerr<<"Missing command line argument"<<endl;
        return -1;
    } 
    
    CPUProgram myProg(filename);
    string instruction;
    CPU myCPU(argv[2]); 
    
    while(!myCPU.halted()) { 
        instruction = myProg.getLine(myCPU.getPC()-2);
        myCPU.execute(instruction); 
    }

    return 0;
}

