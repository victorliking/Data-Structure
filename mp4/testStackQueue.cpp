#include <iostream>
#include "stack.h"
#include "queue.h"
using namespace std;

void testStack(){
  cout << "Testing Stack..." << endl;
  Stack<int> intStack;
  for(int i=1;i<=10;i++){
    intStack.push(i);
	//cout<<intStack.peek()<<endl;
  }
	//cout<<intStack.size()<<endl;
  //intStack.pop();  
  cout << intStack.peek() << endl;
  while( !intStack.isEmpty() ){
    cout << intStack.pop() << " ";
  }
  cout << endl;
	//if(intStack.isEmpty())
	//cout<<"you are right for stack"<<endl;
}

void testQueue(){
  cout << "Testing Queue..." << endl;
  Queue<int> intQueue;
  for(int i=1;i<=10;i++){
    intQueue.enqueue(i);
  }
  //intQueue.dequeue();
  cout << intQueue.peek() << endl;
  while( !intQueue.isEmpty() ){
    cout << intQueue.dequeue() << " ";
  }
  cout << endl;
   //if(intQueue.isEmpty())
	//cout<<"you are right for queue "<<endl;
}


int main(){
  testStack();
  testQueue();
  return 0;
}
