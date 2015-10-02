/**
 * @file kdtree.h
 * KDTree implementation using Points in k-dimensional space.
 *
 * @author Cinda Heeren
 * @author Jack Toole
 * @author Sean Massung
 * @date Spring 2009
 * 
 * Revision history:
 * 3/31/2009     Created
 * 11/10/2009    Modified for MP6 Submission, Fall 2009
 * July 2012     Modified by Sean Massung to remove points_index, forbid
 *                 students from using std::sort, and generally clean up code
 */

#ifndef _KDTREE_H_
#define _KDTREE_H_

#include <vector>
#include "coloredout.h"
#include "point.h"

using std::vector;
using std::string;
using std::ostream;
using std::cout;
using std::endl;

/**
 * KDTree class: implemented using Points in Dim dimensional space (given
 * by the template parameter).
 */
template<int Dim>
class KDTree
{
    public:
       
        bool smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const;
        bool shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest,
                const Point<Dim> & potential) const;
        KDTree(const vector< Point<Dim> > & newPoints);
        Point<Dim> findNearestNeighbor(const Point<Dim> & query) const;
        void printTree(ostream & out = cout, colored_out::enable_t enable_bold = colored_out::COUT,
                int modWidth = -1) const;
        void gradingPrint(std::ostream & out) const;

    private:
        /** This is your KDTree representation. Modify this vector to create a KDTree. */
        vector< Point<Dim> > points;

        /** Helper function for grading */
        int getPrintData(int low, int high) const;
;
        /** Helper function for grading */
        void printTree(int low, int high, std::vector<std::string> & output,
                int left, int top, int width, int currd) const;

        /**
         * @todo Add your helper functions here.
         */
	int size;
	vector<int> index;
	void build_helper(int min, int max, int dimension);
	//int select(vector< Point<Dim> > & list,int left,int right,int k,int dim);
	int partition(int min,int max,int pivot,int dim);
	//int partition(vector< Point<Dim> > & list,int left,int right,int pivotIndex,int dim);
	void swap(int a, int b);
	void process(int min,int max,int k,int dim);
	int find_median(int min,int mid, int max,int dim);
	Point<Dim> search(const vector< Point<Dim> > & currPoints, const Point<Dim> & target, int left, int right, int depth) const;
	double sum(const Point<Dim> & tar, const Point<Dim> & curr) const ;
	int process(const vector<Point<Dim> > & list, int left, int right, int k, int dimension);
	int partition(vector< Point<Dim> > & currPoints, int left, int right, int pivotIndex, int curDim);
	void kdtree(vector< Point<Dim> > & currPoints, int depth, int left, int right);
	void select(vector< Point<Dim> > & currPoints, int left, int right, int k, int curDim);
	double findRadius(const Point<Dim> & first,const Point<Dim> & second) const;
	void find_help(const Point<Dim> & tar, Point<Dim> & curr, int min, int max, int dim) const;	

};

#include "kdtree.cpp"
#include "kdtree_extras.cpp"
#endif
