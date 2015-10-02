/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
#include "iostream"
using namespace std;

template <typename T>
T QuackFun::sum(stack<T> & s)
{
    // Your code here
    // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
	if(s.empty())
	return 0;
	stack<T> t = s;
	t.pop();
 	return s.top() + sum(t);
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void QuackFun::scramble(queue<T> & q)
{
	stack<T> s;
	queue<T> q2;
	int counter = 1;
	int real_counter = 1;
	while(!q.empty())
	{
		if(real_counter%2!=0)
		{
			for(int i=0;i<real_counter;i++)			
			{	
				q2.push(q.front());
				q.pop();
				if(q.empty()) break;
			}			
			counter = counter + real_counter;
			real_counter ++;		
		}
		else
		{			
			for(int i=0;i<real_counter;i++)
			{
				s.push(q.front());
				q.pop();
				if(q.empty()) break;			
			}
			while(!s.empty())
			{	
				q2.push(s.top());
				s.pop();
				
			}
			counter = counter + real_counter;
			real_counter++; 		
	 	}
	}
	while(!q2.empty())
	{
		q.push(q2.front());
		q2.pop();	
	} 
		
}

/**
 * This function is NOT part of the standard lab grade, but is extra credit.
 * It was also a previous exam question, and something similar could show up again.
 * 
 * @return true if the parameter stack and queue contain only elements of exactly
 *  the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in your return statement,
 *      and you may only declare TWO local variables of parametrized type T to use however you wish.
 *   No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be sure to comment your code VERY well.
 */
template <typename T>
bool QuackFun::verifySame(stack<T> & s, queue<T> & q)
{
    bool retval = true; // optional
    //T temp1; // rename me
    //T temp2; // rename :)
    	queue<T> queue_holder;
	stack<T> stack_holder;
	while(!q.empty())
	{
		stack_holder.push(q.front());
		q.pop();	
	}
	while((!s.empty())&&(!stack_holder.empty()))
	{
		q.push(stack_holder.top());
		queue_holder.push(s.top());
		if(stack_holder.top()!=s.top())
		retval = false ;
		stack_holder.pop();
		s.pop();			
	}	
	if((s.empty())&&(!stack_holder.empty()))
	{
		retval = false ;		
		while(!stack_holder.empty())
		{
			q.push(stack_holder.top());
			stack_holder.pop();	
		}	
	}
	if((stack_holder.empty())&&(!s.empty()))
	{
		retval = false ;		
		while(!s.empty())		
		{		
			queue_holder.push(s.top());
			s.pop();	
		}
	}
	while(!queue_holder.empty())
	{	
		s.push(queue_holder.front());
		queue_holder.pop();
	}
	while(!q.empty())
	{
		stack_holder.push(q.front());
		q.pop();	
	}
	while(!stack_holder.empty())
	{
		q.push(stack_holder.top());
		stack_holder.pop();	
	}
	
	while(!s.empty())
	{
		queue_holder.push(s.top());
		s.pop();
	}
	while(!queue_holder.empty())
	{
		s.push(queue_holder.front());
		queue_holder.pop();		
	}
	/*while(!q.empty())	
	{
		cout<<q.front()<<endl;		
		q.pop();	
	}*/
    return retval;
}

