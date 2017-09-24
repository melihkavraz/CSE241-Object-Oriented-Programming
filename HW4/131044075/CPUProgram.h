/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPUProgram.h
 * Author: melih5295
 *
 * Created on October 24, 2016, 7:52 PM
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <iostream>
#include <string>
#include <vector>

class CPUProgram {
public:
    
    // Initialize option and calls the functions readFile.
    CPUProgram(const char* filename, int opt);
    
    // Initialize option
    CPUProgram(int opt);
    
    // Setter
    void setOption( int );
    
    // Returns a string that contains the program line
    std::string getLine(int lineNumber) const;
    
    // Reads and stores all the program instructions
    void ReadFile(const char* filename);
    
    // Okunan instruction satır satıyını döndürür
    int size() const;
    
private:
    
    int option;
    
    // Instructionları depolar
    std::vector<std::string> data;
 
    // String arrayindeki tüm küçük harfleri büyütür. Case sensitive'i ortadan kaldırır.
    std::string toUpper(std::string data);
    
    // Stringi bölme işlemi yapılırken göz ardı edilecek karakterlerin en küçük
    // indexli olanını return eder
    int min(std::string str, int startPos=0) const;
    
    int parseInt(std::string str);
    
    // Tüm satırların syntaxını kontrol eder eğer hata varsa hiçbir işlem yapmadan
    // hatayı gösterip programı bitirir
    bool checkSyntax();
    
    // String içindeki bir sayıyı temsil ediyorsa true return eder
    bool isNumber(std::string str) const;
    
    // String içindeki bir registerı temsil ediyorsa true return eder
    bool isReg(std::string str) const;
    
    // String içindeki sabit bir sayı veya register ise true return eder
    bool isRegOrConstant(std::string str) const;
    
    // String içindeki bir adres ise true return eder
    bool isAddress(std::string str);
    
    // String içindeki adres tanımlanabilir aralıkta ise true return eder
    bool isAddressValueDefinable(int number);
    
    // String içindeki bir register veya adres ise true return eder
    bool isRegOrAddress(std::string str);
    
    // String içindeki bir register, constant veya adres ise true return eder
    bool isRegOrConstOrAddress(std::string str);
};

#endif /* CPUPROGRAM_H */

