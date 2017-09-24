/* 
 * File:   main.cpp
 * Author: Muhammet Melih Kavraz
 * C++ HomeWork 1
 *
 * Created on September 27, 2016, 11:49 AM
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define MAX_LINE 201

// Instructionları parçalar ve uygun fonksiyonu çağırır
void instructionPartition(int R[], string data[], int option, int startLine);

// Tüm satırların syntaxını kontrol eder eğer hata varsa hiçbir işlem yapmadan
// hatayı gösterip programı bitirir
bool checkSyntax(string line[]);

// String içindeki bir sayıyı temsil ediyorsa true return eder
bool isNumber(string str);

// String içindeki bir registerı temsil ediyorsa true return eder
bool isReg(string str);

// String içindeki sabit bir sayı veya register ise true return eder
bool isRegOrConstant(string str);

// Stringi integera çevirir
int parseInt(string str);

// Stringi bölme işlemi yapılırken göz ardı edilecek karakterlerin en küçük
// indexli olanını return eder
int min(string str, int startPos=0);

// String arrayindeki tüm küçük harfleri büyütür. Case sensitive'i ortadan kaldırır.
void toUpper(string data[]);

// Instructions
void mov(int number, int* reg);
void mov(int* reg, int number);
void add(int* reg, int number);
void sub(int* reg, int number);
bool jmp(int lineAddress, int reg=0);
void prn(int number);
void hlt(int* reg);


/*
 * 
 */
int main(int argc, char** argv) {
    
    int j=1, R[6] = {0,0,0,0,0,0};
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
        instructionPartition(R, data, parseInt(argv[2]), 1);
    
    return 0;
}

// Instructionları parçalar ve uygun fonksiyonu çağırır
void instructionPartition(int R[], string data[], int option, int startLine){
    bool jmpResult;
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
            regIndex1 = element1[1]-'0';
            if(isReg(element2)){
                regIndex2 = element2[1]-'0';
                mov(R[regIndex1],&R[regIndex2]);
            }
            else
                mov(&R[regIndex1],parseInt(element2));
                
        }
        else if(key == "ADD"){
            regIndex1 = element1[1]-'0';
            if(isReg(element2)){
                regIndex2 = element2[1]-'0';
                add(&R[regIndex1],R[regIndex2]);
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
                    instructionPartition(R, data, option, parseInt(element1));
                    return;
                }
            }
            else{
                regIndex1 = element1[1]-'0';
                jmpResult = jmp(parseInt(element2), R[regIndex1]);
                if(jmpResult==true){
                    if(option==1 && count==3)
                        cout<<"JMP"<<" "<<element1<<", "<<element2<<" - R1="<<R[1]<<", R2="
                            <<R[2]<<", R3="<<R[3]<<", R4="<<R[4]<<", R5="<<R[5]<<endl<<endl;
                    instructionPartition(R, data, option, parseInt(element2));
                    return;
                }
            }
        }
        else if(key == "PRN"){
            if(isReg(element1)){
                regIndex1 = element1[1]-'0';
                prn(R[regIndex1]);
            }
            else
                prn(parseInt(element1));
                
        }
        else if(key == "HLT"){
            if(option==1)
                cout<<"HLT"<<endl;
            cout<<"R1="<<R[1]<<", R2="<<R[2]<<", R3="<<R[3]<<", R4="<<R[4]<<", R5="<<R[5]<<endl<<endl;
            return;
        }
        
        if(option==1){
            if(data[i].size()!=1 && count==3)
                cout<<key<<" "<<element1<<", "<<element2<<" - R1="<<R[1]<<", R2="
                    <<R[2]<<", R3="<<R[3]<<", R4="<<R[4]<<", R5="<<R[5]<<endl<<endl;
            else if(data[i].size()!=1 && count==2)
                cout<<key<<" "<<element1<<" - R1="<<R[1]<<", R2="
                    <<R[2]<<", R3="<<R[3]<<", R4="<<R[4]<<", R5="<<R[5]<<endl<<endl;
        }
        
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
                else if(!isReg(element1)){
                    cerr<<"[main.cpp:"<<i<<"] 'MOV' 1st operand have to be register\n";
                    return false;
                }
                else if(!isRegOrConstant(element2)){
                    cerr<<"[main.cpp:"<<i<<"] 'MOV' 2nd operand is undefinable\n";
                    return false;
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
                else if(!isRegOrConstant(element2)){
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
                else if(!isRegOrConstant(element2)){
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
            else if(key == "PRN"){
                if(count!=2){
                    cerr<<"[main.cpp:"<<i<<"] 'PRN' can take 1 operand\n";
                    return false;
                }
                else if(!isRegOrConstant(element1)){
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
                cerr<<"[main.cpp:"<<i<<"] opcode can not be found";
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

// String içindeki sabit bir sayı veya register ise true return eder
bool isRegOrConstant(string str){
    if(isReg(str) || isNumber(str))
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

// Stringi bölme işlemi yapılırken göz ardı edilecek karakterlerin en küçük
// indexli olanını return eder
int min(string str, int startPos){
    //virgül pos da olmalı burda
    //; pos da olmalı
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

void add(int* reg, int number){
    *reg +=number;
}

void sub(int* reg, int number){
    *reg -=number;
}

bool jmp(int lineAddress, int reg){
    if(reg==0)
        return true;
    else
        return false;
}

void prn(int number){
    cout<<number<<endl;
}