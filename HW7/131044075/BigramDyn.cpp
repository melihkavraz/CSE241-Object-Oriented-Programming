/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//
//#include "BigramDyn.h"


#include "BigramDyn.h"
#include <fstream>
#include <iostream>
#include <map>

// CONSTRUCTORS

template <class T>
BigramDyn<T>::BigramDyn(int dataType) :capacity(50), used(0)
{
	dType = dataType;
    data = new pair< pair<T,T>, int >[capacity];
}

template <class T>
BigramDyn<T>::BigramDyn(const BigramDyn& myProg) :capacity(myProg.capacity), used(myProg.used)
{
	dType = myProg.dataType;
    data = new pair< pair<T,T>, int >[capacity];
    for(int i=0; i<capacity; i++)
        data[i] = myProg.data[i];
}

// = operator overload
template <class T>
BigramDyn<T>& BigramDyn<T>::operator =(const BigramDyn& myProg){
    
    if(capacity != myProg.capacity)
    {
        delete [] data;
        data = new string[myProg.capacity];
    }

    capacity = myProg.capacity;
    used = myProg.used;
    for(int i=0; i<used; i++)
        data[i] = myProg.data[i];
    return *this;
}

//helper function for << overload
template<class T>
void BigramDyn<T> :: getBigrams(ostream& outputStream)
{

    int max = data[0].second;
    
    for(int i=0; data[i].second != '\0'; ++i)
    {
        if(data[i].second > max)
        {
            max=data[i].second;
            ++i;
        }
    }
    
    for(int i=0; data[i].second != '\0'; ++i)
    {
        for(int j=0; data[j].second != '\0'; ++j)
        {
            if(data[j].second == max)
            {
                outputStream << data[j].first.first << " " << data[j].first.second
                        << " = " << data[j].second << endl;
            }
        }
        max--;
    }
}

// getter private data "int used"
template <class T>
int BigramDyn<T>::getUsed(){
    return used;
}

//getter for private data "data"
template <class T>
pair< pair<T,T>, int>* BigramDyn<T>::getData(){
    return data;
}

//takes a filename as a string parameter, reads the file, calculates all the bigrams.
template <class T>
void BigramDyn<T>::readFile(string filename){
    
    string temp, tmp;
    int foundItemIndex = -1;
	int count=0;
    ifstream infile, inCount;
    infile.open(filename);
	inCount.open(filename);
    if(infile.fail()){
        throw myExceptions("File reading error!");
    }   

	
	while(inCount>>tmp)
			count++;

	if(count==0)
			throw myExceptions("Empty Document");

	inCount.close();

    getline(infile, temp);

	if(dType==1)
    {
    
    int convertString;
   
        for(int j=0; temp[j]!='\0' ; ++j)
        {
                convertString = temp[j]-'0';
                if(!((convertString>=0 && convertString<=9 ) || temp[j]==' ') )
                        throw myExceptions("Wrong data type");			
        }	
         
    }

    
    if(dType == 3)
    {
        int convertString;
        for(int i=0; temp[i]!='\0' ; ++i){
            convertString = temp[i]-'0';
                if(!((convertString>=0 && convertString<=9 )|| temp[i]=='.' || temp[i]==' '))
                        throw myExceptions("Wrong data type");
        }
    }






    
    istringstream iss(temp);
    T word1, word2;
    iss >> word1;
    while(iss >> word2) {

        pair <T,T> icPair (word1,word2);
        
        pair< pair<T,T>, int> disPair (icPair, 0);
        
        for(int i=0; i<used; i++){
            if(icPair == data[i].first)
                foundItemIndex = i;
        }
            
        //Bulunamadıysa
        if(foundItemIndex == -1){
            if(used < capacity){
                data[used] = disPair;
                used++;
            }
            else{
                capacity *=2;
                pair< pair<T,T>, int >* tempData = new pair< pair<T,T>, int >[capacity];

                for(int i=0; i<used; i++)
                    tempData[i] = data[i];

                delete [] data;
                data = new pair< pair<T,T>, int >[capacity];

                for(int i=0; i<used; i++)
                    data[i] = tempData[i];

                delete [] tempData;

                data[used] = disPair;
                used++;
            }
            data[used-1].second = 1;
        }
        //Bulunduysa
        else {
            data[foundItemIndex].second++;
        }
        word1 = word2;
        foundItemIndex = -1;
    }


    infile.close();

}


//adds data to pair
template <class T>
void BigramDyn<T>::pushBack(pair< pair<T,T>, int > instruction){
    
    if(used < capacity){
        data[used] = instruction;
        used++;
    }
    else{
        capacity *=2;
        pair< pair<T,T>, int >* tempData = new pair< pair<T,T>, int >[capacity];

        for(int i=0; i<used; i++)
            tempData[i] = data[i];

        delete [] data;
        data = new pair< pair<T,T>, int >[capacity];

        for(int i=0; i<used; i++)
            data[i] = tempData[i];

        delete [] tempData;

        data[used] = instruction;
        used++;
    }
}


//DESTRUCTOR
template <class T>
BigramDyn<T>::~BigramDyn(){
    
    delete [] data;
}

template <class T>
int BigramDyn<T>::numGrams(){
    
    int total = 0;
    
    for(int i=0; i<used; i++){
        total += data[i].second;
    }

    return total;

}

//takes two elements as bigrams and returns the number of that bigram read so far
template <class T>
int BigramDyn<T>::numOfGrams(T first, T second){
    
    pair <T,T> icPair(first, second);
    
    for(int i=0; i<used; i++){
        if(icPair == data[i].first)
            return data[i].second;
    }
    
    return 0;
}

//returns the bigram that has occurred most frequently
template <class T>
pair<T,T> BigramDyn<T>::maxGrams(){
    
    
    int tempMax = 0;
    
    int lastIndex;
    
    for(int i=0; i<used; i++){
        if(data[i].second > tempMax){
            tempMax = data[i].second;
            lastIndex = i;
        }
    }
    
    return data[lastIndex].first;
}

