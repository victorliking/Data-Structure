// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************
#include <iostream>
#include "quadtree.h"
//#include "png.h"
//#include "math.h"
using namespace std;
	//constructor 
	Quadtree::QuadtreeNode::QuadtreeNode()
	{
		nwChild = NULL;
		neChild = NULL;
		swChild = NULL;
		seChild = NULL;
		_x = 0;
		_y = 0;
		_resolution=0;
		
	}
	Quadtree::QuadtreeNode::QuadtreeNode(RGBAPixel const & elem)
	{
		nwChild = NULL;
		neChild = NULL;
		swChild = NULL;
		seChild = NULL;
		_x = 0;
		_y = 0;
		_resolution=0;
		element = elem;	
	}
        
	//constructor
	Quadtree::Quadtree()
	{
		root = NULL;
	}

	//build 
	Quadtree::Quadtree(const PNG & source, int resolution)
	{
		root = NULL;	
		buildTree(source,resolution);
	}
	//build_tree
	void Quadtree::buildTree(PNG const & source, int resolution)
	{		
		clear(root);
		root = buildTree_helper(source,resolution,0,0);			
	}
	//helper fucntion to build
	Quadtree::QuadtreeNode * Quadtree::buildTree_helper(PNG const & source, int res,int x, int y)
	{
		//if(node==NULL) return;
		if(res == 1)
		{
			QuadtreeNode * leaf = new QuadtreeNode;			
			leaf->element = *source(x,y);
			leaf->nwChild = NULL;	
			leaf->neChild = NULL;
			leaf->swChild = NULL;	
			leaf->seChild = NULL;
			leaf->_resolution = res;
			leaf->_x = x;
			leaf->_y = y;
			return leaf;		
		}
		else
		{
			QuadtreeNode * inter_node = new QuadtreeNode();
			inter_node->_resolution = res;
			inter_node->_x = x;
			inter_node->_y = y;
			inter_node->nwChild = buildTree_helper(source,res/2,x,y);
			inter_node->neChild = buildTree_helper(source,res/2,x+res/2,y);
			inter_node->swChild = buildTree_helper(source,res/2,x,y+res/2);
			inter_node->seChild = buildTree_helper(source,res/2,x+res/2,y+res/2);
			inter_node->element.red = (inter_node->nwChild->element.red+inter_node->neChild->element.red+inter_node->swChild->element.red+inter_node->seChild->element.red)/4;
			inter_node->element.blue = (inter_node->nwChild->element.blue+inter_node->neChild->element.blue+inter_node->swChild->element.blue+inter_node->seChild->element.blue)/4;
			inter_node->element.green = (inter_node->nwChild->element.green+inter_node->neChild->element.green+inter_node->swChild->element.green+inter_node->seChild->element.green)/4;
			return inter_node;
		}
		
	}
	//clear function
	void Quadtree::clear(QuadtreeNode * & subroot)
	{
		if(subroot!=NULL)			
		{
		clear(subroot->nwChild);
		clear(subroot->neChild);
		clear(subroot->swChild);
		clear(subroot->seChild);			
		delete subroot;
		subroot = NULL;	
		}
		//d = 0;
	}
	
	
	
	
	
	

	//get the color!!!!
	void Quadtree::getcolor(QuadtreeNode * node)
	{
		node->element.red = (node->nwChild->element.red + node->neChild->element.red + node->swChild->element.red + node->seChild->element.red)/4;
		node->element.green = (node->nwChild->element.green + node->neChild->element.green + node->swChild->element.green + node->seChild->element.green)/4;
		node->element.blue = (node->nwChild->element.blue + node->neChild->element.blue + node->swChild->element.blue + node->seChild->element.blue)/4;		
	}

	

	//copy constructor
	Quadtree::Quadtree(Quadtree const & other)
	{
		copy(root,other.root);
		//numleaves = other.numleaves;
	}

	

	//destructor
	Quadtree::~Quadtree()
	{
		clear(root);
	}


	//copy helper 
	void Quadtree::copy(QuadtreeNode * & croot, QuadtreeNode * const& source)
	{
		if (source == NULL)
		{
		croot = NULL;
		return;
		}
		croot = new QuadtreeNode();
		croot->element = source->element;
		croot->_x = source->_x;
		croot->_y = source->_y;
		croot->_resolution = source->_resolution;
		copy(croot->nwChild, source->nwChild);
		copy(croot->neChild, source->neChild);
		copy(croot->swChild, source->swChild);
		copy(croot->seChild, source->seChild);
	}



	//assignment operator 
	Quadtree const & Quadtree::operator= (Quadtree const & other)
	{
		if(this != &other)
		{		
			clear(root);
			copy(root,other.root);
		}
		return *this ;
			
	}
	
	//get pixel
	RGBAPixel Quadtree::getPixel(int x, int y) const
	{
		
 		RGBAPixel out =  getPixel_helper(x,y,root);	
		return out ;				
	}


	//helper get_pixel
	RGBAPixel Quadtree::getPixel_helper(int x,int y,QuadtreeNode * subroot) const
	{
		if(subroot->nwChild!=NULL)		
		{
			int new_res = (subroot->_resolution)/2;
			if(x<new_res && y<new_res)
			return getPixel_helper(x,y,subroot->nwChild);
		 	if(x>=new_res && y<new_res)
			return getPixel_helper(x-new_res,y,subroot->neChild);
			if(x<new_res && y >= new_res)
			return getPixel_helper(x,y-new_res,subroot->swChild);
			//if(x>=new_res && y >=new_res)
			else 		
			return getPixel_helper(x-new_res,y-new_res,subroot->seChild);
		}
		else 
		{
			return subroot->element;
		}
		 
			
	}


	//decompress
	PNG Quadtree::decompress () const
	{
		//PNG out;
		if(root == NULL)
		{
			PNG out;		 
			return out;
		}
		else 
		{		
						
			int resolution = root->_resolution;
			PNG result(resolution,resolution);
			for(int i=0;i<resolution;i++)
			{
				for(int j=0;j<resolution;j++)
				{
					RGBAPixel temp = getPixel(i,j);
					*result(i,j) = temp;
				}
			}
			//decompress_helper(root,out);
			return result;
		}	
	}

	void Quadtree::decompress_helper(QuadtreeNode * node , PNG & out) const
	{
		if(node->nwChild)
		{
			decompress_helper(node->nwChild,out);
			decompress_helper(node->neChild,out);
			decompress_helper(node->seChild,out);
			decompress_helper(node->swChild,out);			
		}
		*out(node->_x,node->_y)=this->getPixel(node->_x,node->_y);
			
	}


	//clockwise
	void Quadtree::clockwiseRotate() 
	{
		clockwise_helper(root);
		return;
	}

	//clockwise helper
	void Quadtree::clockwise_helper(QuadtreeNode *  &node)
	{
		if(node==NULL) return;
		QuadtreeNode * temp = node->nwChild;
		node->nwChild = node->swChild;
		node->swChild = node->seChild;
		node->seChild = node->neChild;
		node->neChild = temp;
		clockwise_helper(node->nwChild);
		clockwise_helper(node->neChild);
		clockwise_helper(node->seChild);
		clockwise_helper(node->swChild);
		return ;
		
	}

//prune 
	void Quadtree::prune(int tolerance) 
	{
		if(root == NULL) return ;		
		prune_helper(root,tolerance);
		return ;	
	};

	//prune helper 
	void Quadtree::prune_helper(QuadtreeNode * & node, const int tolerance)
	{
		if(node == NULL) return;
		if(node->nwChild == NULL) return;
		if(check_prune(node,node,tolerance))
		{
			clear(node->nwChild);
			clear(node->neChild);
			clear(node->swChild);
			clear(node->seChild);
			return ;
		}

		//else 
		//{
		prune_helper(node->nwChild,tolerance);
		prune_helper(node->neChild,tolerance);
		prune_helper(node->swChild,tolerance);
		prune_helper(node->seChild,tolerance);	
		//}
	}

	

	bool Quadtree::check_prune(QuadtreeNode *node1, QuadtreeNode *  node2 ,const int tolerance) const
	{
		
		//if(node == NULL) return true;
		if(node1->nwChild == NULL) 
		return (check_diff(node1,node2->element,tolerance));
			
		bool nw_Child = check_prune(node1->nwChild,node2,tolerance);
		bool ne_Child = check_prune(node1->neChild,node2,tolerance);
		bool sw_Child = check_prune(node1->swChild,node2,tolerance);
		bool se_Child = check_prune(node1->seChild,node2,tolerance);

		return (nw_Child && ne_Child && sw_Child && se_Child);
 		
	}


	bool Quadtree::check_diff(QuadtreeNode  * const & node1,  RGBAPixel  color ,int tolerance) const
	{
		int red = (node1->element.red-color.red)*(node1->element.red-color.red);
		int green = (node1->element.green-color.green)*(node1->element.green-color.green);
		int blue = (node1->element.blue-color.blue)* (node1->element.blue-color.blue);
		int sum = red + green + blue ;
		bool result = sum <= tolerance;
		//return (sum < = tol);
		return result;
	}


	int Quadtree::pruneSize(int tolerance) const 
	{
		if(root == NULL) return 0 ;
		int counter =0 ;
		prune_size(root,tolerance,counter);
		return counter;
	};
	
	void Quadtree::prune_size(QuadtreeNode * node, const int tol, int & counter) const
	{
		if(node == NULL) return ;
		if(check_prune(node,node,tol))
		{
			counter++; 
			return ;		
		}
		prune_size(node->nwChild,tol,counter);
		prune_size(node->neChild,tol,counter);	
		prune_size(node->seChild,tol,counter);
		prune_size(node->swChild,tol,counter);		
	}
	int Quadtree::idealPrune(int numLeaves) const 
	{
		return 	ideal_prune(numLeaves,0,3*255*255);
	}
	
	int Quadtree::ideal_prune(int num,int min, int max) const
	{
		if(min>max) return min;
		int mid = (min+max)/2;
		int size = pruneSize(mid);
		if(size>num)
		return ideal_prune(num,mid+1,max);
		else 
		return ideal_prune(num,min,mid-1);
	
	}
	
//bool Quadtree::operator==(Quadtree const & other) const {};	
