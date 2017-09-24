/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPUProgramDyn.h
 * Author: melih5295
 *
 * Created on October 24, 2016, 7:52 PM
 */

#ifndef CPUPROGRAMDYN_H
#define CPUPROGRAMDYN_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace MelihKavraz
{

    class CPUProgramDyn {
    public:

        // Initialize option and calls the functions readFile.
        CPUProgramDyn(const char* filename, int opt);

        // Initialize option
        CPUProgramDyn(int opt);

        // Copy Constructor
        CPUProgramDyn(const CPUProgramDyn& myProg);

        // Setter
        void setOption( int );

        // Returns a string that contains the program line
        std::string getLine(int lineNumber) const;

        // Reads and stores all the program instructions
        void ReadFile(const char* filename);

        // Okunan instruction satır satıyını döndürür
        int size() const;    

        // String arrayine string ekler
        void pushBack(string instruction);

        // Operator Overloads
        CPUProgramDyn& operator =(const CPUProgramDyn& myProg);
        string operator [](int index);
        CPUProgramDyn operator +(string instruction) const;
        CPUProgramDyn& operator +=(string instruction);
        CPUProgramDyn operator +(const CPUProgramDyn& myProg) const;
        bool operator ==(const CPUProgramDyn& myProg) const;
        bool operator !=(const CPUProgramDyn& myProg) const;
        bool operator <=(const CPUProgramDyn& myProg) const;
        bool operator >=(const CPUProgramDyn& myProg) const;
        bool operator <(const CPUProgramDyn& myProg) const;
        bool operator >(const CPUProgramDyn& myProg) const;
        friend ostream& operator <<(ostream& outputStream, const CPUProgramDyn& myProg);
        const CPUProgramDyn& operator --();
        const CPUProgramDyn operator --(int);
        const CPUProgramDyn operator ()(int startIndex, int lastIndex);


        //Destructor
        ~CPUProgramDyn();

    private:

        int option;
        int capacity;
        int used;

        // Instructionları depolar
        string* data;

        // String arrayindeki tüm küçük harfleri büyütür. Case sensitive'i ortadan kaldırır.
        string toUpper(string data);

        // Stringi bölme işlemi yapılırken göz ardı edilecek karakterlerin en küçük
        // indexli olanını return eder
        int min(string str, int startPos=0) const;

        int parseInt(string str);

        // Tüm satırların syntaxını kontrol eder eğer hata varsa hiçbir işlem yapmadan
        // hatayı gösterip programı bitirir
        bool checkSyntax();

        // String içindeki bir sayıyı temsil ediyorsa true return eder
        bool isNumber(string str) const;

        // String içindeki bir registerı temsil ediyorsa true return eder
        bool isReg(string str) const;

        // String içindeki sabit bir sayı veya register ise true return eder
        bool isRegOrConstant(string str) const;

        // String içindeki bir adres ise true return eder
        bool isAddress(string str);

        // String içindeki adres tanımlanabilir aralıkta ise true return eder
        bool isAddressValueDefinable(int number);

        // String içindeki bir register veya adres ise true return eder
        bool isRegOrAddress(string str);

        // String içindeki bir register, constant veya adres ise true return eder
        bool isRegOrConstOrAddress(string str);
    };

} //MelihKavraz

#endif /* CPUPROGRAMDYN_H */

