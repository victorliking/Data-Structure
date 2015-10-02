/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
#include "iostream"
using namespace std;
template <class T>

List<T>::~List()
{	clear();
    /// @todo Graded in MP3.1
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{	if(head==NULL) return;  	
	ListNode *ptr;
	ptr=head;
	while(head->next!=NULL)
	{
	  head=head->next;
	  delete ptr;
	  ptr = head;
	}
	delete ptr;
	length=0;
	ptr=NULL;
    /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{	ListNode * newNode = new ListNode(ndata);
	newNode->next=head;
	newNode->prev=NULL;
	if (head != NULL)
	{
        head->prev=newNode;
	head=newNode;
	}
	else
	{
        head = newNode;
        tail = newNode;
	}
	length++;
    /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{	ListNode * newNode = new ListNode(ndata);
	newNode->prev=tail;
	newNode->next=NULL;
    if (tail != NULL)
    {
        tail->next = newNode;
	tail=newNode;
    }
    else
    {   
        head = newNode;
        tail = newNode;
    }
    length++;
    /// @todo Graded in MP3.1
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{	if(startPoint==NULL||endPoint==NULL)
	return ;
	if(startPoint==endPoint)
	return ;
	ListNode* former_link=startPoint->prev;;
	ListNode* later_link=endPoint->next;
	//if(startPoint!=head)   	former_link=startPoint->prev;
	//if(endPoint!=tail)	later_link=endPoint->next;
	ListNode* temp;
	//ListNode* start_holder= startPoint;
	//ListNode* end_holder = endPoint;	
	ListNode* current=startPoint;
	ListNode* limit=endPoint->next;
	while(current!=limit)
	{
		temp=current->next;	
		current->next=current->prev;
		current->prev=temp;
		current=temp;	
	}
	if(startPoint!=head&&endPoint!=tail)
	{	
		temp=startPoint;
		startPoint=endPoint;
		endPoint=temp;
		startPoint->prev=former_link;
		startPoint->prev->next=startPoint;
		endPoint->next=later_link;
		endPoint->next->prev=endPoint;
	}
	if(startPoint==head&&endPoint!=tail)
	{	
		temp=startPoint;
		startPoint=endPoint;
		endPoint=temp;
		startPoint->prev=NULL;
		endPoint->next=later_link;
		endPoint->next->prev=endPoint;
		head=startPoint;
	}
	if(startPoint!=head&&endPoint==tail)
	{	
		temp=startPoint;
		startPoint=endPoint;
		endPoint=temp;
		startPoint->prev=former_link;
		startPoint->prev->next=startPoint;
		endPoint->next=NULL;
		tail=endPoint;
	}
	if(startPoint==head&&endPoint==tail)
	{	
		temp=startPoint;
		startPoint=endPoint;
		endPoint=temp;
		startPoint->prev=NULL;
		endPoint->next=NULL;
		head=startPoint;
		tail=endPoint;
	}
	/*temp=startPoint;
	startPoint=endPoint;
	endPoint=temp;
	
	/*	
	start_holder->next=later_link;
	end_holder->prev=former_link;
	if(former_link!=NULL) former_link->next=end_holder;
	if(later_link!=NULL) later_link->prev=start_holder;
	temp=end_holder;
	end_holder=start_holder;
	start_holder=temp;
	startPoint=start_holder;
	endPoint=end_holder;
	*/
}
/*
template <class T>
void List<T>::ppplist()
{
	ListNode* tempprev;
	tempprev=tail;
	while(tempprev!=NULL)
	{
		cout<<tempprev->data<<" ";
		tempprev=temprev->prev;	
	}	
}
*/
/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{	if(n==0||n==1)
	return;
	ListNode* temp=head;
	ListNode* temp_start=head;
	while(temp!=NULL)	
	{	for(int i=1;i<n;i++)
		{
	  	if(temp->next!=NULL)
	  	temp=temp->next;
	        else break;
		}
		reverse(temp_start,temp);
		temp_start=temp->next;
		temp=temp_start;

	}
    /// @todo Graded in MP3.1
}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
	if(length<=2)	return;
	//ListNode* tail_node=tail;
	ListNode* remove;
	ListNode* curr = head;
	curr=curr->next;
	while(curr!=tail&&curr!=NULL)
	{
		curr->next->prev=curr->prev;
		curr->prev->next=curr->next;
		remove=curr;
		curr=curr->next;
		remove->prev=tail;
		remove->next=NULL;
		tail->next=remove;
		tail=tail->next;
		curr=curr->next;
	}
	   
	/// @todo Graded in MP3.1
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{	
	if(start==NULL||splitPoint==0)
	return NULL;
	ListNode* split_point=start;
	ListNode* later_link;
	for(int i=1;i<splitPoint;i++)
	{
		if(split_point->next!=NULL)		
		split_point=split_point->next;
		else break;
	}
	later_link=split_point->next;
	split_point->next=NULL;
	later_link->prev=NULL;
	//head=later_link;
	start=later_link;
	return later_link;
    /// @todo Graded in MP3.2
    
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
/*template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
			
}
*/

template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{	
	 ListNode* curr = NULL;
    
    	if(first == NULL) return second;
    	if(second == NULL) return first;

    	if(first->data < second->data)
    	{
        	curr = first;
        	curr->next = merge(first->next, second);
		curr->next->prev = curr;
    	}
    	else
    	{
        	curr = second;
        	curr->next = merge(first, second->next);
		curr->next->prev = curr;
    	}
    	return curr;
	/* ListNode* curr = NULL;
	if(first==NULL) return second;
	if(second==NULL) return first;
	if(first->data<second->data)
	{
		curr = first;
		curr->next = merge(first->next,second);	
	}
	else 
	{
		curr =second;
		curr->next=merge(first,second->next);	
	}
	return curr;
*/
	/*if(first==NULL&&second==NULL)
	return NULL;
	if(first==NULL)
	{
		first=second;
		second=NULL;
		return first;
	}		
	if(second==NULL)
	{
		return first;
	}
	ListNode* list1_node=first;
	ListNode* list2_node=second;
	ListNode* temp1;
	ListNode* temp2;
	while(list1_node->next!=NULL&&list2_node->next!=NULL)////////////infinte loop start here
	{
		
		if(list1_node->data<list2_node->data)
		{
			list1_node=list1_node->next;
			continue;
		}
		else 
		{
			if(list1_node->prev==NULL)
			{
				temp2=list2_node->next;
				temp2->prev=NULL;
				list2_node->next=list1_node;
				list1_node->prev=list2_node;
				list1_node=list2_node;
				list1_node->prev=NULL;
				first=list1_node;
				list2_node=temp2;
				//list2_node->prev=NULL;			
			}
			else 
			{
				temp2=list2_node->next;				
				temp1=list1_node->prev;
				temp1->next=list2_node;
				list2_node->prev=temp1;
				list1_node->prev=list2_node;
				list2_node->next=list1_node;
				list2_node=temp2;
				list2_node->prev=NULL;			
			}				
		}
	}
	if(list2_node->next==NULL)
	{
		if(list2_node->data<list1_node->data)
		{
			temp1=list1_node->prev;	
			if(temp1!=NULL)
			{
				temp1->next=list2_node;
				list2_node->prev=temp1;
				list1_node->prev=list2_node;
				list2_node->next=list1_node;
				second=NULL;
				
				//fisrt=list1_node;				
			}
			else
			{
				list2_node->next=list1_node;
				list1_node->prev=list2_node;
				list2_node->prev=NULL;
				second=NULL;
				first=list2_node;
								
			}			
		}
		else
		{
			if(list1_node->next==NULL)		
			{ 
				list2_node->prev=list1_node;
				list1_node->next=list2_node;
				list2_node->next=NULL;
				second=NULL;
				
			}
			if(list1_node->next!=NULL)
			{
				temp1=list1_node->next;
				list1_node->next=list2_node;
				list2_node->prev=list1_node;
				list2_node->next=temp1;
				temp1->prev=list2_node;
				second=NULL;				
			}			
		}
	return first;		
	}
	if(list1_node->next==NULL)
	{
		if(list1_node->data<list2_node->data)
		{
			list2_node->prev=list1_node;
			list1_node->next=list2_node;
			second=NULL;			
		}
		else 
		{
			if(list1_node->prev==NULL)
			{
				temp1=list2_node;
				while(list2_node->data<list1_node->data)
				{
					if(list2_node->next==NULL) break;
					list2_node=list2_node->next;
				
				}
				if(list2_node->next==NULL)
				{
					list2_node->next=list1_node;
					list1_node->prev=list2_node;
					list1_node->next=NULL;					
				}
				if(list2_node->next!=NULL)
				{
					temp2=list2_node->next;
					list2_node->next=list1_node;
					list1_node->prev=list2_node;
					list1_node->next=temp2;
					temp2->prev=list1_node;
				
				}
				temp1->prev=NULL;
				first=temp1;
			}
			else 
			{
				temp1=list1_node->prev;
				temp2=list2_node->next;
				temp1->next=list2_node;
				list2_node->prev=temp1;
				list1_node->prev=list2_node;
				list2_node->next=list1_node;
				list2_node=temp2;
				list1_node->next=list2_node;
				list2_node->prev=list1_node;
				second=NULL;				
			}			
		}		
	}

	//head=first;
	return first;
    /// @todo Graded in MP3.2

*/
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{	
	if(start==NULL||chainLength<=0)
	return NULL;
	if(chainLength==1) 
	return start;
	ListNode* right = NULL;
	ListNode* left = NULL;
	ListNode* new_start=NULL;
	//ListNode* final;

	//if(chainLength>1)
	//chainLength=chainLength/2;
	left=start;
	new_start=split(start,chainLength/2);
	//right=new_start;
	right=mergesort(new_start,chainLength-chainLength/2);
	left=mergesort(start,chainLength/2);
	return merge(left,right);
		
	
	//return final;
	/*if(start==NULL)
	return NULL;
	if (chainLength == 1||chainLength == 0||chainLength < 0)
	return start;
	ListNode* min_node;
	ListNode* temp=start;
	ListNode* begin_node=NULL;
	ListNode* begin_holder=start;
	ListNode* former_link;
	ListNode* later_link;
	int min=start->data;
	int step=0;
	int woqu=chainLength;
	while(start!=NULL&&step!=chainLength)
	{
		min_node = start;
		min=min_node->data;
		temp = start->next;

		for(int j=0;j<woqu;j++)
		{	
			if(temp==NULL)
			break;		
			if(temp->data<min)
			{
				min_node=temp;
				min=min_node->data;
			}
			temp=temp->next;			
		}
		former_link=min_node->prev;
		later_link=min_node->next;
		if(former_link!=NULL)
		former_link->next=later_link;
		if(later_link!=NULL)
		later_link->prev=former_link;
		step++;
		start=start->next;
		if(step==1)
		{
			begin_node=min_node;
			begin_node->prev=NULL;
			begin_holder=begin_node;		
		}
		else if(step==woqu)
		{
			begin_node->next=min_node;
			min_node->prev=begin_node;
			min_node->next=NULL;			
		}
		else
		{
			begin_node->next=min_node;
			min_node->prev=begin_node;
			begin_node=begin_node->next;		
		}

	}
	return begin_holder;
	/*ListNode *temp = start;
	ListNode *begin_node = start;
	ListNode *min_node=NULL;
	ListNode *former_holder=NULL;
	ListNode *later_holder=NULL; 
	int min ;
	int step=chainLength;
	while(begin_node!=NULL)
	{	
		temp=begin_node;
		min=begin_node->data;
		for(int i = 0;i<chainLength&&temp!=NULL;i++)
		{
			if(temp->data<min)
			{
				min_node=temp;
				min=temp->data;			
			}
			temp=temp->next;		
		}
		former_holder=min_node->prev;
		later_holder=min_node->next;
		if(begin_node->prev!=NULL)
		{ 
			begin_node->prev->next=min_node;		
		}
		else 
		{		
			min_node->prev=NULL;
		}		
		if(begin_node->next!=NULL)
		{
			begin_node->next->prev=min_node;
		}
		else 
		{	
			min_node->next=NULL;
		}
		min_node->prev=begin_node->prev;
		min_node->next=begin_node->next;
		begin_node=min_node;
		if(former_holder!=NULL)
		{
			former_holder->next=later_holder;		
		}
		else
		{
			later_holder->prev=NULL;		
		}
		if(later_holder!=NULL)
		{
			later_holder->prev=former_holder;		
		}
		else
		{
			former_holder->next=NULL;		
		}	
		begin_node=begin_node->next;
		chainLength=chainLength-1;
	}
	for(int i=0;i<step;i++)
	{
		begin_node=begin_node->prev;	
	}
	start=begin_node;
	return start;
        ListNode* end_holder=start;
	for(int i=0;i<chainLength;i++)
	{
		if(end_holder->next==NULL) break;
		end_holder=end_holder->next;	
	}
	ListNode* temp_begin=start;
	ListNode* temp_swap=NULL;
	ListNode* former_holder=NULL;
	ListNode* later_holder=NULL;
	ListNode* temp_next=NULL;
	for(int i=0;i<chainLength;i++)
	for(int j=0;j<i-1;j++)
	{
		start=start->next;
		if(temp_next->data<temp_begin->data)
		{
			former_holder=temp_begin->prev;
			later_holder=temp_next->next;
			temp_swap=temp_next;
			temp_next=temp_begin;
			temp_begin=temp_swap;
			if(former_holder!=NULL)
			{
				former_holder->next=temp_next;
				temp_next->prev= former_holder;			
			}
			else 
			{
				temp_next->prev=NULL;			
			}
			if(later_holder!=NULL)
			{
				temp_begin->next=later_holder;
				later_holder->prev=temp_begin;						
			}		
			else 
			{
				temp_begin->next=NULL;			
			}		
			temp_begin->prev=temp_next;
			temp_next->next=temp_begin;
		}	
	}
	temp_begin->next=end_holder;
	while(temp_begin->prev!=NULL)
	{
		temp_begin=temp_begin->prev;		
	}
	start=temp_begin;
	return start;
	*/
	//return NULL;
	
}














