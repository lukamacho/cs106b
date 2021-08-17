/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "vector.h"
#include "set.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
Grid<char> paintCubes();
Set<string> playerMove(Lexicon & english,Map<string,Vector<int> > &allWords,Grid<char> & board);
bool existSuchWord(Set<string> & words,Lexicon & english,string word,Map<string,Vector<int> >& allWords);
Map<string,Vector<int> > wordsGeneration(Grid<char> &board,Lexicon& english);
Map<string, Vector<int> >wordsStartedFrom(string word,Lexicon & english,Grid<char>board,int i, int j,Vector<int>luka);
void computerMove(Map<string,Vector<int> > & all, Set<string> & player);
void highlightWord(Vector<int> akaki, Grid<char>& board,bool q);
/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
	Lexicon english("EnglishWords.dat");
    initGBoggle(gw);
    welcome();
    giveInstructions();
	while(true){
	Grid<char> board=paintCubes();
	Map<string,Vector<int> > allWords=wordsGeneration(board,english);
	Set<string>playerWords=playerMove(english,allWords,board);
	computerMove(allWords,playerWords);
	string answer=getLine("Do you want to continue gaming?");
	if(answer=="no"){
		break;
	}
	}
    return 0;
}
/*
This function highlight the word.
*/
void highlightWord(Vector<int> coordinates,Grid<char>& board,bool q){
	for(int i=0;i<coordinates.size();i+=2){
		highlightCube(coordinates[i], coordinates[i+1], q);
			}
}
/*
Description of the computer move.
*/
void computerMove(Map<string,Vector<int> > & allWords,Set<string>& playerWords){
	foreach(string a in allWords){
		if(!playerWords.contains(a)){
			recordWordForPlayer(a,COMPUTER);
		}
	}
}
/*
Return vetor of words started from some index with recursion after discussing every neighbour of the cube.
*/
Map<string, Vector<int> > wordsStartedFrom(string word,Lexicon & english,Grid<char>board,int i, int j,Vector<int>coordinates){
	Map<string,Vector<int> >data;
	coordinates.add(i);
	coordinates.add(j);
	if(!english.containsPrefix(word)){
	return data;
	}if(word[word.size()-1]=='-'){
		return data;
	}
	Grid<char>next=board;
	next[i][j]='-';
	if(word.size()>3&&english.contains(word)){
		data.put(word,coordinates);
	}/*continue from the upper neighbour cube*/
	if(i<board.numCols()-1){
		Vector<int> nextcoor=coordinates;
		string upper=word;
		upper+=board[i+1][j];
		Map<string,Vector<int> > step=wordsStartedFrom(upper,english,next,i+1,j,nextcoor);
		foreach(string word in step){
			if(!data.containsKey(word)){
				data.put(word,step[word]);}
		}
	}/*continue from the lower neighbour cube*/
	if(i>0){
		Vector<int> nextcoor=coordinates;
		string lower=word;
		lower+=board[i-1][j];
		Map<string,Vector<int> >step=wordsStartedFrom(lower,english,next,i-1,j,nextcoor);
		foreach(string word in step){
			if(!data.containsKey(word)){
				data.put(word,step[word]);}
		}
	}/*Continue from the left cube*/
	if(j>0){
		Vector<int> nextcoor=coordinates;
		string lower=word;
		lower+=board[i][j-1];
		Map<string,Vector<int> >step=wordsStartedFrom(lower,english,next,i,j-1,nextcoor);
		foreach(string word in step){
			if(!data.containsKey(word)){
				data.put(word,step[word]);}
		}
	}/*Continue recursion from the right cube*/
	if(j<3){
		Vector<int> nextcoor=coordinates;
		string upper=word;
		upper+=board[i][j+1];
		Map<string,Vector<int> >ta=wordsStartedFrom(upper,english,next,i,j+1,nextcoor);
		foreach(string word in ta){
			if(!data.containsKey(word)){
				data.put(word,ta[word]);}
		}
	}/*Continue recursion from the lower left cube*/
	if(j>0&&i>0){
		Vector<int> nextcoor=coordinates;
		string under=word;
		under+=board[i-1][j-1];
		Map<string,Vector<int> > step=wordsStartedFrom(under,english,next,i-1,j-1,nextcoor);
		foreach(string word in step){
		if(!data.containsKey(word)){
				data.put(word,step[word]);}
		}
	}/*Continue recursion from the upper right cube */
	if(i<3&&j<3){
		Vector<int>nextcoor=coordinates;
		string up=word;
		up+=board[i+1][j+1];
		Map<string,Vector<int> > step=wordsStartedFrom(up,english,next,i+1,j+1,nextcoor);
		foreach(string word in step){
			if(!data.containsKey(word)){
			data.put(word,step[word]);
			}
		}
	}/*Continue recursion from the upper left cube*/
	if(i>0&&j<3){
		Vector<int> nextcoor=coordinates;
		string up=word;
		up+=board[i-1][j+1];
		Map<string,Vector<int> >step=wordsStartedFrom(up,english,next,i-1,j+1,nextcoor);
		foreach(string word in step){
			if(!data.containsKey(word)){
				data.put(word,step[word]);
			}
		}
	}/*Continue recursion from the lower right cube*/
	if(i<3&&j>0){
		Vector<int> nextcoor=coordinates;
		string low=word;
		low+=board[i+1][j-1];
		Map<string, Vector<int> > step=wordsStartedFrom(low,english,next,i+1,j-1,nextcoor);
		foreach(string word in step){
			if(!data.containsKey(word)){
			data.put(word,step[word]);
			}
		}
	}
	
	return data;
}
/*
This function generates words which can be made up with chars in grid and return them with the
vector of its coordinates.
*/
Map<string,Vector<int> > wordsGeneration(Grid<char> &board,Lexicon & english){
	Map<string,Vector<int> > result;
	for(int i=0;i<board.numCols();i++){
		for(int j=0;j<board.numRows();j++){
			string a="";
			a+=board[i][j];
			Vector<int> coordinates;
			Map<string,Vector<int> > recursion=wordsStartedFrom(a,english,board,i,j,coordinates);
			foreach(string word in recursion){
				result.put(word,recursion[word]);
			}
		}
	}
	return result;
}
/*
Checks if the word exist and it is used before or not and return false if it doesn't meet the conditions
and returns true otherwise.
*/
bool existSuchWord(Set<string> & words,Lexicon & english,string word,Map<string,Vector<int> >& allWords){
	if(word.size()<4){
		cout<<"I'm sorry but we have our standards."<<endl;
		cout<<"Enter the word which size is more than 3."<<endl;
		return false;
	}else if(!english.contains(word)){
		cout<<"That's not a word."<<endl;
		return false;
	}else if(words.contains(word)){
		cout<<"You've already entered such word."<<endl;
		return false;
	}else if(!allWords.containsKey(word)){
		cout<<"It's impossible to get this word."<<endl;
		return false;
	}
	words.add(word);
	return true;
}
/*
This function gives the player an oppourtunity to write down words until he has nerves.
*/
Set<string> playerMove(Lexicon& english,Map<string,Vector<int> > & allWords,Grid<char> &board){
	Set<string> words;
	string last="";
	while(true){
		string word=getLine("Enter a word:");
		if(word==""){
			break;
		}if(allWords.containsKey(last)){
			highlightWord(allWords[last],board,false);}
		for(int i=0;i<word.size();i++){
			word[i]=toupper(word[i]);
		}
		if(existSuchWord(words,english,word,allWords)){
			recordWordForPlayer(word,HUMAN);
			words.add(word);
			highlightWord(allWords[word],board,true);
			last=word;
		}
	}
	return words;
}
/*
This function paints cubes on the board and writes random chars in them from 4*4 cons array.
*/
Grid<char> paintCubes(){
	Vector <string> vec;
	for(int i=0;i<16;i++){
		vec.add(STANDARD_CUBES[i]);
	}
	for(int i=0;i<vec.size();i++){
		int x=randomInteger(i,vec.size()-1);
		string a=vec[i];
		vec[i]=vec[x];
		vec[x]=a;
	}
	drawBoard(4,4);
	Grid<char> board(4,4);
	for(int i=0;i<vec.size();i++){
		int a=(int)i/4;
		int b=i-a*4;
		int x=randomInteger(0,5);
		char c=vec[i][x];
		board[a][b]=c;
		labelCube(a,b,c);
	}
	return board;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

