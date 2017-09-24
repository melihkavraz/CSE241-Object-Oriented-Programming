/* 
 * File:   main.cpp
 * Author: Muhammet Melih Kavraz
 * C++ HomeWork 2
 *
 * Created on October 9, 2016, 11:49 AM
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

using namespace std;

#define MAX_LINE 201

// Instructionları parçalar ve uygun fonksiyonu çağırır
void instructionPartition(int R[], string data[], uint8_t memory[], int option, int startLine);

// Tüm satırların syntaxını kontrol eder eğer hata varsa hiçbir işlem yapmadan
// hatayı gösterip programı bitirir
bool checkSyntax(string line[]);

// String içindeki bir sayıyı temsil ediyorsa true return eder
bool isNumber(string str);

// String içindeki bir registerı temsil ediyorsa true return eder
bool isReg(string str);

// String içindeki bir adresi temsil ediyorsa true return eder
bool isAddress(string str);

// Memory içinde 0dan 255e kadar sayılar tutabilir, aşım var mı kontrol eder
bool isAddressValueDefinable(int number);

// String içindeki sabit bir sayı veya register ise true return eder
bool isRegOrConstant(string str);

// String içindeki bir register veya adresi temsil ediyor ise true return eder.
bool isRegOrAddress(string str);

// String içindeki sabit bir sayı, register veya memory adresi ise true return eder.
bool isRegOrConstOrAddress(string str);

// Stringi integera çevirir
int parseInt(string str);

// Address stringini integera çevirir
int parseAddress(string str);

// Stringi bölme işlemi yapılırken göz ardı edilecek karakterlerin en küçük
// indexli olanını return eder
int min(string str, int startPos=0);

// String arrayindeki tüm küçük harfleri büyütür. Case sensitive'i ortadan kaldırır.
void toUpper(string data[]);

// Instructions
void mov(int number, int* reg);
void mov(int* reg, int number);
bool move(int reg, uint8_t* number);
void move(uint8_t number, int* reg);
bool move(uint8_t* number, int con);
void add(int* reg, int number);
void addU(int* reg, uint8_t number);
void sub(int* reg, int number);
void subU(int* reg, uint8_t number);
bool jmp(int lineAddress, int reg=0);
bool jpn(int lineAddress, int reg);
void prn(int number);

// Prints 50 memory with their values
void printMemory(uint8_t mem[]);


/*
 * 
 */
int main(int argc, char** argv) {
    
    int j=1, R[6] = {0,0,0,0,0,0};
    uint8_t memory[50];
    string data[MAX_LINE];
    
    if(argc != 3){
        cerr<<"Missing command line argument"<<endl;
        return -1;
    }

    ifstream infile;
    
    if(infile.fail()){
        cerr<<"File reading error"<<endl;
        return -1;
    }   
    infile.open(argv[1]);
    while (!infile.eof()){
        getline(infile, data[j]);
        j++;
    }
    infile.close();
    
    toUpper(data);
    
    if(checkSyntax(data))
        instructionPartition(R, data, memory, parseInt(argv[2]), 1);
    
    return 0;
}

// Instructionları parçalar ve uygun fonksiyonu çağırır
void instructionPartition(int R[], string data[], uint8_t mem[], int option, int startLine){
    
    bool jmpResult, jpnResult;
    int count=0;
    int i=0;
    int regIndex1, regIndex2;
    string key;
    size_t semicolonPos=0;
    size_t nearestPos=0, oldNearestPos=-1;//-1 olma nedeni döngüye ilk girişte 0 ile nearestPos arası kontrol edilmesi gerek
    string token, element1, element2;
    size_t spaceSize = 1;  
    
    for(i=startLine; i<MAX_LINE; i++){
        if( (semicolonPos = data[i].find(';')) != string::npos)
            data[i] = data[i].substr(0, semicolonPos);
        data[i].append("\n");
        while  (data[i].size()!=1 && nearestPos != string::npos){
            nearestPos = min(data[i],oldNearestPos+spaceSize); 
            token = data[i].substr(oldNearestPos+spaceSize, nearestPos-oldNearestPos-spaceSize); // tokena spacei dahil etmiyor
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
                    mov(R[regIndex1],&R[regIndex2]);

                }
                else              
                    mov(&R[regIndex1],parseInt(element2));
            }
            else if(isAddress(element1)){
                if(isReg(element2)){
                    regIndex2 = element2[1]-'0';
                    mov(mem[ parseAddress(element1) ], &R[regIndex2]);
                }
                else
                    if(!move(&mem[ parseAddress(element1) ],parseInt(element2))){
                        cerr<<"[main.cpp:"<<i<<"] 'MOV' 1st (memory address) operand can only take value from 0 to 255\n";
                        return; 
                    }
            }
            else{
                regIndex1 = element1[1]-'0';
                if(!move(R[regIndex1],&mem[ parseAddress(element2) ])){
                    cerr<<"[main.cpp:"<<i<<"] 'MOV' 1st (memory address) operand can only take value from 0 to 255\n";
                    return; 
                }
            }
                
        }
        else if(key == "ADD"){
            regIndex1 = element1[1]-'0';
            if(isReg(element2)){
                regIndex2 = element2[1]-'0';
                add(&R[regIndex1],R[regIndex2]);
            }
            else if(isAddress(element2)){
                addU(&R[regIndex1],mem[ parseAddress(element2) ]);
            }
            else
                add(&R[regIndex1],parseInt(element2));
        }
        else if(key == "SUB"){
            regIndex1 = element1[1]-'0';
            if(isReg(element2)){
                regIndex2 = element2[1]-'0';
                sub(&R[regIndex1],R[regIndex2]);
            }
            else if(isAddress(element2)){
                subU(&R[regIndex1],mem[ parseAddress(element2) ]);
            }
            else
                sub(&R[regIndex1],parseInt(element2));
        }
        else if(key == "JMP"){
            if(element2.empty()){
                jmpResult = jmp(parseInt(element1));
                if(jmpResult==true){
                    if(option==1 && count==2)
                        cout<<"JMP"<<" "<<element1<<" - R1="<<R[1]<<", R2="
                            <<R[2]<<", R3="<<R[3]<<", R4="<<R[4]<<", R5="<<R[5]<<endl<<endl;
                    if(option==2)
                        printMemory(mem);
                    instructionPartition(R, data, mem, option, parseInt(element1));
                    return;
                }
            }
            else{
                regIndex1 = element1[1]-'0';
                jmpResult = jmp(parseInt(element2), R[regIndex1]);
                if(jmpResult==true){
                    if(( option==1 || option==2) && count==3)
                        cout<<"JMP"<<" "<<element1<<", "<<element2<<" - R1="<<R[1]<<", R2="
                            <<R[2]<<", R3="<<R[3]<<", R4="<<R[4]<<", R5="<<R[5]<<endl<<endl;
                    if(option==2)
                        printMemory(mem);
                    instructionPartition(R, data, mem, option, parseInt(element2));
                    return;
                }
            }
        }
        else if(key == "JPN"){
            regIndex1 = element1[1]-'0';
                jpnResult = jpn(parseInt(element2), R[regIndex1]);
                if(jpnResult==true){
                    if(option==1 || option==2)
                        cout<<"JMP"<<" "<<element1<<", "<<element2<<" - R1="<<R[1]<<", R2="
                            <<R[2]<<", R3="<<R[3]<<", R4="<<R[4]<<", R5="<<R[5]<<endl<<endl;
                    if(option==2)
                        printMemory(mem);
                    instructionPartition(R, data, mem, option, parseInt(element2));
                    return;
                }
        }
        else if(key == "PRN"){
            if(isReg(element1)){
                regIndex1 = element1[1]-'0';
                prn(R[regIndex1]);
            }
            else if(isNumber(element1))
                prn(parseInt(element1));
            else
                prn(mem[parseAddress(element1)]);
                
        }
        else if(key == "HLT"){
            if(option==1 || option==2)
                cout<<"HLT"<<endl;
            cout<<"R1="<<R[1]<<", R2="<<R[2]<<", R3="<<R[3]<<", R4="<<R[4]<<", R5="<<R[5]<<endl<<endl;
            printMemory(mem);
            return;
        }
        
        
        if(option==1 || option==2){
            if(data[i].size()!=1 && count==3)
                cout<<key<<" "<<element1<<", "<<element2<<" - R1="<<R[1]<<", R2="
                    <<R[2]<<", R3="<<R[3]<<", R4="<<R[4]<<", R5="<<R[5]<<endl<<endl;
            else if(data[i].size()!=1 && count==2)
                cout<<key<<" "<<element1<<" - R1="<<R[1]<<", R2="
                    <<R[2]<<", R3="<<R[3]<<", R4="<<R[4]<<", R5="<<R[5]<<endl<<endl;
        }
        
        if(option==2)
            printMemory(mem);
        count=0;
        nearestPos=0;
        oldNearestPos=-1;
        key.clear();
        element1.clear();
        element2.clear();
        
    }
}

// Tüm satırların syntaxını kontrol eder eğer hata varsa hiçbir işlem yapmadan
// hatayı gösterip programı bitirir
bool checkSyntax(string line[]){
   
    size_t nearestPos;
    size_t semicolonPos;
    size_t commaPos;
    int count;
    int spaceSize;
    string data[MAX_LINE], token, key, element1, element2; // bunları sonradan boşalt
    
    for(int i=1; i<MAX_LINE; i++){
    
        nearestPos = min(line[i]);
        semicolonPos = line[i].find(';');
        commaPos = line[i].find(',');
        count=0;
        spaceSize = 1;
        data[i] = line[i], token, key, element1, element2; // bunları sonradan boşalt

        if(data[i].size()!=0){
     
            //Eleman sayısı kontrol
            if( (semicolonPos = data[i].find(';')) != string::npos){
                data[i] = data[i].substr(0, semicolonPos); // tokena noktalı virgülü dahil etmiyor     
            }
            data[i].append("\n");

            while(data[i].size()!=0){
                nearestPos = min(data[i]);
                token = data[i].substr(0, nearestPos); // tokena spacei dahil etmiyor
                data[i].erase(0, nearestPos + spaceSize); // spacei de dahil edip siliyor

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
                    cerr<<"[main.cpp:"<<i<<"] 'MOV' can take 2 operand\n";
                    return false;
                }
                else if(!isRegOrAddress(element1)){
                    cerr<<"[main.cpp:"<<i<<"] 'MOV' 1st operand have to be register or memory address\n";
                    return false;
                }
                else if(!isRegOrConstOrAddress(element2)){
                    cerr<<"[main.cpp:"<<i<<"] 'MOV' 2nd operand is undefinable\n";
                    return false;
                }
                
                if(isAddress(element1)){
                    if(isNumber(element2)){
                        if(!isAddressValueDefinable(parseInt(element2))){
                            cerr<<"[main.cpp:"<<i<<"] 'MOV' 1st (memory address) operand can only take value from 0 to 255\n";
                            return false;
                        }
                    }
                        
                    if(!isRegOrConstant(element2)){
                        cerr<<"[main.cpp:"<<i<<"] 'MOV' if 1st operand is an address, 2nd operand have to be register or constant\n";
                        return false;
                    }
                }
                else if(isAddress(element2)){
                    if(!isReg(element1)){
                        cerr<<"[main.cpp:"<<i<<"] 'MOV' if 2nd operand is an address, 1st operand have to be a register\n";
                        return false;
                    }
                        
                }
            }
            else if(key == "ADD"){
                if(count!=3){
                    cerr<<"[main.cpp:"<<i<<"] 'ADD' can take 2 operand\n";
                    return false;
                }
                else if(!isReg(element1)){
                    cerr<<"[main.cpp:"<<i<<"] 'ADD' 1st operand have to be register\n";
                    return false;
                }
                else if(!isRegOrConstOrAddress(element2)){
                    cerr<<"[main.cpp:"<<i<<"] 'ADD' 2nd operand is undefinable\n";
                    return false;
                }
            }
            else if(key == "SUB"){
                if(count!=3){
                    cerr<<"[main.cpp:"<<i<<"] 'SUB' can take 2 operand\n";
                    return false;
                }
                else if(!isReg(element1)){
                    cerr<<"[main.cpp:"<<i<<"] 'SUB' 1st operand have to be register\n";
                    return false;
                }
                else if(!isRegOrConstOrAddress(element2)){
                    cerr<<"[main.cpp:"<<i<<"] 'SUB' 2nd operand is undefinable\n";
                    return false;
                }
            }
            else if(key == "JMP"){
                if(!(count == 2 || count == 3)){
                    cerr<<"[main.cpp:"<<i<<"] 'JMP' can take 1 or 2 operand\n";
                    return false;
                }
                else if(!isRegOrConstant(element1)){
                    cerr<<"[main.cpp:"<<i<<"] 'JMP' 1st operand is undefinable\n";
                    return false;
                }
                else if(element2.size()>0){
                    if(!isNumber(element2)){
                        cerr<<"[main.cpp:"<<i<<"] 'JMP' 2nd operand is not lineAddress\n";
                        return false;
                    }
                }
            }
            
            else if(key == "JPN"){
                if(count != 3){
                    cerr<<"[main.cpp:"<<i<<"] 'JPN' can take 2 operand\n";
                    return false;
                }
                else if(!isReg(element1)){
                    cerr<<"[main.cpp:"<<i<<"] 'JPN' 1st operand is not a register\n";
                    return false;
                }
                else if(!isNumber(element2)){
                        cerr<<"[main.cpp:"<<i<<"] 'JPN' 2nd operand is not lineAddress\n";
                        return false;
                }
            }
            
            
            else if(key == "PRN"){
                if(count!=2){
                    cerr<<"[main.cpp:"<<i<<"] 'PRN' can take 1 operand\n";
                    return false;
                }
                else if(!isRegOrConstOrAddress(element1)){
                    cerr<<"[main.cpp:"<<i<<"] 'PRN' 1st operand is undefinable\n";
                    return false;
                }
            }
            else if(key == "HLT"){
                if(count!=1){
                    cerr<<"[main.cpp:"<<i<<"] 'HLT' can take only 1 operand\n";
                    return false;
                }
            }
            else{
                cerr<<"[main.cpp:"<<i<<"] opcode can not be found\n";
                return false;
            }


            //Noktalı virgülden önceki virgül sayısı 1den fazla mı kontrol ediliyor
            if (count == 3){
                size_t element1_pos = line[i].find(element1);
                size_t element2_pos = line[i].find(element2);
                size_t comma_pos = line[i].find(',');

                if(commaPos == string::npos){
                    cerr<<"[main.cpp:"<<i<<"] There is no ',' between 2 operand\n";
                    return false;
                }
                else if(semicolonPos == string::npos){
                    if(line[i].find(",",commaPos+1,1) != string::npos){
                        cerr<<"[main.cpp:"<<i<<"] It has to be only 1 ','\n";
                        return false;
                    }
                }

                else if(commaPos<semicolonPos){
                    if( (commaPos = line[i].find(",", commaPos+1,1)) != string::npos){
                        if(commaPos<semicolonPos){
                            cerr<<"[main.cpp:"<<i<<"] It has to be only 1 ',' before ';'\n";
                            return false;
                        }
                    }
                }
                // virgül iki eleman arasında mı kontrol ediliyor
                else if(!(element1_pos + element1.size()-1 < comma_pos && comma_pos < element2_pos)){
                    cerr<<"[main.cpp:"<<i<<"] It has to be ',' between 2 operand\n";
                    return false;
                }
            }

            else if(count == 2){
                if(semicolonPos == string::npos && commaPos != string::npos){
                    cerr<<"[main.cpp:"<<i<<"] ',' can not be used here\n";
                    return false;
                }
                else if(semicolonPos != string::npos && commaPos != string::npos){
                    cerr<<"[main.cpp:"<<i<<"] ',' can not be used here\n";
                    return false;
                }
            }
        }
    }
    
    return true;
}

// String içindeki bir sayıyı temsil ediyorsa true return eder
bool isNumber(string str){
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
bool isReg(string str){
    if(str.size() != 2)
        return false;
    if(str[0] !='R')
        return false;
    if(!('1' <= str[1] && str[1] <= '5'))
        return false;
    return true;
}

bool isAddress(string str){
    
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

bool isAddressValueDefinable(int number){
    
    if(0<=number && number<=255)
        return true;
    else
        return false;
}

// String içindeki sabit bir sayı veya register ise true return eder
bool isRegOrConstant(string str){
    if(isReg(str) || isNumber(str))
        return true;
    else
        return false;
}

bool isRegOrAddress(string str){
    if(isReg(str) || isAddress(str))
        return true;
    else
        return false;
}

bool isRegOrConstOrAddress(string str){
    if(isRegOrConstant(str) || isAddress(str))
        return true;
    else
        return false;
        
    
}

// Stringi integera çevirir
int parseInt(string str){
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

int parseAddress(string str){
    
    if(str.size() == 3)
        return parseInt(str.substr(1,2));
    else if(str.size() == 2)
        return parseInt(str.substr(1,1));
}

// Stringi bölme işlemi yapılırken göz ardı edilecek karakterlerin en küçük
// indexli olanını return eder
int min(string str, int startPos){
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

// String arrayindeki tüm küçük harfleri büyütür. Case sensitive'i ortadan kaldırır.
void toUpper(string data[]){
    for(int i=1; i<MAX_LINE; i++){
        for(int j=0; j<data[i].size(); j++){
            if(data[i][j] >= 'a' && data[i][j] <= 'z' ){
                data[i][j] -= 'a' - 'A';
            }
        }
    }
}

void mov(int number, int* reg){
    *reg = number;
}

void mov(int* reg, int number){
    *reg = number;
}

void move(uint8_t number, int* reg){
    *reg = number;
}

bool move(int reg, uint8_t* number){

    if(!(0<=reg && reg<=255))
        return false;
    
    *number = reg;
    
    return true;
}

bool move(uint8_t* number, int con){
    
    if(!(0<=con && con<=255))
        return false;
    
    *number = con;
    
    return true;
}

void add(int* reg, int number){
    
    *reg +=number;
}

void addU(int* reg, uint8_t number){
    
    *reg +=number;
}

void sub(int* reg, int number){
    
    *reg -=number;
}

void subU(int* reg, uint8_t number){
    
    *reg -=number;
}

bool jmp(int lineAddress, int reg){
    
    if(reg==0)
        return true;
    else
        return false;
}

bool jpn(int lineAddress, int reg){
    
    if(reg<=0)
        return true;
    else
        return false;
}

void prn(int number){
    
    cout<<number<<endl;
}

void printMemory(uint8_t mem[]){
    
    for(int i=0; i<50; i++){
        cout<<"#"<<i<<"="<<(int)mem[i]<<" ";
        if((i+1)%10==0)
            cout<<endl;
    }
}