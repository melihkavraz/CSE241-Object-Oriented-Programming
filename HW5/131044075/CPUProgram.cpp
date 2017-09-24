/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CPUProgram.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>  // for exit())

using namespace std;

// Constructors
CPUProgram::CPUProgram(const char* filename, int opt){
    
    ReadFile(filename);
    setOption(opt);
      
}

CPUProgram::CPUProgram(int opt){
    
    setOption(opt);
    
}

// Setter
void CPUProgram::setOption( int value ){
    
    option = value;
}


// Returns a string that contains the program line
string CPUProgram::getLine(int lineNumber) const{
    
    return data[lineNumber];
}


// Reads and stores all the program instructions
void CPUProgram::ReadFile(const char* filename){
    
    string temp;
    ifstream infile;
    infile.open(filename);
    if(infile.fail()){
        cerr<<"File reading error"<<endl;
        exit(1);
    }   
    
    while (!infile.eof()){
        getline(infile, temp);
        data.push_back(temp);
    }
    
    data.pop_back(); // eofden dolayı olusan size problemi için
    
    infile.close();
    
    if(checkSyntax()==false)
        exit(1);
}


// Okunan instruction satır satıyını döndürür
int CPUProgram::size() const{
    
    return data.size();
}


// Operator Overloads

string CPUProgram::operator [](int lineNumber){
    
    if(data.empty()){
        cerr<<"Operator[] can not get data because vector is empty\n";
        return "";
    }
    
    else if(!(0<=lineNumber && lineNumber<size())){
        cerr<<"Operator[] index is out of bounds\n";
        return "";
    }
    
    return data[lineNumber];
}


CPUProgram CPUProgram::operator +(string instruction) const{
    
    CPUProgram myProg = *this;
    myProg.data.push_back(instruction);
    return myProg;
}


CPUProgram& CPUProgram::operator +=(string instruction){
    
    data.push_back(instruction);
    return *this;
}


CPUProgram CPUProgram::operator +(const CPUProgram& myProg) const{
    
    CPUProgram myProg2 = *this;
    for(int i=0; i<myProg.size(); i++)
        myProg2.data.push_back(myProg.getLine(i));
    return myProg2;
}


bool CPUProgram::operator ==(const CPUProgram& myProg) const{
    
    return (size() == myProg.size());  
}


bool CPUProgram::operator !=(const CPUProgram& myProg) const{
    
    return (size() != myProg.size());
}


bool CPUProgram::operator <=(const CPUProgram& myProg) const{
    
    return (size() <= myProg.size());
}


bool CPUProgram::operator >=(const CPUProgram& myProg) const{
    
    return (size() >= myProg.size());
}


bool CPUProgram::operator <(const CPUProgram& myProg) const{
    
    return (size() < myProg.size());
}


bool CPUProgram::operator >(const CPUProgram& myProg) const{
    
    return (size() > myProg.size());
}


ostream& operator <<(ostream& outputStream, const CPUProgram& myProg){
    
    for(int i=0; i<myProg.size(); i++)
        outputStream<<myProg.data[i]<<endl;
    
    //outputStream<<endl;
    
    return outputStream;
}


const CPUProgram& CPUProgram::operator --(){
    
    if(data.size() != 0)
        data.pop_back();
    
    return *this;
}


const CPUProgram CPUProgram::operator --(int){
    
    CPUProgram myProg = *this;
    if(data.size() != 0)
        data.pop_back();
    
    return myProg;
}


const CPUProgram CPUProgram::operator ()(int startIndex, int lastIndex){
    
    CPUProgram myProg = *this;
    myProg.data.clear();
    
    if(data.empty()){
        cerr<<"Function call operator() can not get data because vector is empty\n";
        return myProg;
    }
    
    if(!(0<=startIndex && startIndex<size() && 0<lastIndex && lastIndex<=size())){
        cerr<<"Function call operator() out of bounds\n";
        return myProg;
    }
    
    for(int i=startIndex; i<=lastIndex; i++)
        myProg.data.push_back(data[i]);
    
    return myProg;
}


// String arrayindeki tüm küçük harfleri büyütür. Case sensitive'i ortadan kaldırır.
string CPUProgram::toUpper(string data){
    
    for(int j=0; j<data.size(); j++){
        if(data[j] >= 'a' && data[j] <= 'z' ){
            data[j] -= 'a' - 'A';
        }
    }
    
    return data;
    
}


// Stringi bölme işlemi yapılırken göz ardı edilecek karakterlerin en küçük
// indexli olanını return eder
int CPUProgram::min(string str, int startPos) const{
    
    size_t commaPos = str.find(',', startPos);
    size_t spacePos = str.find(' ',startPos);
    size_t enterPos = str.find('\n',startPos);
    size_t tabPos = str.find('\t',startPos);
    
    if(spacePos<enterPos && spacePos<tabPos && spacePos<commaPos)
        return spacePos;
    else if(enterPos<spacePos && enterPos<tabPos && enterPos<commaPos)
        return enterPos;
    else if(tabPos<spacePos && tabPos<enterPos && tabPos<commaPos)
        return tabPos;
    else
        return commaPos;
}

// Stringi integera çevirir
int CPUProgram::parseInt(string str){
    int total=0, temp, base=1;
    if(str[0]!='-'){
        for(int i=0; i<str.size(); i++){
            temp = str[i]-'0';
            for(int j=i+1; j<str.size(); j++)
                base*=10;
            total += temp * base;
            base = 1;
        }
    }
    else if(str[0]=='-'){
        for(int i=1; i<str.size(); i++){
            temp = str[i]-'0';
            for(int j=i+1; j<str.size(); j++)
                base*=10;
            total += temp * base;
            base = 1;
        }
        total *= -1;
    }
    return total;
}

// Tüm satırların syntaxını kontrol eder eğer hata varsa hiçbir işlem yapmadan
// hatayı gösterip programı bitirir
bool CPUProgram::checkSyntax(){
    
    size_t nearestPos;
    size_t semicolonPos;
    size_t commaPos;
    int count;
    int spaceSize;
    string  data, line, token, key, element1, element2; // bunları sonradan boşalt
    
    // getline ile çağırırken indexe 1 eklediğimizden
    // for döngüsünü -1den başlatıyorum
    for(int i=0; i<size(); i++){   
        
	int j=i+1;
        line = getLine(i);
        line = toUpper(line);
        nearestPos = min(line);
        semicolonPos = line.find(';');
        commaPos = line.find(',');
        count=0;
        spaceSize = 1;
        data = line, token, key, element1, element2; // bunları sonradan boşalt

        if(data.size()!=0){
     
            //Eleman sayısı kontrol
            if( (semicolonPos = data.find(';')) != string::npos){
                data = data.substr(0, semicolonPos); // tokena noktalı virgülü dahil etmiyor     
            }
            data.append("\n");

            while(data.size()!=0){
                nearestPos = min(data);
                token = data.substr(0, nearestPos); // tokena spacei dahil etmiyor
                data.erase(0, nearestPos + spaceSize); // spacei de dahil edip siliyor

                if(count==0)
                    key=token;
                else if(count==1)
                    element1=token;
                else if(count==2)
                    element2=token;


                if(token != " " && token != "\t" && token != "\n"){
                    //sadece virgül içeriyorsa countları artırma
                    if(!(token.find(',') !=string::npos && token.size()==1) && token.size()!=0)
                        count++;        
                }
            }


            if(key == "MOV"){
                if(count!=3){
                    cerr<<"[main.cpp:"<<j<<"] 'MOV' can take 2 operand\n";
                    return false;
                }
                else if(!isRegOrAddress(element1)){
                    cerr<<"[main.cpp:"<<j<<"] 'MOV' 1st operand have to be register or memory address\n";
                    return false;
                }
                else if(!isRegOrConstOrAddress(element2)){
                    cerr<<"[main.cpp:"<<j<<"] 'MOV' 2nd operand is undefinable\n";
                    return false;
                }
                
                if(isAddress(element1)){
                    if(isNumber(element2)){
                        if(!isAddressValueDefinable(parseInt(element2))){
                            cerr<<"[main.cpp:"<<j<<"] 'MOV' 1st (memory address) operand can only take value from 0 to 255\n";
                            return false;
                        }
                    }
                        
                    if(!isRegOrConstant(element2)){
                        cerr<<"[main.cpp:"<<j<<"] 'MOV' if 1st operand is an address, 2nd operand have to be register or constant\n";
                        return false;
                    }
                }
                else if(isAddress(element2)){
                    if(!isReg(element1)){
                        cerr<<"[main.cpp:"<<j<<"] 'MOV' if 2nd operand is an address, 1st operand have to be a register\n";
                        return false;
                    }
                        
                }
            }
            else if(key == "ADD"){
                if(count!=3){
                    cerr<<"[main.cpp:"<<j<<"] 'ADD' can take 2 operand\n";
                    return false;
                }
                else if(!isReg(element1)){
                    cerr<<"[main.cpp:"<<j<<"] 'ADD' 1st operand have to be register\n";
                    return false;
                }
                else if(!isRegOrConstOrAddress(element2)){
                    cerr<<"[main.cpp:"<<j<<"] 'ADD' 2nd operand is undefinable\n";
                    return false;
                }
            }
            else if(key == "SUB"){
                if(count!=3){
                    cerr<<"[main.cpp:"<<j<<"] 'SUB' can take 2 operand\n";
                    return false;
                }
                else if(!isReg(element1)){
                    cerr<<"[main.cpp:"<<j<<"] 'SUB' 1st operand have to be register\n";
                    return false;
                }
                else if(!isRegOrConstOrAddress(element2)){
                    cerr<<"[main.cpp:"<<j<<"] 'SUB' 2nd operand is undefinable\n";
                    return false;
                }
            }
            else if(key == "JMP"){
                if(!(count == 2 || count == 3)){
                    cerr<<"[main.cpp:"<<j<<"] 'JMP' can take 1 or 2 operand\n";
                    return false;
                }
                else if(!isRegOrConstant(element1)){
                    cerr<<"[main.cpp:"<<j<<"] 'JMP' 1st operand is undefinable\n";
                    return false;
                }
                else if(element2.size()>0){
                    if(!isNumber(element2)){
                        cerr<<"[main.cpp:"<<j<<"] 'JMP' 2nd operand is not lineAddress\n";
                        return false;
                    }
                }
            }
            
            else if(key == "JPN"){
                if(count != 3){
                    cerr<<"[main.cpp:"<<j<<"] 'JPN' can take 2 operand\n";
                    return false;
                }
                else if(!isReg(element1)){
                    cerr<<"[main.cpp:"<<j<<"] 'JPN' 1st operand is not a register\n";
                    return false;
                }
                else if(!isNumber(element2)){
                        cerr<<"[main.cpp:"<<j<<"] 'JPN' 2nd operand is not lineAddress\n";
                        return false;
                }
            }
            
            
            else if(key == "PRN"){
                if(count!=2){
                    cerr<<"[main.cpp:"<<j<<"] 'PRN' can take 1 operand\n";
                    return false;
                }
                else if(!isRegOrConstOrAddress(element1)){
                    cerr<<"[main.cpp:"<<j<<"] 'PRN' 1st operand is undefinable\n";
                    return false;
                }
            }
            else if(key == "HLT"){
                if(count!=1){
                    cerr<<"[main.cpp:"<<j<<"] 'HLT' can take only 1 operand\n";
                    return false;
                }
            }
            else{
                cerr<<"[main.cpp:"<<j<<"] opcode can not be found\n";
                return false;
            }


            //Noktalı virgülden önceki virgül sayısı 1den fazla mı kontrol ediliyor
            if (count == 3){
                
                size_t element1_pos = line.find(element1);
                size_t element2_pos = line.find(element2);
                size_t comma_pos = line.find(',');

                if(commaPos == string::npos){
                    cerr<<"[main.cpp:"<<j<<"] There is no ',' between 2 operand\n";
                    return false;
                }
                else if(semicolonPos == string::npos){
                    if(line.find(",",commaPos+1,1) != string::npos){
                        cerr<<"[main.cpp:"<<j<<"] It has to be only 1 ','\n";
                        return false;
                    }
                }

                else if(commaPos<semicolonPos){
                    if( (commaPos = line.find(",", commaPos+1,1)) != string::npos){
                        if(commaPos<semicolonPos){
                            cerr<<"[main.cpp:"<<j<<"] It has to be only 1 ',' before ';'\n";
                            return false;
                        }
                    }
                }
                // virgül iki eleman arasında mı kontrol ediliyor
                else if(!(element1_pos + element1.size()-1 < comma_pos && comma_pos < element2_pos)){
                    cerr<<"[main.cpp:"<<j<<"] It has to be ',' between 2 operand\n";
                    return false;
                }
            }

            else if(count == 2){
                
                if(semicolonPos == string::npos && commaPos != string::npos){
                    cerr<<"[main.cpp:"<<j<<"] ',' can not be used here\n";
                    return false;
                }
                else if(semicolonPos != string::npos && commaPos != string::npos){
                    cerr<<"[main.cpp:"<<j<<"] ',' can not be used here\n";
                    return false;
                }
            }
        }
    }
    
    return true;
}


// String içindeki bir sayıyı temsil ediyorsa true return eder
bool CPUProgram::isNumber(string str) const{
    
    int i;
    if(str[0]!='-'){
        for(i=0; i<str.size(); i++){
            if(!('0'<= str[i] && str[i]<='9'))
                return false;
        }
    }
    else if(str[0]=='-'){
        for(i=1; i<str.size(); i++){
            if(!('0'<= str[i] && str[i]<='9'))
                return false;
        }
    }
    return true;
}

// String içindeki bir registerı temsil ediyorsa true return eder
bool CPUProgram::isReg(string str) const{
    
    if(str.size() != 2)
        return false;
    if(str[0] !='R')
        return false;
    if(!('1' <= str[1] && str[1] <= '5'))
        return false;
    return true;
}

bool CPUProgram::isAddress(string str){
    
    int num;
    
    if(str.size() > 3)
        return false;
    if(str[0] != '#')
        return false;
    
    if(str.size() == 3)
        num = parseInt(str.substr(1,2));
    else if(str.size() == 2)
        num = parseInt(str.substr(1,1));
    
    if( num<0 || num>50 )
        return false;
    return true;
}

bool CPUProgram::isAddressValueDefinable(int number){
    
    if(0<=number && number<=255)
        return true;
    else
        return false;
}

// String içindeki sabit bir sayı veya register ise true return eder
bool CPUProgram::isRegOrConstant(string str) const{
    
    if(isReg(str) || isNumber(str))
        return true;
    else
        return false;
}

bool CPUProgram::isRegOrAddress(string str){
    if(isReg(str) || isAddress(str))
        return true;
    else
        return false;
}

bool CPUProgram::isRegOrConstOrAddress(string str){
    if(isRegOrConstant(str) || isAddress(str))
        return true;
    else
        return false;
        
    
}

