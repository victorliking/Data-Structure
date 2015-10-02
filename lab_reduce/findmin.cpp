/**
 * @file findmin.cpp
 * Implementation of the findmin namespace.
 *
 * @author Chase Geigle
 * @date Spring 2012
 */
#include "findmin.h"
#include <omp.h>
/**
 * Finds the minimum element in a sequence of type T.
 * Assumes a well defined operator< exists for the type T.
 * If the parameter list is empty, it should return a default T.
 *
 * You will need to modify this function to use OpenMP to parallelize the
 * search.
 *
 * @param list The list of type T to find the minimum element in.
 * @return The minimum element in the sequence.
 */
template <class T>
T findmin::minimum( const vector<T> & list ) {
	// Implement and parallelize this code!
	if(list.empty())	
	return T();
	T min = list[0];
	#pragma omp parallel
	{
		T local_min = min;
		#pragma omp for 
		for(int i= 0;i<(int)list.size();i++)
			if(list[i]<local_min)
			local_min = list[i];
		#pragma omp critical 
		{
			if(local_min<min)
			min = local_min;		
		}		
	}
	return min;
}
