#include <bits/stdc++.h>
using namespace std;
class Stack{
 
    int top;
    int *arr;
    int capacity;
  public:
    Stack(int s){
        this -> top = -1;
        this -> capacity = s;
        arr = new int[capacity];
    }
    void push(int val){
        if(top == capacity){
         cout << "Stack is full" << endl;
         return;
        }
        arr[++top] = val;
    }
    void pop(){
        if(top == -1){
         cout << "Stack is empty" << endl;
         return;
        }
        arr[top] = 0;
        top--;
    }
    int peek(){
        if(top == -1)
         return -1;
        return arr[top]; 
    }
    int size(){
        return top + 1;
    }
    int isempty(){
        if(top == -1)
         return 1;
        else
         return 0;
    }
};

int main() {
	int t;
	cin >> t;
	
	Stack ob(INT_MAX);
	while(t--){
	    string s;
	    int element = 0;
	    cin >> s;
	     
	    if(s == "push"){
	        cin >> element;
	        ob.push(element);
	    }
	        
	    if(s == "pop")
	     ob.pop();
	     
	    if(s == "peek")
	     cout << ob.peek() << endl;
	    
	    if(s == "size")
	     cout << ob.size() << endl;
	     
	    if(s == "isempty")
	     cout << ob.isempty() << endl;
	     
	     
	}
	return 0;
}
