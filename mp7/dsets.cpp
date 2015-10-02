#include "dsets.h"

void DisjointSets::addelements(int n)
{
	set.resize((set.size()+n),-1);
}

int DisjointSets::find(int elem)
{
	if(elem<set.size())
	{
		if(set[elem]<0) 
		return elem;
		else return find(set[elem]);	
	}
	return -1;
}

void DisjointSets::setunion(int a, int b)
{
	int root1 = find(a);
	int root2 = find(b);
	if(root1==root2) 
	return ;
	int new_size = set[root1]+set[root2];
	if(set[root1]<=set[root2])
	{
		set[root2] = root1;
		set[root1] = new_size;	
	}
	else
	{
		set[root1] = root2;
		set[root2] = new_size; 	
	}
}
