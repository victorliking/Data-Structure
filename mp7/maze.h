#ifndef maze_H
#define maze_H

#include "dsets.h"
#include "png.h"

class SquareMaze{
public :

	void makeMaze(int,int);
	bool canTravel(int,int,int);
	void setWall(int,int,int,bool);
	void deleteWall(int &);
	vector<int> solveMaze();
	vector<int> path;
	PNG* drawMaze() ;
	PNG* drawMazeWithSolution() ;
	void calPath(int , int , int *);
	void goBack(int * , int , int );
	SquareMaze();
	int soll;
	
private:
	DisjointSets maze;
	vector<bool> rWall;
	vector<bool> dWall;
	//vecotr<bool> visit;
	int _height;
	int _width;
	
};	
#endif
