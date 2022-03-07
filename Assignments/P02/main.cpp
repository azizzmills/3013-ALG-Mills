/*
Author:           Azizz Mills 
Email:            azizzmillz@gmail.com
Title:            Linear Time Lookup
Course:           3013 - 201
Semester:         Spring 2022

Description:
The purpose of this program is to mimick an auto complete word search. This is done by recieving a character input and comparing it with words in a file. It then displays the output of the predicted words through a link list. 

Files:
main.cpp
timer.hpp
termcolor.hpp
dictionary.txt
 */

#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define YELLOW termcolor::yellow

// Intialization of the node structure
struct Node {
  string word;
  Node* next;
  Node(string whatever) {
    word = whatever;
    next  = NULL;
  }
};

class randomWords {
  private:
    Node* head;
    Node* tail;
    int size;
  public:
    randomWords() {
	    head = tail = NULL;
      size = 0;
    }

// adds nodes list 
    void Push (string data) {
      if (tail == NULL) {
        head = tail = new Node (data);
      }
      else if (head == tail) {
        Node* temp = new Node (data);
        tail = temp;
        head->next = tail;
        tail->next = NULL;
        temp = NULL;
        delete temp;
      }
      else {
        Node* temp;
        temp = tail;
        tail = new Node (data);
        temp->next = tail;
        tail->next = NULL;
      }
      size++;
    }
// removes nodes from the list
    string Pop () {
      string remove;                   // value to be remove and returned
      Node* temp = head;            // Needed to relink and reconnect tail
      while (temp->next != tail) {  // finds to node before tail
        temp = temp->next;
      }
      tail = temp;                  // Moves tail back up by 1
      temp = temp->next;            // Moves temp to old tail
      tail->next = NULL;         // Cuts off linking
      temp->next = NULL;         // Cuts off linking
      remove = temp->word;          // Stores data before deletion
      delete temp;                  // Deletes remove node
      size--;
      return remove;
    }
// protoype for function definition
void Locator (vector<string> &matches, string term);  
};


int main() {
    char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to
    int loc;                // location of substring to change its color

    ofstream fout("temp.txt");

    Timer T;   // create a timer
    T.Start(); // start it
    randomWords dict;
    vector<string> matches;
    string data;
    ifstream fin("dictionary.txt");

    while (!fin.eof()) {
      fin >> data;
      dict.Push(data);
    }
    T.End(); // end the current timer    
    
    cout << T.Seconds() << " seconds to read in and print dictionary to list" << endl;
    cout << T.MilliSeconds() << " milli to read in and print dictionary to list" << endl;
    cout << T.NanoSeconds() << " nano to read in and print dictionary to list" << endl;

    cout << "Type keys and watch what happens. Type capital Z to quit." << endl;

    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z') {
        T.Start(); // start it
        // Tests for a backspace and if pressed deletes
        // last letter from "word".
        if ((int)k == 127) {
            if (word.size() > 0) {
                word = word.substr(0, word.size() - 1);
            }
        } else {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k)) {
                cout << "Letters only!" << endl;
                continue;
            }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97) {
                k += 32;
            }
            word += k; // append char to word
        }

        // Find any animals in the array that partially match
        // our substr word

        dict.Locator(matches, word);  

        if ((int)k != 32) { // if k is not a space print it
            T.End();
            cout << termcolor::yellow << word << termcolor::reset << endl << endl;
            cout << matches.size() << " words found in " << T.NanoSeconds() << " nanoseconds" << endl << endl;            
            cout << termcolor::blue;
            // This prints out all found matches
            for (int i = 0; i < matches.size(); i++) {              
                // find the substring in the word
                loc = matches[i].find(word);
                // if its found               
                if (loc != string::npos) {
                    //print one letter at a time turning on red or green
                    // depending on if the matching subtring is being printed
                    for (int j = 0; j < matches[i].size(); j++) {
                        // if we are printing the substring turn it red
                        if (j >= loc && j <= loc + word.size() - 1) {
                            cout << termcolor::blue;
                        } else {
                            cout << termcolor::yellow;
                        }
                        cout << matches[i][j];
                    }
                    cout << termcolor::green;
                }
                cout << " ";
              if(i>9){
                break;
              }
            }
            cout << termcolor::reset << endl
                 << endl;
            }
          cout <<endl;
        }
    
    return 0;
}
//  Locator
//
// Description:
// Loops through the link list and finds the words that matches the characters that are typed in.
//
// Params: 
// vector <matches>
// string term
void randomWords:: Locator (vector<string> &matches, string term){
   matches.clear();
      Node* find = head;
      size_t found;           // size_t is an integer position of
                            // found item. -1 if its not found.

      while (find->next != NULL) { // loop through list
        found = find->word.find(term);    // check for substr match

        if(found == 0) {          // if found >= 0 (its found then)
          matches.push_back(find->word);     // add to matches
        }
        find = find->next; // traverses list
      }  
}
