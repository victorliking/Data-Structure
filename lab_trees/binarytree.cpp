/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary tree
 *  is just the length of the longest path from the root to a leaf, and that the
 *  height of an empty tree is -1.
 */
#include <iostream>
using namespace std;

template <typename T>
int BinaryTree<T>::height() const
{
	// Call recursive helper function on root
	
	return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node * subRoot) const
{
	// Base case
	if (subRoot == NULL)
        return -1;
	
	// Recursive definition
	return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that node
 *  itself, and everything to the right of a node will be printed out after that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
	// Call recursive helper function on the root
	printLeftToRight(root);

	// Finish the line
	cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node * subRoot) const
{
	// Base case - null node
	if (subRoot == NULL)
		return;

	// Print left subtree
	printLeftToRight(subRoot->left);

	// Print this node
	cout << subRoot->elem << ' ';

	// Print right subtree
	printLeftToRight(subRoot->right);
}

template <typename T>
void BinaryTree<T>::mirror_helper(Node *t)
{
	if(t==NULL) return ;	
	else
	{
		Node * temp; 
		mirror_helper(t->left);
		mirror_helper(t->right);
		temp = t->left;
		t->left = t->right;
		t->right = temp;	
	}
}
/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
	// your code here
	mirror_helper(root);
	
}

/**
 * @return True if an in-order traversal of the tree would produce a nondecreasing list
 *  output values, and false otherwise. This is also the criterion for a binary tree to be
 *  a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::order_helper(Node* node) const
{
        if ((node->left == NULL)&&(node->right == NULL)) 
	return true;
        if ((node->left != NULL )&&( !order_helper(node->left))) 
	return false;
        if ((node->right != NULL ) && (!order_helper(node->right))) 
	return false;
        if ((node->left != NULL )&& (node->elem < getMax(node->left))) 
	return false;
        if ((node->right != NULL)&&( getMin(node->right) < node->elem)) 
	return false;
        return true;   
}

template <typename T>
T BinaryTree<T>::getMin(Node* subroot) const
{
	T output = subroot->elem;
	if((subroot->left!=NULL)&&(getMin(subroot->left)<output))
	output = getMin(subroot->left);
	if((subroot->right!=NULL)&&(getMin(subroot->right)<output))
	output = getMin(subroot->right);
	return output;
}


template <typename T>
T BinaryTree<T>::getMax(Node* subroot) const
{
	T output = subroot->elem;
	if((subroot->left!=NULL)&&(getMax(subroot->left)>output))
	output = getMax(subroot->left);
	if((subroot->right!=NULL)&&(getMax(subroot->right)>output))
	output = getMax(subroot->right);
	return output;
}


template <typename T>
bool BinaryTree<T>::isOrdered() const 
{
    // your code here
	
	return order_helper(root);
}

/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards, ending at a
 *  leaf node. Paths ending in a left node should be printed before paths ending in a node
 *  further to the right.
 */
template <typename T>
void BinaryTree<T>::printPath_helper(Node * node, vector<T> & temp) const
{
	if(node!=NULL)
	{
		temp.push_back(node->elem);
		if(node->left==NULL&&node->right==NULL)
		{
			cout<<"Path: ";
			for(int i =0 ;i<temp.size();i++)
			{
				cout<<temp[i];
				cout<<" ";			
			}
			cout<<endl;
		}
		printPath_helper(node->left,temp);
		printPath_helper(node->right,temp);
		temp.pop_back();
	}
}
template <typename T>
void BinaryTree<T>::printPaths() const
{
    // your code here
	vector <T> temp;
	printPath_helper(root,temp);
}

/**
 * Each node in a tree has a distance from the root node - the depth of that node,
 *  or the number of edges along the path from that node to the root. This function returns
 *  the sum of the distances of all nodes to the root node (the sum of the depths of all
 *  the nodes). Your solution should take O(n) time, where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sum_helper(Node * node,int count) const
{
	if(node==NULL)
	return 0; 
	return count + sum_helper(node->left,count+1)+sum_helper(node->right,count+1);
}

template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    //int sum =0;
	return sum_helper(root,0);
}
