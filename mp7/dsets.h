
#ifndef _DSETS_H_
#define _DSETS_H_
#include <vector>
#include <iostream> 

using namespace std;

class DisjointSets
{
  public:
	void addelements(int n);
	int find(int target);
	void setunion(int root1, int root2);
	vector<int> set;
};
#endif
