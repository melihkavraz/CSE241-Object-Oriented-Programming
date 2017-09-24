/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bigram.h
 * Author: melih5295
 *
 * Created on December 25, 2016, 11:44 AM
 */

#ifndef BIGRAM_H
#define BIGRAM_H
//ostream& outputStream, const Bigram<T>& myProg
#include <string>
#include "myExceptions.h"

using namespace std;

template <class T>
class Bigram {
public:
    virtual void readFile(string filename) = 0;
    virtual int numGrams() = 0;
    virtual int numOfGrams(T firstElement, T secondElement) = 0;
    friend ostream & operator <<(ostream & outputStream, Bigram & myProg)
    {
        myProg.getBigrams(outputStream);
        return outputStream;
    }
    virtual void getBigrams(ostream& outputStream)=0;
    virtual pair<T,T> maxGrams() = 0;
};



#endif /* BIGRAM_H */
