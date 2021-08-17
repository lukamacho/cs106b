/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

int combinations(int n,int k){
	if(k==0||k==n){
		return 1;
	}else {
		return combinations(n-1,k-1)+combinations(n-1,k);
	}
}



int main() {
    int n=getInteger("Enter first integer");
	int k=getInteger("Enter second integer");
	int c=combinations(n,k);
	cout<<c<<endl;
    return 0;
}
