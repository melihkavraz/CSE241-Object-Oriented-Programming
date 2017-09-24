/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BigramMap.h
 * Author: melih5295
 *
 * Created on December 25, 2016, 12:15 PM
 */

#ifndef BIGRAMMAP_H
#define BIGRAMMAP_H

#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include "myExceptions.h"
#include "Bigram.h"

using namespace std;

template <class T>
class BigramMap : public Bigram<T>
{
public:
    BigramMap(int dataType);
    virtual void getBigrams(ostream& outputStream)override;
    virtual void readFile(string filename) override;
    virtual int numGrams() override;
    virtual int numOfGrams(T first, T second) override;
    //friend ostream& operator <<(ostream& outputStream, const bigram& myProg);
    virtual pair<T,T> maxGrams() override;
private:
    map< pair<T,T>, int > mymap;
    int dType;
};



#endif /* BIGRAMMAP_H */

