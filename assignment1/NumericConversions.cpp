/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include <cmath>
using namespace std;

/* Function prototypes */

//string intToString(int n);
int stringToInt(string str);
string intToString(int n);
/* Main program */

int main() {
   int n=getInteger("Enter int to turn it into string ");
   string str=getLine("Enter string to turn it into int ");
   string stri=str;
   if(n<0){
	   cout<<"-"<<intToString(n)<<endl;
   }else if(n>=0){
	   cout<<intToString(n)<<endl;
   }
   if(str[0]=='-'){
	   stri=str.substr(1);
	   cout<<"-"<<stringToInt(stri)<<endl;
   }else{
	   cout<<stringToInt(str)<<endl;
   }
  
   return 0;
}
string intToString(int n){
	string str="";
	if(n<0){
		n*=(-1);
	}
	int a=n%10;
	int b=n/10;
	char nashti=(char)a+'0';
	
	str+=nashti;
	if((n*n)<100){
		return str;
	}else {
		return intToString(b)+str;
	}
	
}
int stringToInt(string str){
	char s=str.at(str.size()-1);
	int k=(int)(s-'0');
	string reminder=str.substr(0,str.size()-1);
	if(str.size()==1){
	return k;
	}else {
		return k+10*stringToInt(reminder);
	}
}
