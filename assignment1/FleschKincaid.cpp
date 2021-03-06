/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "tokenscanner.h"
using namespace std;

/*
Methods which are defined below
*/
bool punqtuacia(string a);
int syllable(string luka);
string filename();
static int words=0;
static int syllables=0;
static int sentences=0;
static int winavowel=0;
static double difficulty=0;
static bool apostrophi=false;
int main() {
	ifstream inputFile;
	string tapu=filename();
	inputFile.open(tapu.c_str());
	TokenScanner scanner(inputFile);
	scanner.ignoreWhitespace();
	while(scanner.hasMoreTokens()){
		string word=scanner.nextToken();
		cout<<word<<endl;
		if(punqtuacia(word)){
			if(word=="."||word=="!"||word=="?"){
				sentences++;
				apostrophi=false;
			}else if(word=="'"){
				apostrophi=true;
			}
		}else{
			if((!apostrophi||word.size()>2)&&isalpha(word[0])){
			words++;
			int syll=syllable(word);
			syllables+=syll;
			}else {
				apostrophi=false;
			}
			
		}
	}
	cout<<words<<endl;
	cout<<syllables<<endl;
	cout<<sentences<<endl;
	difficulty=-15.59+0.39*(double)words/(double)sentences+11.8*(double)syllables/(double)words;
	cout<<difficulty<<endl;
    return 0;
}
/*
checks if the token is punctuation mark or not.
*/
bool punqtuacia(string a){
	if(ispunct(a[0])){
		return true;
	}
	return false;
}
/*
counts the number of the syllables in the word.
*/
int syllable(string luka){
	int vowel=0;
	int winavowel=0;
	for(int i=0;i<luka.size();i++){
		if(luka[i]=='a'||luka[i]=='i'||luka[i]=='o'||(luka[i]=='e'&&i!=luka.size()-1)||luka[i]=='u'||luka[i]=='A'||luka[i]=='O'
			||luka[i]=='I'||(luka[i]=='E'&&i!=luka.size()-1)||luka[i]=='U'||luka[i]=='y'||luka[i]=='Y'){
			if(winavowel==0){
			vowel++;
			}
			winavowel=1;
		}else {
		winavowel=0;}
	}
	if(vowel==0){
	vowel=1;}
	return vowel;
}
string filename(){
	ifstream inputFile;
	string tapu="";
	while(true){
		tapu=getLine("Enter input file name ");
		inputFile.open(tapu.c_str());
		if(!inputFile.fail()){
			return tapu;
		}
		
		else{
			inputFile.clear();
			cout<<"Unable to open that file. Try again "<<endl;
		}
	}
}

