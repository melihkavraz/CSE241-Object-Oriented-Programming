/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPU.h
 * Author: melih5295
 *
 * Created on October 24, 2016, 7:52 PM
 */

#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <string>

class CPU {
public:

    CPU( char * );
    void print() const;
    bool halted() const;
    void execute( std::string );
    
    
    //Getters
    int getPC() const;
    int getReg( int ) const;
    
    //Setters
    void setPC( int );
    void setReg( int, int );
    void setIsFinished( bool );
    void setOption( int );

private:

    int PC, R[6], option;
    bool isFinished;
    
    int parseInt(std::string str);
    int min(std::string str, int startPos=0);
    std::string toUpper(std::string data);
    bool isReg(std::string);

    //Instructions
    void add(int reg, int number);
    void sub(int reg, int number);
    bool jmp(int lineAddress, int reg=0);
    void prn(int number);
    void hlt(int* reg);
    
};


#endif /* CPU_H */

