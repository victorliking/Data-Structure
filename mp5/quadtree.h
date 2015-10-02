// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
	Quadtree();
	Quadtree(const PNG & source, int resolution);
	Quadtree(Quadtree const & other);
	~Quadtree();
	PNG decompress () const;
	Quadtree const & operator= (Quadtree const & other);
	void buildTree(PNG const & source, int resolution);
	void clockwiseRotate();
	void prune(int tolerance);
	int pruneSize(int tolerance) const;
	RGBAPixel getPixel(int x, int y) const;
	int idealPrune(int numLeaves) const;
	
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two..
	
	class QuadtreeNode
	{
		public:
		QuadtreeNode();
		QuadtreeNode(const RGBAPixel & elem);
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child
		RGBAPixel element;  // the pixel stored as this node's "data"
		int _resolution;
		int _x;
		int _y;
		//int _x;
		//int _y;
		
	};
	void copy(QuadtreeNode* &source,QuadtreeNode* const & currNode);
	//QuadtreeNode* growQuadtree(PNG const & gSource, int gResolution, int x, int y);
	RGBAPixel findPixel(QuadtreeNode* currNode, int x, int y) const;
	void extract(QuadtreeNode* currNode, PNG& result) const;
	void prune_helper(QuadtreeNode * & node, const int tolerance);
	QuadtreeNode* root;    // pointer to root of quadtree
	void clear(QuadtreeNode * &  subroot);
	QuadtreeNode * buildTree_helper(PNG const & source, int res,int x, int y);
	//QuadtreeNode* copy(QuadtreeNode *   source);int d; 
	
	RGBAPixel getPixel_helper(int x,int y,QuadtreeNode * subroot) const;
	void getcolor(QuadtreeNode * node);
	//bool operator==(Quadtree const & other) const;	
	void clockwise_helper(QuadtreeNode * & node);
	
	bool check_prune(QuadtreeNode * node1, QuadtreeNode * node2 ,const int tolerance) const; 
	bool check_diff(QuadtreeNode  * const & node1,  RGBAPixel  color ,int tolerance) const;
	void prune_size(QuadtreeNode * node, int tol, int & counter) const ;
	void remove_prune(QuadtreeNode * &node)	;
	int ideal_prune(int num,int min, int max) const;
	void remove_node(QuadtreeNode * &node);
	void decompress_helper(QuadtreeNode * node , PNG & out)const;
	//void prune_helper(QuadtreeNode * & node, int tol,bool &able);
	//void check_prune(QuadtreeNode * cRoot,QuadtreeNode * curr,int tol,bool & able) const;
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif


