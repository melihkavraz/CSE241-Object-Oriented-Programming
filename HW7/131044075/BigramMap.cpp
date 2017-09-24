/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "BigramMap.h"
#include <fstream>
#include <iostream>
#include <map>


//CONSTRUCTOR
template <class T>
BigramMap<T>::BigramMap(int dataType){
    
    dType = dataType;
  
}


//takes a filename as a string parameter, reads the file, calculates all the bigrams.
template <class T>
void BigramMap<T>::readFile(string filename){
    
    string temp, tmp;
	int count=0;
    ifstream infile, inCount;
    infile.open(filename);
	inCount.open(filename);
    if(infile.fail()){
        throw myExceptions("File reading error!");
    }   

    getline(infile, temp);


	while(inCount>>tmp)
		count++;

	inCount.close();


	if(count==0)
			throw myExceptions("Empty Document");
    
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
        /* do stuff with word */

        pair <T,T> first (word1,word2);
        auto ite = mymap.find(first);
        
        if(ite != mymap.end())
            mymap[first]++;
        else {
            mymap[first] = 1;
        }
        
        word1 = word2;
    }
    

    infile.close();

}

//helper function for << overload
template<class T>
void BigramMap<T> :: getBigrams(ostream& outputStream)
{

    map< string, pair<T,T>> tempMap;

    string temp;
    int convertString;
    ostringstream strs;
	size_t found=0;
    
    for(auto ite = mymap.begin(); ite != mymap.end(); ite++) {
        strs << ite->second << ite->first.first << ite->first.second;
        temp = strs.str();
		strs.str("");
		strs.clear();
		
        tempMap[temp] = ite->first;
    }
    
    for(auto ite = tempMap.rbegin(); ite != tempMap.rend(); ite++) {

		strs << ite->second.first << ite->second.second;
		temp = strs.str();
		strs.str("");
		strs.clear();

		if( (found = ite->first.find(temp)) != string::npos)
            temp = ite->first.substr(0, found);
     
        outputStream<< ite->second.first << " " 
                << ite->second.second << " = "<<temp << endl;
    }
    
       
}

//returns the total number of bigrams calculated so far
template <class T>
int BigramMap<T>::numGrams(){
	
	int total = 0;    

	for(auto ite = mymap.begin(); ite != mymap.end(); ite++) {

        total += ite->second;

    }

	return total;
}


//takes two elements as bigrams and returns the number of that bigram read so far.
template <class T>
int BigramMap<T>::numOfGrams(T first, T second){
    
    pair <T,T> foo(first, second);
    
    for(auto ite = mymap.begin(); ite != mymap.end(); ite++) {

        if(ite->first == foo){
            return ite->second;
        }

    }
    
    return 0;
}

//returns the bigram that has occurred most frequently
template <class T>
pair<T,T> BigramMap<T>::maxGrams(){
    
    
    int tempMax = 0;
    
    auto iteLast = mymap.begin();
    
    for(auto ite = mymap.begin(); ite != mymap.end(); ite++) {
        
        if(ite->second > tempMax){
            tempMax = ite->second;
            iteLast = ite;
        }

    }
    
    return iteLast->first;
}

