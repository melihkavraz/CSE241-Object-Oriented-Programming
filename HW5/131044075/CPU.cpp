/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CPU.h"
#include <iostream>

using namespace std;


CPU::CPU(int opt){
    
    setPC(1);
    setReg( 1, 0 );
    setReg( 2, 0 );
    setReg( 3, 0 );
    setReg( 4, 0 );
    setReg( 5, 0 );
    setIsFinished(false);
    setOption(opt);
    
}

// Prints all the registers and the PC
void CPU::print() const{
    
    cout << "CPU Register Values:\n" << "PC=" << PC;
    
    for(int i=1; i<=5; i++){
        std::cout << " R[" << i << "]=" << getReg(i) << " "; 
    }
    
    cout << endl;
}

// Returns true if the last instruction executed halted the CPU
bool CPU::halted() const{
    
    if(isFinished)
        return true;
    else
        return false;
}


// Getters
int CPU::getPC()const{
    
    return PC;
}

int CPU::getReg(int i) const{
    
    return R[i];
}


// Setters
void CPU::setPC(int value){
    
    PC = value;
}

void CPU::setReg(int i, int value){
    
    R[i] = value;
}

void CPU::setIsFinished( bool value ){
    
    isFinished = value;
}

void CPU::setOption( int value ){
    
    option = value;
}


// Instructionları parçalar ve uygun fonksiyonu çağırır
//// jmpde startLine yerine pc kullanılacak
//void CPU::instructionPartition(string data){
void CPU::execute( string data , Memory& myMemory){

    bool jmpResult, jpnResult;
    int count=0;
    int i=0;
    int regIndex1, regIndex2;
    string key;
    size_t semicolonPos=0;
    size_t nearestPos=0, oldNearestPos=-1;//-1 olma nedeni döngüye ilk girişte 0 ile nearestPos arası kontrol edilmesi gerek
    string token, element1, element2;
    size_t spaceSize = 1;  
    
    // Case sensitiveliği ortadan kaldırıyoruz
    data = toUpper(data);
    
    if( (semicolonPos = data.find(';')) != string::npos)
        data = data.substr(0, semicolonPos);
    
    data.append("\n");
    
    while  (data.size()!=1 && nearestPos != string::npos){
        nearestPos = min(data,oldNearestPos+spaceSize); 
        token = data.substr(oldNearestPos+spaceSize, nearestPos-oldNearestPos-spaceSize); // tokena spacei dahil etmiyor
        oldNearestPos = nearestPos;

        if( (semicolonPos = token.find(';')) != string::npos)
            token = token.substr(0, semicolonPos); // tokena semicolonu dahil etmiyor

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
        
        if(!(isAddress(element1) || isAddress(element2))){
            regIndex1 = element1[1]-'0';
            if(isReg(element2)){
                regIndex2 = element2[1]-'0';
                setReg(regIndex2, R[regIndex1]);
            }
            else
                setReg(regIndex1, parseInt(element2));
        }        
        else if(isAddress(element1)){
            if(isReg(element2)){
                regIndex2 = element2[1]-'0';
                setReg(regIndex2, (int)myMemory.getMem( parseAddress(element1) ));
            }
            else{
                if( !( parseInt(element2)<=255 && parseInt(element2)>=0) ){
                    cerr<<"[main.cpp:"<<i<<"] 'MOV' 1st (memory address) operand can only take value from 0 to 255\n";
                    return; 
                }
                
                myMemory.setMem(parseAddress(element1), parseInt(element2));
            }
        }
        else{
            regIndex1 = element1[1]-'0';
            if(!(getReg(regIndex1)<=255 && getReg(regIndex1)>=0)){
                cerr<<"[main.cpp:"<<i<<"] 'MOV' 2nd (memory address) operand can only take value from 0 to 255\n";
                return; 
            }
            myMemory.setMem(parseAddress(element2), getReg(regIndex1));
        }

    }
    
    else if(key == "ADD"){
        
        regIndex1 = element1[1]-'0';
        if(isReg(element2)){
            regIndex2 = element2[1]-'0';
            add( regIndex1, R[regIndex2] );
        }
        else if(isAddress(element2)){
            add( regIndex1, myMemory.getMem( parseAddress(element2) ) );
        }
        else
            add( regIndex1, parseInt(element2) );
    }
    
    else if(key == "SUB"){
        
        regIndex1 = element1[1]-'0';
        if(isReg(element2)){
            regIndex2 = element2[1]-'0';
            sub(regIndex1, R[regIndex2]);
        }
        else if(isAddress(element2)){
            sub(regIndex1, myMemory.getMem( parseAddress(element2) ));
        }
        else
            sub(regIndex1, parseInt(element2));
    }
    else if(key == "JMP"){
        
        if(element2.empty()){
            
            jmpResult = jmp(parseInt(element1));
            if(jmpResult==true)
                setPC( parseInt(element1)-1 ); // fonksiyondan çıkmadan 1 artırılacağı için -1
        }
        
        else{
            
            regIndex1 = element1[1]-'0';
            jmpResult = jmp(parseInt(element2), getReg(regIndex1));
            
            if(jmpResult==true)
                setPC( parseInt(element2)-1 ); // fonksiyondan çıkmadan 1 artırılacağı için -1 
        }
        
    }
    
    else if(key == "JPN"){
        regIndex1 = element1[1]-'0';
        jpnResult = jpn(parseInt(element2), R[regIndex1]);
        if(jpnResult==true)
            setPC( parseInt(element2)-1 ); // fonksiyondan çıkmadan 1 artırılacağı için -1 
    }
    
    else if(key == "PRN"){
        
        if(isReg(element1)){
            regIndex1 = element1[1]-'0';
            prn(R[regIndex1]);
        }
        else if(isNumber(element1))
            prn(parseInt(element1));
        else
            prn(myMemory.getMem( parseAddress(element1) ));

    }
    
    else if(key == "HLT"){
        
        if(option==1 || option==2)
            cout<<"HLT"<<endl;
        cout<<"R1="<<R[1]<<", R2="<<R[2]<<", R3="<<R[3]<<", R4="<<R[4]<<", R5="<<R[5]<<endl;
        if(option==0 || option==1)
            myMemory.printAll();
        setIsFinished(true);
    }

    if(option==1 || option==2){
        
        if(data.size()!=1 && count==3)
            cout<<key<<" "<<element1<<", "<<element2<<" - R1="<<R[1]<<", R2="
                <<R[2]<<", R3="<<R[3]<<", R4="<<R[4]<<", R5="<<R[5]<<endl<<endl;
        else if(data.size()!=1 && count==2)
            cout<<key<<" "<<element1<<" - R1="<<R[1]<<", R2="
                <<R[2]<<", R3="<<R[3]<<", R4="<<R[4]<<", R5="<<R[5]<<endl<<endl;
    }
    
    if(option==2)
        myMemory.printAll();

    setPC(getPC()+1);
}


// Stringi integera çevirir
int CPU::parseInt(string str){
    
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

// Stringden adres indexini parse eder
int CPU::parseAddress(string str){
    
    if(str.size() == 3)
        return parseInt(str.substr(1,2));
    else if(str.size() == 2)
        return parseInt(str.substr(1,1));
}


// Stringi bölme işlemi yapılırken göz ardı edilecek karakterlerin en küçük
// indexli olanını return eder
int CPU::min(string str, int startPos){
    
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


// Stringdeki tüm küçük harfleri büyütür. Case sensitive'i ortadan kaldırır.
string CPU::toUpper(string data){
    
    for(int j=0; j<data.size(); j++){
        if(data[j] >= 'a' && data[j] <= 'z' ){
            data[j] -= 'a' - 'A';
        }
    }
    
    return data;
    
}


// String içindeki bir registerı temsil ediyorsa true return eder
bool CPU::isReg(string str){
    
    if(str.size() != 2)
        return false;
    if(str[0] !='R')
        return false;
    if(!('1' <= str[1] && str[1] <= '5'))
        return false;
    return true;
}

// String içindeki bir sayıyı temsil ediyorsa true return eder
bool CPU::isNumber(string str){
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

bool CPU::isAddress(string str){
    
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

// String içindeki sabit bir sayı veya register ise true return eder
bool CPU::isRegOrConstant(string str){
    if(isReg(str) || isNumber(str))
        return true;
    else
        return false;
}

bool CPU::isRegOrAddress(string str){
    if(isReg(str) || isAddress(str))
        return true;
    else
        return false;
}

bool CPU::isRegOrConstOrAddress(string str){
    if(isRegOrConstant(str) || isAddress(str))
        return true;
    else
        return false;
        
    
}

void CPU::add(int regIndex, int number){

    setReg(regIndex, getReg(regIndex) + number);
}

void CPU::sub(int regIndex, int number){
    
    setReg(regIndex, getReg(regIndex) - number);
}

bool CPU::jmp(int lineAddress, int reg)const{
    if(reg==0)
        return true;
    else
        return false;
}

bool CPU::jpn(int lineAddress, int reg)const{
    
    if(reg<=0)
        return true;
    else
        return false;
}

void CPU::prn(int number){
    cout<<number<<endl;
}