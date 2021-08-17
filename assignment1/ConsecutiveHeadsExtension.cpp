/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include <cstdlib>
#include "random.h"
using namespace std;

string yourorder();
bool  onlyHT(string a);
int main() {
	int n=0;
	string arioli=yourorder();
    string reshka="";
	while(true){
		if(randomChance(0.50)){
			cout<<"Heads"<<endl;
			reshka+='H';
			n++;
		}
		else {
			cout<<"Tails"<<endl;
			reshka+='T';
			n++;
		}
		size_t found=reshka.find(arioli);
		if(found!=string::npos){
			break;
		}
		
	}
	cout<<"It took "<<n<<" flips to get" <<arioli<<endl;
    return 0;
}
/*
This method allows you to enter string which you want to be reached.
*/
string yourorder(){
	while(true){
		string arioli=getLine("Enter word with H-s and T-s");
		if(onlyHT(arioli)){
			return arioli;
			break;
		}
	}
}
/*
This method checks if the string contains only H's and T's or not.
*/
bool onlyHT(string a){
	for(int i=0;i<a.size();i++){
		if(a[i]!='H'&&a[i]!='T'){
			return false;
		}
	}
	return true;
}
