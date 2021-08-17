
/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "vector.h"
#include "map.h"
#include "random.h"
#include <fstream>
using namespace std;

int k;
string filename();
int getInt();
string key(int i,string b);
string randomText(string big);
Map<string, Vector<char> >  data;
string max();
int main() {
	ifstream inputFile;
	string file=filename();
	inputFile.open(file.c_str());
    k=getInt();
	cout<<"Proccessing file..."<<endl;
	char ch;
	string big="";
	while(inputFile.get(ch)){
		big+=ch;
	}
	string answer=randomText(big);
	cout<<answer<<endl;
	
    return 0;
}
/*
This code gives you an opportunity to choose file.
*/
string filename(){
	ifstream inputFile;
	string file="";
	while(true){
		file=getLine("Enter input file name");
		inputFile.open(file.c_str());
		if(!inputFile.fail()){
			return file;
		}
		else {
			inputFile.clear();
			cout<<"Unable to open file.Try again"<<endl;
		}
	}
}
 /*
 This code allows you to choose number from 1 to 10.
 */
int getInt(){
	while(true){
		int a=getInteger("Enter markovis number from 1 to 10 : ");
		if(a<11&&a>0){
			return a;
		}
		cout<<"These number isn't in margins"<<endl;
	}
}
/*
This code returns the key to store it in the map.
*/
string key(int i,string b){
	string dasabrunebeli="";
	for(int j=i;j<i+k;j++){
		dasabrunebeli+=b[j];
	}
	return dasabrunebeli;
}
/*
This code fills the map and return the most frequentid string which contains k chars.
*/
string max(string big){
	int maxfrequency=0;
	string maxKey="";
	for(int i=0;i<big.size()-k-1;i++){
		string keuli=key(i,big);
		if(data.containsKey(keuli)){
			Vector<char> cha=data.get(keuli);
			if(cha.size()>maxfrequency){
				maxfrequency=cha.size();
				maxKey=keuli;
			}
			cha.add(big[i+k]);
			data.put(keuli,cha);
		}else{
			Vector<char> cha;
			cha.add(big[i+k]);
			data.put(keuli,cha);
		}
	}
	return maxKey;
}
/*
This code return the random text whose first K symbols are the most frequencied in your inputted text.
*/
string randomText(string big){
	string gamosagdebi=max(big);
	for(int i=0;i<2000;i++){
		string last=gamosagdebi.substr(gamosagdebi.size()-k);
		int index=randomInteger(0,data.get(last).size()-1);
		gamosagdebi+=data.get(last)[index];
	}
	return gamosagdebi;
}