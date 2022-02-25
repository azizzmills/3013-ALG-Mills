///////////////////////////////////////////////////////////////////////////////
//
// Author:           Azizz Mills 
// Email:            azizzmillz@gmail.com
// Title:            Lecture 01 - Array Based Stack
// Course:           3013 - 201
// Semester:         Spring 2022
//
// Description:
//       Overview of a class implementing an array based stack
//
//
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

/**
 * ArrayStack
 * 
 * Description:
 *      Array based stack
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
class ArrayStack {
private:
    int *A;   // pointer to array of int's
    int size; // current max stack size
    int top;  // top of stack 
    int count=0;  
    int amountResized = 0; // get the amount of times the stack is resized
    int TotalStackSize = 0;  // gets the total size of the stack
    double startResize; // percentage to start making the size bigger
    double startShrink; // percentage to start making the size smaller
    double resize; // amount to resize stack by
    double shrink; // amount to shrink stack by
    


    // top = number of items in the stack + 1
    // size = array size

    // size = 100
    // (top + 1) / size

public:
    /**
  * ArrayStack
  * 
  * Description:
  *      Constructor no params
  * 
  * Params:
  *     - None
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack() {
        size = 10;
        A = new int[size]; // ignore for now 
        top = -1;
    }

    /**
  * ArrayStack
  * 
  * Description:
  *      Constructor size param
  * 
  * Params:
  *     - int size
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack(int s) {
        size = s;
        A = new int[s];
        top = -1;

    }

    //ArrayStack stack(startResize,resize,startShrink,shrink);  
    ArrayStack(double a, double b, double c, double d) {
        size = 10;
        A = new int[size];
        top = -1;
        startResize = a; 
        resize = b;
        startShrink = c;
        shrink = d;
    }

    /**
  * Public bool: Empty
  * 
  * Description:
  *      Stack empty?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = empty
  */
    bool Empty() {
        return (top <= -1);
    }

    /**
  * Public bool: Full
  * 
  * Description:
  *      Stack full?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = full
  */
 
    bool Full() {
      //if ()
        return (top >= size - 1);
    }

    /**
  * Public int: Peek
  * 
  * Description:
  *      Returns top value without altering the stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
    int Peek() {
        if (!Empty()) {
            return A[top];
        }

        return -99; // some sentinel value
                    // not a good solution
    }

    /**
  * Public int: Pop
  * 
  * Description:
  *      Returns top value and removes it from stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
    int Pop() {
      if (Empty()){
        ContainerShrink();
        amountResized +=1;
        count++;
      }
      if (!Empty()) {
            return A[top--];
            }
        
        return -99; // some sentinel value
                    // not a good solution
    }
    int getSize(){
      return this->size;
    }
    int getamountSize(){
      return this->amountResized;
    }

    /**
  * Public bool: Push
  * 
  * Description:
  *      Adds an item to top of stack. It also makes a call to 
  *      the Resize function if the stack is to small.
  * 
  * Params:
  *      [int] : item to be added
  * 
  * Returns:
  *      [bool] ; success = true
  */
    bool Push(int x){
        if (Full()) {
            Resize();
            amountResized +=1;
            count++;
        }
        if (!Full()) {
            A[++top] = x;

            //checkResize();
            return true;
        }

        return false;
    }

 
    /**
  * Public void: Resize
  * 
  * Description:
  *      Resizes the container for the stack by incrementing
  *      its capacity. It also keeps track of the size of the stack 
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
 
    void Resize() {
        int newSize = size * resize; // grow the stack
        int *B = new int[newSize]; // allocate new memory
   
        // MaxSize(newSize);  
        
        for (int i = 0; i < top; i++) { // copy values to new array
            B[i] = A[i];
        }

        delete[] A; // delete old array

        size = newSize; // save new size

        A = B; // reset array pointer
        if (TotalStackSize < newSize){
          TotalStackSize = newSize;
        }
    }
    /**
  * Public void: ContainerShrink
  * 
  * Description:
  *      Resizes the container for the stack by decrementing
  *      its capacity. 
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void ContainerShrink(){
      if(size <= 10){
        return;
      }
      int newSize = size * shrink; // shrink the stack 
      int *B = new int[newSize]; // allocate new memory
      

        for (int i = 0; i < top; i++) { // copy values to new array
            B[i] = A[i];
        }

        delete[] A; // delete old array

        size = newSize; // save new size
    }
     /**
  * Public void: Ouput
  * 
  * Description:
  *      Displays the output of the stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void Ouput(int count2){
      cout<< "################################################################ \n";
      cout << "Assignment 4 - Resizing the Stack\n";
      cout << "CMPS 3013\n";
      cout << "Azizz Mills\n";
      cout << "Config Params:\n";
      cout << "  Full Threshold: "<< startResize <<endl;
      cout << "  Shrink Threshold: "<< startShrink <<endl;
      cout << "  Grow Ratio: "<< resize <<endl;
      cout << "  Shrink Ratio: "<< shrink <<endl;
      cout << "\n\n";
      cout << "Processed " << count2 <<" commands"<<endl;
      cout<<"\n\n";
      cout<<"Max stack size: "<< TotalStackSize << endl;
      cout <<"End Stack size: "<< size << endl;
      cout<<"Stack Resized: "<< getamountSize() <<endl ;
     
      
      cout<< "################################################################ \n";
    }
  
};

// MAIN DRIVER
// Simple Array Based Stack Usage:
int main(int argc, char**argv) {
  ifstream infile;
  string fileName;
  double startResize =.8;
  double resize = 2.0;
  double startShrink = 0.15;
  double shrink = 0.5;
  int maxSize = -1;



  int num;
  int count = 0;

  // NO PARAMS!!!
  if(argc == 1){
    fileName = "nums.txt";
  // params are coming in
  }else if(argc == 2){
    fileName = argv[1];
  }else{
    fileName = argv[1];
    startResize = stod(argv[2]);
    resize = stod(argv[3]);
    startShrink = stod(argv[4]);
    shrink = stod(argv[5]);
  }

  ArrayStack stack(startResize,resize,startShrink,shrink);  
  
  infile.open(fileName);
  
  while(!infile.eof()){
      infile >> num;
      if(num % 2 == 0){ // checks if the value is even or odd    
        stack.Push(num);
      }else{        
        stack.Pop();
      }
      count++;
      
      maxSize = max(maxSize,stack.getSize()); // call to get the large size the stack can be
  }
 

  stack.Ouput(count);
  // cout<< maxSize;
  //cout << stack.getamountSize();
  return 0;  
};