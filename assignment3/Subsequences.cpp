/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
	string text=getLine("Enter first word: ");
	string subseq=getLine("Enter second word: ");
	if(isSubsequence(text,subseq)){
		cout<<"Second string is subsequence of the first one"<<endl;
	}else{
		cout<<"Second string isn't subsequence of the first one"<<endl;
	}
    return 0;
}
bool isSubsequence(string text, string subsequence){
	if(subsequence==""){
		return true;
	}if(text==""){
		return false;
	}
	string subtext=text.substr(1,text.size()-1);
	string subseq=subsequence.substr(1,subsequence.size()-1);
	if(text[0]==subsequence[0]){
		return isSubsequence(subtext,subseq);
	}else{
		return isSubsequence(subtext,subsequence);
	}
}
