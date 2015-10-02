/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <iostream>
using namespace std;


template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
	
    	if(first[curDim]==second[curDim])
	return first<second;
	else 
	return first[curDim]<second[curDim];
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    /**
     * @todo Implement this function!
     */
	int curr_dis = 0;
	int pote_dis = 0 ;
	for(int i=0; i<Dim; i++)
	{
		curr_dis = curr_dis + (currentBest[i]-target[i])*(currentBest[i]-target[i]);
		pote_dis = pote_dis + (potential[i]-target[i])*(potential[i]-target[i]);	
	}
	if(curr_dis==pote_dis)	
	return potential<currentBest;
	else 
	return curr_dis>pote_dis;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{

	    int n = newPoints.size();
	    if(n >= 2)
	    {
		points = newPoints;
		kdtree(points, 0, 0, n-1);
	    }

   	//@todo Implement this function!
}

template<int Dim>
void KDTree<Dim>::kdtree(vector< Point<Dim> > & currPoints, int depth, int left, int right)
{
    if(left >= right || right >= currPoints.size() || left < 0) return;         //no more 
    int curDim = depth % Dim;                                                   //
    int newPivot = (left + right)/2;                                        //new pivot
    select(currPoints, left, right, newPivot, curDim);
    kdtree(currPoints, depth+1, left, newPivot-1);
    kdtree(currPoints, depth+1, newPivot+1, right);
    return;
}


template<int Dim>
void KDTree<Dim>::select(vector< Point<Dim> > & currPoints, int left, int right, int k, int curDim)
{
    if(left >= right || right >= currPoints.size() || left < 0) return;
    int pivotIndex = (left + right)/2;
    int pivotNewIndex = partition(currPoints, left, right, pivotIndex, curDim);
    if(pivotNewIndex == k) return;
    else if(pivotNewIndex < k)
        select(currPoints, pivotNewIndex + 1, right, k, curDim);
    else
        select(currPoints, left, pivotNewIndex - 1, k, curDim);
}

template<int Dim>
void KDTree<Dim>::build_helper(int min,int max, int dim)
{
	if(min>=max) return;
	process(min,max,(min+max)/2,dim);
	if(min<=(min+max)/2-1)
	build_helper(min,(min+max)/2-1,(dim+1)%Dim);
	if((min+max)/2+1<=max)
	build_helper((min+max)/2+1,max,(dim+1)%Dim);
	return;
}



template<int Dim>
void KDTree<Dim>::process(int min,int max,int k,int dim)
{
	if(min>=max) return;	
	//int pivot = find_median(min,(max+min)/2,max,dim);
	int pivot = (max+min)/2;	
	int newPivotIndex = partition(min,max,pivot,dim);
	if(k==newPivotIndex)
	return;
	else if(k<newPivotIndex)
	process(min,newPivotIndex-1,k,dim);
	else 
	process(newPivotIndex+1,max,k,dim);	
}

template<int Dim>
int KDTree<Dim>::find_median(int min,int mid, int max,int dim)
{
	double low = points[index[min]][dim];
	double med = points[index[mid]][dim];
	double high = points[index[max]][dim];
	if(low<high&&med<high)
	{
		if(low<med) 	return mid;
		else 		return min;		
	}		
	else if(low<med&&high<med)
	{
		if(low<high)  	return max;
		else 		return min;	
	}
	else 
	{
		if(med<high)	return max;
		else 		return mid;	
	}
}



template<int Dim>
int KDTree<Dim>::partition(vector< Point<Dim> > & currPoints, int left, int right, int pivotIndex, int curDim)
{
    Point<Dim> pivotValue = currPoints[pivotIndex];
    currPoints[pivotIndex] = currPoints[right];
    currPoints[right] = pivotValue;

    int storeIndex = left;
    for(int i = left; i < right; i++)
    {
        if(smallerDimVal(currPoints[i], pivotValue, curDim))
        {
            Point<Dim> tmp = currPoints[i];
            currPoints[i] = currPoints[storeIndex];
            currPoints[storeIndex] = tmp;
            storeIndex++;
        }
    
    }
    Point<Dim> temp = currPoints[storeIndex];
    currPoints[storeIndex] = currPoints[right];
    currPoints[right] = temp;
    return storeIndex;
}

template<int Dim>
void KDTree<Dim>::swap(int a, int b)
{
	int temp = index[a];
	index[a] = index[b];
	index[b] = temp;
}

/*

template <int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
	if(newPoints.empty()) return;
	size = newPoints.size();
	//points = newPoints;
	for(int i =0;i<size;i++)
	{
		index.push_back(i);
		points.push_back(newPoints[i]);	
	}
	build_helper(0,size-1,0);
}

template <int Dim>
void KDTree<Dim>::build_helper(int min, int max, int dim)
{
	int mid = (min+max)/2;
	int t = mid-min+1;
	if(min>=max) return;
	int pivotIndex = process(points,min,max,t,dim);
	dim++;
	build_helper(min,pivotIndex-1,dim%Dim);
	build_helper(pivotIndex+1,max,dim%Dim);
}

template <int Dim>
int KDTree<Dim>::process(const vector<Point<Dim> > & list, int left, int right, int k, int dim)
{
	if(left>=right) return left;
	int pivot = left;
	int newPivot = partition(list,left,right,pivot,dim);
	int dis = newPivot - left +1;
	if(dis==k)
	return newPivot;
	else if (k<dis)
	return process(list,left,newPivot-1,k,dim);
	else 
	return process(list,newPivot+1,right,k-newPivot,dim);
}


template<int Dim>
int KDTree<Dim>::partition(const vector<Point<Dim> > & list, int min, int max, int pivot, int dim)
{
	Point<Dim> value = list[index[pivot]];
	swap(pivot,max);
	int curr = min;
	for(int i = min;i<max;i++)
	{
		if(smallerDimVal(list[index[i]],value,dim))
		swap(curr,i);
		curr++;	
	}
	swap(max,curr);
	return curr;
}

*/

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
    /**
     * @todo Implement this function!
     */
	 int size_ = points.size();
    	if(size_ == 0) return Point<Dim>();
    	return search(points, query, 0, size_-1, 0);
}

template<int Dim>
void KDTree<Dim>::find_help(const Point<Dim> & tar, Point<Dim> & curr, int min, int max, int dim) const
{
	if(min>=max)
	{
		if(shouldReplace(tar,curr,points[min]))
			curr = points[min];
		else 
			return;	
	}

	dim ++;
	dim = dim%Dim;
	
	int cur_index = (min+max)/2;
	double dis = (tar[dim] - points[cur_index][dim])*(tar[dim] - points[cur_index][dim]);
	if(shouldReplace(tar,curr,points[cur_index]))
	{
		curr = points[cur_index];	
	}
	if(smallerDimVal(tar,points[cur_index],dim))
	{
		find_help(tar,curr,min,cur_index-1,dim);
		//double after_dis = (tar[dim] - points[cur_index][dim])*(tar[dim] - points[cur_index][dim]);
		double after_dis = sum(tar,curr);		
		if(dis<=after_dis)
		find_help(tar,curr,cur_index+1,max,dim);	
	}
	else if(smallerDimVal(points[cur_index],tar,dim))
	{
		find_help(tar,curr,cur_index+1,max,dim);
		//double after_dis = (tar[dim] - points[cur_index][dim])*(tar[dim] - points[cur_index][dim]);
		double after_dis = sum(tar,curr);		
		if(dis<=after_dis)
		find_help(tar,curr,min,cur_index-1,dim);	
	}
}


template<int Dim>
double KDTree<Dim>::sum(const Point<Dim> & tar, const Point<Dim> & curr) const
{
	double result  =0;
	for(int i =0 ;i<Dim;i++)
	{
		result = result + (tar[i]-curr[i])*(tar[i]-curr[i]);	
	}
	return result;
}


template<int Dim>
Point<Dim> KDTree<Dim>::search(const vector< Point<Dim> > & currPoints, const Point<Dim> & target, int left, int right, int depth) const
{
    int curDim = depth % Dim;
    int curRoot = (left + right)/2;
    Point<Dim> currentBest, potential;
    if(left >= right) return currPoints[curRoot];
    else if(smallerDimVal(target, currPoints[curRoot], curDim))
    {
        currentBest = search(currPoints, target, left, curRoot-1, depth+1);
        potential = currPoints[curRoot];
        if(shouldReplace(target, currentBest, potential))
        {
            currentBest = potential;
        }
        double radius = findRadius(currentBest, target);
        double distance = (target[curDim] - currPoints[curRoot][curDim])*(target[curDim] - currPoints[curRoot][curDim]);
        if(distance <= radius)
        {
            potential = search(currPoints, target, curRoot+1, right, depth+1);
            if(shouldReplace(target, currentBest, potential))
                currentBest = potential;
        }
        return currentBest;        
    }
    else
    {
        currentBest = search(currPoints, target, curRoot+1, right, depth+1);
        potential = currPoints[curRoot];
        if(shouldReplace(target, currentBest, potential))
        {
            currentBest = potential;
        }
        double radius = findRadius(currentBest, target);
        double distance = (target[curDim] - currPoints[curRoot][curDim])*(target[curDim] - currPoints[curRoot][curDim]);
        if(distance <= radius)
        {
            potential = search(currPoints, target, left, curRoot-1, depth+1);
            if(shouldReplace(target, currentBest, potential))
                currentBest = potential;
        }
        return currentBest;
    }
}

template<int Dim>
double KDTree<Dim>::findRadius(const Point<Dim> & first,const Point<Dim> & second) const
{
    double rad = 0;
    for(int i = 0; i < Dim; i++)
    {
        rad = rad + (first[i]-second[i])*(first[i]-second[i]);
    }
    return rad;
}

