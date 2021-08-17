/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "lexicon.h"
#include "console.h"
#include "simpio.h"
#include "queue.h"
#include "set.h"
#include "tokenscanner.h"
using namespace std;
string ladder(string & a, string & b);
Set<string> permut(string & a);
const Lexicon lex("EnglishWords.dat");
void minLadder(string & a,string & b);
int main() {
	string sentinel="";
	while(true){
		string firstWord=getLine("Enter the starting word (or nothing to quit): ");
		if(firstWord==sentinel){
			cout<<"Goodbye"<<endl;
			break;
		}
		string endWord=getLine("Enter the ending word: ");
		cout<<"Searching..."<<endl;
		if(!lex.contains(firstWord)||!lex.contains(endWord)||(firstWord.size()!=endWord.size())){
			cout<<"No word ladder could be found."<<endl;
			cout<<endl;
		}else{
		minLadder(firstWord,endWord);
		}
	}
    
    return 0;
}
/*
This code checks if it is possible to get string b from string a and returns appropriate string if it exists.
*/
string ladder(string & a,string & endWord){
		Set<string>words;
		Queue<Stack<string> > ladder;
		Stack<string> simravle ;
		simravle.push(a);
		ladder.enqueue(simravle);
		while(!ladder.isEmpty()){
			Stack<string> biliki=ladder.dequeue();
			if(biliki.peek() == endWord){
				return biliki.toString(); 
			}
			Set<string> permutation= permut(biliki.peek());
			foreach(string word in permutation){
				if(!words.contains(word))
					{
					Stack<string> copya=biliki;
					copya.push(word);
					words.add(word);
					ladder.enqueue(copya);
				}
			}
		}
	
	return "";
}
/*
This code makes up set which have strings whose difference is once from the last element from last string of the ladder.
*/
Set<string> permut(string & a){
	Set<string> permutation;
	for(int i=0;i<a.length();i++){
		for(char ch='a';ch<'z'+1;ch++){
		string part=a.substr(0,i)+ch+a.substr(i+1);
		if(lex.contains(part)){
			permutation.add(part);
			}
		}
	}
	return permutation;
}

/*
This code finds min ladder between inputted words and print it.
*/
void minLadder(string & firstWord, string & endWord){
	string biliki=ladder(firstWord,endWord);
	if(biliki==""){
		cout<<"No word ladder could be found"<<endl;
	}
	if(biliki!=""){
		cout<<"Ladder found: ";
	}
	string answer="";
	TokenScanner scanner(biliki);
	scanner.ignoreWhitespace();
	while(scanner.hasMoreTokens()){
		string word=scanner.nextToken();
		if(isalpha(word[0])){
			word+="-->";
			answer+=word;
		}
	}
	cout<<answer.substr(0,answer.size()-3)<<endl;
		cout<<endl;
}