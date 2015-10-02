#include "maze.h"
//using namespace std;
#include <stdlib.h> 
#include <iostream>

using namespace std;
SquareMaze::SquareMaze(){
	_width = 0;
	_height = 0;
}
void SquareMaze::makeMaze(int height, int width){
	if(!maze.set.empty()){
		rWall.clear();
		dWall.clear();
		maze.set.clear();	
	}
	int size = width*height;
	maze.set.resize(size);
	rWall.resize(size);
	dWall.resize(size);
	for(int i =0; i<size;i++){
		maze.set[i] = -1;/////? how to intitalize?
		rWall[i] = true;
		dWall[i] = true;	
	}
	_height = height;
	_width = width;
	//int count = 0;
	//cout<<"------------------width"<<_width<<endl;
	//cout<<"-----------------height"<<_height<<endl;
	int x,y,dir;
	int a,b;
	//bool out;
	//srand(time(0));
	/*for(x=0;x<_width;x++){
		for(y=0;y<_height;y++){
			dir = rand()%2;
			//out = (((x==_width-1)&&(dir==0))||((y==_height-1)&&(dir==1)));
				a = _width*y + x;
			//if(!out){
				if(dir==0&&x!=_width-1)//{
					b = a + 1;				
				//}
				else if(dir==1&&y!=_height-1)//{
					b = a + _width;			
				//}
				else continue;
				if(maze.find(a)!=maze.find(b)){
				setWall(x,y,dir,false);					
				}
				//count++;
			//}	
		}	*/
	int count =0;
	while(count<size-1){
		deleteWall(count);
	}


}

void SquareMaze::deleteWall(int &count){
	int x,y,dir;
	int a,b;
	bool out;
	//srand(time(0));
	for(x=0;x<_width;x++){
		for(y=0;y<_height;y++){
			dir = rand()%2;
			out = (((x==_width-1)&&(dir==0))||((y==_height-1)&&(dir==1)));
			a = _width*y + x;
			if(!out){
				if(dir==0){
					b = a + 1;				
				}
				if(dir==1){
					b = a + _width;			
				}

				if(maze.find(a)!=maze.find(b)){
				setWall(x,y,dir,false);
				count++;					
				}
				//count++;
			}	
		}	
	} 
}

void SquareMaze::setWall(int x, int y, int dir, bool ex){
	int next;
	//int curr;
	//curr = 	y*_width + x;
	if(dir==0){
		next = 1 + y*_width + x;
		if(!ex){
			maze.setunion(next,y*_width + x);
			rWall[y*_width + x] = false;	
		}
		else if(!rWall[y*_width + x]){
			rWall[y*_width + x] = true;		
		}	
	}
	else {
		next = (y+1)*_width +x;
		if(!ex){
			maze.setunion(next,y*_width + x);
			dWall[y*_width + x] = false;	
		}	
		else if(!dWall[y*_width + x]){
			dWall[y*_width + x] = true;		
		}
	}
}

bool SquareMaze::canTravel(int x ,int y ,int dir){
	if(x<0||y<0||x>=_width||y>=_height){
		return false ;	
	}
	//if(_height==2&&_width==2&&dir==1)
	//return false;
	switch (dir){
	case 0 : 
		if(x>= _width-1) return false;
		else  return (!rWall[y*_width+x]);
		break;
	case 1 :
		if(y>=_height-1) return false;
		else return (!dWall[y*_width+x]);
		break;
	case 2 :
	        if(x<=0) return false;
		else return (!rWall[y*_width+x-1]);
		break;
	case 3 :
		if(y<=0) return false;
		else return (!dWall[(y-1)*_width+x]);
		break;
	}
	return false;
}



vector<int> SquareMaze::solveMaze(){
	//vector<int> path;
	int sol = 0;
	int dist[_width*_height];
	for(int i =0;i<_width;i++){
		for(int j =0;j<_height;j++)
		{
			dist[i+j*_width] = 0;		
		}	
	}	
	int * dis = &dist[0];
	calPath(0,0,dis);
	for(int k =0;k<_width;k++){
		if(dist[k+(_height-1)*_width]>dist[sol+_width*(_height-1)])
		sol = k;
			
	}
	soll = sol;
	path.clear();
	//if(path.empty()) cout<<"23333 i'm empty"<<endl;
	dist[0] = 0;
	goBack(dis,soll,_height-1);		
	return path;	
}

void SquareMaze::calPath(int x, int y, int *dis){
	
	if(canTravel(x,y,0)&&(dis[y*_width+x+1]==0)){
		dis[y*_width+x+1] = dis[y*_width+x]+1;
		calPath(x+1,y,dis);	
	}
	if(canTravel(x,y,1)&&(dis[(y+1)*_width+x]==0)){
		dis[(y+1)*_width+x] = dis[y*_width+x]+1;
		calPath(x,y+1,dis);	
	}
	if(canTravel(x,y,2)&&(dis[y*_width+x-1]==0)){
		dis[y*_width+x-1] = dis[y*_width+x]+1;
		calPath(x-1,y,dis);	
	}
	if(canTravel(x,y,3)&&(dis[(y-1)*_width+x]==0)){
		dis[(y-1)*_width+x] = dis[y*_width+x]+1;
		calPath(x,y-1,dis);	
	}
	return;
}

void SquareMaze::goBack(int * dis, int x, int y){
	//path.clear();	
	if((x==0)&&(y==0)) return ;
	if(canTravel(x,y,0)&&(dis[y*_width+x]>dis[y*_width+x+1])){
		path.insert(path.begin(),2);
		goBack(dis,x+1,y);	
	}
	else if(canTravel(x,y,1)&&(dis[y*_width+x]>dis[(y+1)*_width+x])){
		path.insert(path.begin(),3);
		goBack(dis,x,y+1);	
	}
	else if(canTravel(x,y,2)&&(dis[y*_width+x]>dis[y*_width+x-1])){
		path.insert(path.begin(),0);
		goBack(dis,x-1,y);	
	}
	else if(canTravel(x,y,3)&&(dis[y*_width+x]>dis[(y-1)*_width+x])){
		path.insert(path.begin(),1);
		goBack(dis,x,y-1);	
	}
	return;
}

PNG* SquareMaze::drawMaze()  {
	PNG * ret = new PNG(_width*10+1,_height*10+1);
	RGBAPixel black;
	black.red = 0;
	black.blue = 0;
	black.green = 0;
	for(int i =0 ;i<_width*10;i++){
		if(i>=1&&i<=9) continue;
		(*ret)(i,0)->red = black.red;
		(*ret)(i,0)->green = black.green;
		(*ret)(i,0)->blue = black.blue;	
	}
	for(int j =0;j<_height*10;j++){
		(*ret)(0,j)->red = black.red;
		(*ret)(0,j)->green = black.green;
		(*ret)(0,j)->blue = black.blue;	
	}
	for(int i =0;i<_width;i++){
		for(int j =0;j<_height;j++){		
			if(!canTravel(i, j, 0)){
				for(int k=0;k<=10;k++){
					(*ret)((i+1)*10,10*j+k)->red = black.red;
					(*ret)((i+1)*10,10*j+k)->blue = black.blue;
					(*ret)((i+1)*10,10*j+k)->green = black.green;
			
				}
			}

			if(!canTravel(i, j, 1)){
				for(int k =0;k<=10;k++){
					(*ret)(i*10+k,10*(j+1))->red = black.red;
					(*ret)(i*10+k,10*(j+1))->blue = black.blue;
					(*ret)(i*10+k,10*(j+1))->green = black.green;		
				}	
					
			}		
		}	
	}	
	return ret;
};
PNG* SquareMaze::drawMazeWithSolution() {
	PNG * ret = drawMaze(); 
	RGBAPixel red;	
	red.red = 255;
	red.green = 0;
	red.blue = 0;
	int x = 5;
	int y = 5;
	for(int i =0;i<path.size();i++){
		
		if(path[i]==0){
			for(int k=0;k<=10;k++){
				(*ret)(x+k,y)->red = red.red;
				(*ret)(x+k,y)->blue = red.blue;
				(*ret)(x+k,y)->green = red.green;		
			}
			x =x +10;			
		}
		else if(path[i]==1){
			for(int k=0;k<=10;k++){
				(*ret)(x,y+k)->red = red.red;
				(*ret)(x,y+k)->blue = red.blue;
				(*ret)(x,y+k)->green = red.green;		
			}
			y =y +10;	
		}
		else if(path[i]==2){
			for(int k=0;k<=10;k++){
				(*ret)(x-k,y)->red = red.red;
				(*ret)(x-k,y)->blue = red.blue;
				(*ret)(x-k,y)->green = red.green;		
			}
			x = x -10;	
		}
		else if(path[i]==3){
			for(int k=0;k<=10;k++){
				(*ret)(x,y-k)->red = red.red;
				(*ret)(x,y-k)->blue = red.blue;
				(*ret)(x,y-k)->green = red.green;		
			}
			y =y -10;	
		}

	
	}
	for (int k =1;k<10;k++){
		(*ret)(soll*10+k,_height*10)->red = 255;
		(*ret)(soll*10+k,_height*10)->blue = 255;
		(*ret)(soll*10+k,_height*10)->green = 255;		
	}
	
	return ret;	
};
