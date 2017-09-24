/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BigramDyn.h
 * Author: melih5295
 *
 * Created on December 25, 2016, 12:15 PM
 */

#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H

#include <string>
#include "Bigram.h"
#include "myExceptions.h"
//ostream& outputStream, const BigramDyn<T>& myProg
using namespace std;

template <class T>
class BigramDyn : public Bigram<T>
{
public:
    BigramDyn(int dataType);
    BigramDyn(const BigramDyn<T>& myProg);
    BigramDyn& operator =(const BigramDyn& myProg);
    virtual void getBigrams(ostream& outputStream)override;
    int getUsed();
    pair< pair<T,T>, int>* getData();
    virtual void pushBack(pair< pair<T,T>, int > instruction);
    virtual void readFile(string filename) override;
    virtual int numGrams() override;
    virtual int numOfGrams(T firstElement, T secondElement) override;
    virtual pair<T,T> maxGrams() override;
    
    ~BigramDyn();
private:
    pair< pair<T,T>, int >* data;
    int capacity;
    int used;
	int dType;
        
};

#endif /* BIGRAMDYN_H */
