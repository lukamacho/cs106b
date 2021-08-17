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


int main() {
	int n=0;
	int a=0;
	while(true){
		if(randomChance(0.50)){
			cout<<"Heads"<<endl;
			a++;
			n++;
		}
		else {
			cout<<"Tails"<<endl;
			a=0;
			n++;
		}
		if(a==3){
			break;
		}
		
	}
	cout<<"It took "<<n<<" flips to get 3 heads" <<endl;
    return 0;
}
