/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();
Set<string> getSetOfProtein(string protein, Map<char, Set<string> >& codons);
int numberOfSameProteins(string & protein, Map<char,Set <string> >& codons);
Set<string> permutation(string &part);
int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();
	string protein;
	while(true){
		string RNAstrand = getLine("Enter protein(If its size is not multiply of 3 you have to input it another time): ");
		if(RNAstrand.size()%3==0){
			protein=RNAstrand;
			break;
		}
	}
	/*I divide protein size by three and multuply it by 8 because each 3 length codon have 8 different codon 
	which may bew given from this one.
	*/
	int overAllPermutations=protein.size()*8/3;
	int sameProtein=numberOfSameProteins(protein,codons);
	double possibility=double(sameProtein)/double(overAllPermutations);
	cout<<possibility<<endl;
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}

void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){
	Set<string> luka=getSetOfProtein(protein, codons);
	foreach(string word in luka){
		cout<<word<<endl;
	}
}
/*
This code returns the set of strings for the word which you entered.
*/
Set<string> getSetOfProtein(string protein, Map<char, Set<string> >& codons){
	if(protein.size()==1){
		Set<string> last;
		Set<string> vals=codons.get(protein[0]);
		foreach(string word in vals){
			last.add(word);
		}
		return last;
	}
	string prev=protein.substr(1,protein.size()-1);
	Set<string> dasabrunebeli;
	Set<string> previous=getSetOfProtein(prev, codons);
	Set<string> vals=codons.get(protein[0]);
	foreach(string word in vals){
		foreach(string prev in previous){
			string now=word;
			now+=prev;
			dasabrunebeli.add(now);
		}
	}
	return dasabrunebeli;
}
/*
This code returns the number of same strings which can be made by changing one point of RNA strand.
*/
int numberOfSameProteins(string & protein, Map<char,Set <string> >& codons){
	int sameProtein=0;
	for(int i=0;i<protein.size()-2;i+=3){
		string part=protein.substr(i,3);
		char p;
		foreach(char ch in codons){
			if(codons.get(ch).contains(part)){
				p=ch;
			}
		}
		Set<string> changed=permutation(part);
		foreach(string change in changed){
			if(codons.get(p).contains(change)){
				sameProtein++;
			}
		}
	}
	return sameProtein;
}
/*
This code returns set of strings which can be made by changing one symbol by another nucleus. 
*/
Set<string> permutation(string & part){
	Set<string> result;
	Set<string> letters;
	letters+="C","A","G","U";
	for(int i=0;i<3;i++){
		foreach(string a in letters){
		string nawili=part.substr(0,i)+a+part.substr(i+1);
		if(nawili!=part){
			result.add(nawili);
			}
		}
	}
	return result;
}