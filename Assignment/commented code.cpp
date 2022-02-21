/*****************************************************************************
*                    
*  Author:           Azizz Mills
*  Email:            azizzmillz@gmail.com
*  Label:            A04
*  Title:            Commenting C++ Code
*  Course:           CMPS 3013
*  Semester:         Spring 2022
* 
*  Description:
*        This program implements a class that allows a linked list to be used just like 
*        an array. It overloads the square brackets to simulate accessing seperate array 
*        elements, but really it traverses the list to find the specified node using an
*        index value. It also overloads the "+" signs allowing a user "push" items onto
*        the end of the list.
*        
*  Usage: 
*       - $ ./main filename
*       
*  Files:            
*       main.cpp    : driver program 
*****************************************************************************/

#include <iostream>

using namespace std;

int A[100];

// definition of the node
struct Node {
    int x;
    Node *next;
    Node() {
        x = -1;
        next = NULL;
    }
    Node(int n) {
        x = n;
        next = NULL;
    }
};

/**
 * List
 * 
 * Description:
 *      It contains the definition of a node and the nessary methods
 *      create and link the list. 
 * 
 * Public Methods:
               List()
        void   Push(int)
        void   Insert(int)
        void   PrintTail()
        void   Print()
        int    Pop()
        int    operator+ 
        int    operator[](int)
        friend ostream &operator<<(ostream, List)

 * Usage: 
 *      -Creation of a node
 *      -Linking multiple nodes together 
 *      -Transversing through the list 
 *      -Accessing specfic indexes
 *      
 */

class List {
private:
    Node *Head;
    Node *Tail;
    int Size;

public:
    List() {
        Head = Tail = NULL;
        Size = 0;
    }
     
    // this one inserts a node in the tail (being used)
    void Push(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail) {
            Head = Tail = Temp;
        } else {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }
/**
     * Public : Insert
     * 
     * Description:
     *      Gives a node an integer value and ties it to another node
     * 
     * Params:
     *      int  :  an integer value
     *     
     * Returns:
     *        It doesn't return anything iys a void function
     */
    // this one inserts from the head (not being used)
    void Insert(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail) {
            Tail = Head;
        }
        Size++;
    }

    void PrintTail() {
        cout << Tail->x << endl;
    }

    string Print() {
        Node *Temp = Head;
        string list;

        while (Temp != NULL) {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    // not implemented
    int Pop() {
        Size--;
        return 0; //
    }

    List operator+(const List &Rhs) {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    // Implementation of [] operator.  This function returns an
    // int value as if the list were an array.
    int operator[](int index) {
        Node *Temp = Head;

        if (index >= Size) {
            cout << "Index out of bounds, exiting";
            exit(0);
        } else {

            for (int i = 0; i < index; i++) {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }
    // the key word 'friend was used so the ostream could access to the private attributes of List
    friend ostream &operator<<(ostream &os, List L) {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv) {
    List L1;
    List L2;

    for (int i = 0; i < 25; i++) {
        L1.Push(i);
    }

    for (int i = 50; i < 100; i++) {
        L2.Push(i);
    }

    //cout << L1 << endl;
    L1.PrintTail();
    L2.PrintTail();

    List L3 = L1 + L2;
    cout << L3 << endl;

    // displays a specfic index in the link list 
    cout << L3[5] << endl;
    return 0;
}
