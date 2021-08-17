/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"

using namespace std;



/*
This function checks if the coordinates are in borders or not and if it coicides the current point and 
if return false, otherwise true.
*/

bool isValid(int x, int y, Loc current, Grid<double> & world){
	if(x==current.row&&y==current.col){
		return false;
	}
	if(x<0||y<0||x>=world.numRows()||y>=world.numCols()){
		return false;
	}
	return true;
}

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
			 double heuristic(Loc current, Loc end, Grid<double>& world)) {
	 /*This grid is used to store the information about the parent*/
	Grid<Loc> parentAddress(world.numRows(),world.numCols());

	/*This grid is used to store the cost of the path*/
	Grid<double> pathCost(world.numRows(),world.numCols());
	pathCost[start.row][start.col]=0;
	
	/*This grid is used to store the information about the color of the locations*/
	Grid<Color> locationColors(world.numRows(),world.numCols());
	for(int i=0;i<world.numRows();i++){
		for(int j=0;j<world.numCols();j++){
			locationColors[i][j]=GRAY;
		}
	}
	locationColors[start.row][start.col]=YELLOW;
	TrailblazerPQueue <Loc> toVisit;
	toVisit.enqueue(start,heuristic(start,end,world));
	colorCell(world,start,YELLOW);
	while(!toVisit.isEmpty()){
		Loc current=toVisit.dequeueMin();
		locationColors[current.row][current.col]=GREEN;
		colorCell(world,current,GREEN);
		if(current==end){
			break;
		}
		for(int i=current.row-1;i<current.row+2;i++){
			for(int j=current.col-1;j<current.col+2;j++){
				if(isValid(i,j,current,world)){
					Loc neigh=makeLoc(i,j);
					double newCost=pathCost[current.row][current.col]+
						costFn(current,neigh,world);
					if(locationColors[neigh.row][neigh.col]==GRAY){
						locationColors[neigh.row][neigh.col]=YELLOW;
						colorCell(world,neigh,YELLOW);
						parentAddress[i][j]=current;
						pathCost[i][j]=newCost;
						toVisit.enqueue(neigh,newCost+heuristic(neigh,end,world));
					}else if(locationColors[neigh.row][neigh.col]==YELLOW&&
						pathCost[neigh.row][neigh.col]>newCost){
						pathCost[neigh.row][neigh.col]=newCost;
						parentAddress[neigh.row][neigh.col]=current;
						toVisit.decreaseKey(neigh,newCost+heuristic(neigh,end,world));
					}
				}
			}
		}
	}
	Vector<Loc> Path;
	Loc curr =end;
	while(curr!=start){
		Path.add(curr);
		curr=parentAddress[curr.row][curr.col];
	}
	Path.add(start);
    return Path;
}

/*
This function makes Horizontal Edges and adds them in the set called maze.
*/
void makeHorizontalEdges(Set<Edge> & maze,int numRows, int numCols){
	for(int i=0;i<numRows;i++){
		for(int j=0;j<numCols-1;j++){
			Loc start=makeLoc(i,j);
			Loc end=makeLoc(i,j+1);
			Edge horizontal=makeEdge(start,end);
			maze.add(horizontal);
		}
	}
}

/*
This function makes Vertical Edges and adds them in the set called maze.
*/
void makeVerticalEdges(Set<Edge>& maze,int numRows, int numCols){
	for(int i=0;i<numCols;i++){
		for(int j=0;j<numRows-1;j++){
			Loc start=makeLoc(j,i);
			Loc end=makeLoc(j+1,i);
			Edge vertical=makeEdge(start,end);
			maze.add(vertical);
		}
	}
}
/*
This function returns the parent of current Loc.
*/
Loc findSet(Loc current, Grid<Loc>& board){
	if(board[current.row][current.col]==current){
		return current;
	}
	board[current.row][current.col]=findSet(board[current.row][current.col],board);
	return board[current.row][current.col];
}
/*
Defines if the two locs have same parent or not.
*/
bool connectedClusters(Loc start,Loc end, Grid<Loc> & board){
	Loc parent=findSet(start,board);
	Loc secondParent=findSet(end,board);
	if(parent!=secondParent){
		board[secondParent.row][secondParent.col]=parent;
	}
	return parent==secondParent;
}
/*
Creates random maze with the number of rows and cols, generates edges with random weight, and builds
minimum spanning tree.
*/
Set<Edge> createMaze(int numRows, int numCols) {
	Set<Edge> maze;
	makeHorizontalEdges(maze,numRows,numCols);
	makeVerticalEdges(maze,numRows,numCols);
	TrailblazerPQueue<Edge> weights;
	foreach(Edge current in maze ){
		double a=randomReal(0,1);
		weights.enqueue(current,a);
	}
	int clusterNumber=numRows*numCols;
	Grid<Loc> board (numRows,numCols);
	for(int i=0;i<numRows;i++){
		for(int j=0;j<numCols;j++){
			Loc cur=makeLoc(i,j);
			board[i][j]=cur;
		}
	}
	Set<Edge> result;
	while(!weights.isEmpty()&&clusterNumber>1){
		Edge current=weights.dequeueMin();
		Loc start=current.start;
		Loc end=current.end;
		if(!connectedClusters(start,end,board)){
			result+=current;
			clusterNumber--;
		}
	}
	
    return result;
}
