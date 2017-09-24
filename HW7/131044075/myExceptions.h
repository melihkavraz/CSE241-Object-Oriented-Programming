/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myExceptions.h
 * Author: oguzhan
 *
 * Created on 30 Aralık 2016 Cuma, 16:32
 */
#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H

#include <exception>
#include <string>

using namespace std;

class myExceptions: public exception {
public:
  myExceptions () noexcept{
      
  }
  myExceptions(string exc){
      except = exc;
  }
  myExceptions (const exception&) noexcept{
      
  }
  myExceptions& operator= (const exception&) noexcept{
      
  }
  virtual ~myExceptions(){
      
  }
  virtual const char* what() const noexcept{
      return except.c_str();
  }
private:
    string except;  
};

#endif /* MYEXCEPTIONS_H */

