/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);

Vector< Vector<Set<string> > > subsetsOf(Vector< Set<string> >& locations);
bool contains(Vector <Set <string> > & first, Set< string>  & second);
const int numHospitals=3;
int main() {
	Vector<Set<string> > locations;
    Set<string> cities;
	cities += "A","B","C","D","E","F";
	Set<string> first;
	Set<string> second;
	Set<string> third;
	Set<string> fourth;
	first +="A","B","C";
	second +="A","C","D";
	third +="B","F";
	fourth +="C","E","F";
	locations+= first,second,third,fourth;
	Vector<Set<string> > result;
	bool q=canOfferUniversalCoverage(cities,locations,numHospitals,result);
	if(q==true){
		cout<<"We can cover cities with these elements."<<endl;
	}if(q==false){
		cout<<"It is impossible to cover cities with "<<numHospitals<<" hospitals."<<endl;
	}
    return 0;
}
/*
This code returns true if it is impossible to cover every cities with hospitals and if it is possible this vector
of set is saved in result and if it isn't possible returns false;
*/
bool canOfferUniversalCoverage(Set<string>& cities,Vector< Set<string> >& locations,
							   int numHospitals,Vector< Set<string> >& result){
									Vector< Vector< Set<string> > > sub=subsetsOf(locations);
									for(int i=0;i<sub.size();i++){
										Vector<Set<string> >copy=sub[i];
										Set<string> citycopy=cities;
										if(contains(copy,citycopy)&&copy.size()<=numHospitals){
											result=copy;
											/*Writes the elements of the result vector's set's.*/
											for(int j=0;j<copy.size();j++){
												Set<string >answer=copy[j];
												foreach(string a in answer){
													cout<<a<<" ";
												}
												cout<<endl;
											}
											return true;
										}
									}
								   return false;
}
/*
This code returns vector of vectors of sets which is possible to get from locations subsets by DFS.
*/
Vector< Vector< Set<string> > > subsetsOf(Vector< Set<string> >& locations){
	Vector< Vector< Set<string> > > result;
	if(locations.size()==0){
		Vector< Set<string> > empty;
		result.add(empty);
		return result;
	}
	Set<string> pirveli=locations[0];
	Vector< Set<string> >prev=locations;
	prev.remove(0);
	Vector< Vector< Set <string> > > previous=subsetsOf(prev);
	result=previous;
	for( int i=0;i<previous.size();i++){
		Vector< Set <string> > copy=previous[i];
		copy.add(locations[0]);
		result.add(copy);
	}
	return result;
}
/*
This code checks if every element from second set is in  the set of vectors or not
and if it is returns true else false
*/
bool contains(Vector <Set <string> > & first, Set< string> & second){
	for(int i=0;i<first.size();i++){
		Set<string> set=first[i];
		foreach(string a in set){
			if(second.contains(a)){
				second.remove(a);
			}
		}
	}
	if(second.isEmpty()){
		return true;	
	}
	return false;
}