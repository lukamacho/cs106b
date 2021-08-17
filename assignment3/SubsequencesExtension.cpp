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
#include "vector.h"
#include "queue.h"
#include "set.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string &text, string &subsequence);
bool everysSubseq(string& possubseq,Vector<string> &words);
void findMinSubseq(Vector<string> & words,Set<char> &chars);
/*
Main function:
*/
int main() {
	Vector<string> words;
	Set<char> chars;
	while(true){
		string word=getLine("Enter word (or nothing to finish word input): ");
		if(word==""){
			break;
		}
		for(int i=0;i<word.size();i++){
			if(!chars.contains(word[i])){
				chars.add(word[i]);
			}
		}
		words.add(word);
	}
	cout<<"searching...(If such word's size is more than 7 it needs a lot time)"<<endl;
	findMinSubseq(words,chars);
    return 0;
}
/*
Checks if the text has subsequnce as its part.
*/
bool isSubsequence(string & text, string & subsequence){
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

/*
Checks if possible Subsequence have all words elements as its part or not.
*/
bool everysSubseq(string & possSubseq, Vector<string> & words){
	foreach(string word in words){
		if(!isSubsequence(possSubseq,word)){
			return false;
		}
	}
	return true;
}

/*
This code finds minstring which contains every element of words vector.
*/
void findMinSubseq(Vector<string> &words, Set <char> & chars){
	Queue<string> minSubseq;
	for(char ch='a';ch<'z'+1;ch++){
		string a="";
		a+=ch;
		minSubseq.enqueue(a);
	}while(true){
		bool q=false;
		string a=minSubseq.dequeue();
		foreach(char ch in chars){
			string b=a;
			b+=ch;
			if(everysSubseq(b,words)){
				cout<<b<<endl;
				q=true;
				break;
			}else{
				minSubseq.enqueue(b);
			}
		}
		if(q==true){
			break;
		}
	}
}