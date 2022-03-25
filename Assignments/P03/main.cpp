/*
Author:           Azizz Mills 
Email:            azizzmillz@gmail.com
Title:            Processing in Trie Tree Time
Course:           3013 - 201
Semester:         Spring 2022

Description:
The purpose of this program is to mimick an auto complete word search. This is done by recieving a character input and it is located in a trie tree node. The other characters in the word are then found in other trie nodes. For this example each node is filled with letters from A to Z. After a word is linked together in the tree, other words will be added. However the new word will be linked to other by the begining letters of other word the was previously added to the list. 

Files:
main.cpp
timer.hpp
termcolor.hpp
dictionary.txt
mygetch.hpp
 */

#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// Define the character size
#define CHAR_SIZE 26

/*
*  Function name: upperCase
*
*Description:
 *      checks if the word is in upper case
 * Params:
 *      char letter - letter to be checked 
 * Returns:
 *      bool-whether or not letter is upper case 
 */
bool upperCase(char letter) {
    int l = letter;
    return (l >= 65 && l <= 90);
}

/*
* Function name: lowerCase
*
 * Description:
 *      checks if the word is in lower case
 * Params:
 *      char letter - letter to be checked 
 * Returns:
 *      bool - whether or not character is lower
 */
bool lowerCase(char letter) {
    int l = letter;
    return (l >= 97 && l <= 122);
}

/**
*  Function name: Letter
*
 * Description:
 *      checks if value is a letter 
 * Params:
 *      char letter : letter to be checked 
 * Returns:
 *      bool : whether or not char is a letter
 */
bool Letter(char letter) 
{
    int l = letter;
    return upperCase(l) || lowerCase(l);
}

/**
*  Function name : lettersOnly
* 
 * Description:
 *      checks if word only has letters
 * Params:
 *      string word - word to be checked 
 * Returns:
 *      bool - whether or not any other characters were found
 */
bool lettersOnly(string word) 
{
    for (int i = 0; i < word.length(); i++) 
    {
        if (!Letter(word[i])) 
        {
            return false;
        }
    }
    return true;
}

/**
* Function name: makeUpper
*
 * Description:
 *      puts string in all caps
 * Params:
 *      string &word : string reference to be put in all caps
 * Returns:
 *      N/a
 */
void makeUpper(string &word) 
{
    for (int i = 0; i < word.length(); i++) 
    {
        if (lowerCase(word[i])) 
        {
            word[i] -= 32;
        }
    }
}

/** 
* Struct name : TrieNode
*
 * Description:
 *      Node holding the entire alphabet
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
struct TrieNode 
{
    bool Leaf;
    TrieNode *character[CHAR_SIZE];

    TrieNode() 
    {
        this->Leaf = false;

        for (int i = 0; i < CHAR_SIZE; i++) 
        {
            this->character[i] = nullptr;
        }
    }
};

/*
* Class name: Trie
*
 * Description:
 *      Trie tree that holds strings
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
class Trie
{
private:       

TrieNode *root;

/**
* Function name: deletion
*
 * Description:
 *     It is a recursive fucntion that deletes a key. 
 * Params:
 *      TrieNode *& : current node to look down the tree from
 *      String key : substring to be deleted
 * Returns:
 *      bool : whether or not it was deleted
 */
// Recursive function to delete a key in the Trie

        bool deletion(TrieNode*& root, string key)
{          
    // return if Trie is empty
    if (root == nullptr) 
    {
        return false;
    }
 
    // if the end of the key is not reached
    if (key.length())
    {
        // recur for the node corresponding to the next character in the key
        // and if it returns true, delete the current node (if it is non-leaf)
 
        if (root != nullptr &&
            root->character[key[0]] != nullptr &&
            deletion(root->character[key[0]], key.substr(1)) &&
            root->Leaf == false)
        {
            if (!Children(root))
            {
                delete root;
                root = nullptr;
                return true;
            }
            else {
                return false;
            }
        }
    }
 
    // if the end of the key is reached
    if (key.length() == 0 && root->Leaf)
    {
        // if the current node is a leaf node and doesn't have any children
        if (!Children(root))
        {
            // delete the current node
            delete root;
            root = nullptr;
 
            // delete the non-leaf parent nodes
            return true;
        }
 
        // if the current node is a leaf node and has children
        else {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            root->Leaf = false;
 
            // don't delete its parent nodes
            return false;
        }
    }
 
    return false;
}
/**
*Function name: Locator
*
 * Description:
 *      Recursively calls Locator to find all matches 
 * Params:
 *      TrieNode *& : current node to look down the tree from
 * Returns:
 *      N/a
 */        
void Locator(TrieNode *&curr,string key)
  {
    // If the current node is a Leaf, push it onto results
    if(curr->Leaf)
    {
        results.push_back(key);
    }

    // loop through whole alphabet
    for (int i = 0; i < 26; i++) 
    {
        // if the current node's character at position i has a value
        if(curr->character[i])
        {
            // recursive call to the finall function using node 
            //at curr->char[i] and Key+the character found to continue
            Locator(curr->character[i],key+char(i+65));
        }
    }
}


vector<string> results;

    public:
        Trie()
        {
            root = new TrieNode;
        }
    
        void insert(string key){
           // make upper case 
    makeUpper(key);

    // start from the root node
    TrieNode* curr = root;

    // loops through key length
    for (int i = 0; i < key.length(); i++)
    {
        // create a new node if the path doesn't exist
        if (curr->character[key[i] - 65] == nullptr) 
        {
            curr->character[key[i] - 65] = new TrieNode();
        }
 
        // go to the next node
        curr = curr->character[key[i] - 65];
    }
 
    // mark the current node as a leaf
    curr->Leaf = true;
        }

/**
 * Description:
 *      determines if a key is in the Trie
 * Params:
 *      String key : string to be searched for
 * Returns:
 *      bool : whether or not string was found in Trie
 */
        bool search(string key){
            // return false if Trie is empty
    if (this == nullptr) 
    {
        return false;
    }

    // set current to root
    TrieNode* curr = root;

    // loop through string length 
    for (int i = 0; i < key.length(); i++)
    {
        // go to the next node
        curr = curr->character[key[i]];
 
        // if the string is invalid (reached end of a path in the Trie)
        if (curr == nullptr) 
        {
            return false;
        }
    }
 
    // return true if the current node is a leaf and the
    // end of the string is reached
    return curr->Leaf;
        }

/**
*Function name: Children
*
 * Description:
 *      determines if a node has children
 * Params:
 *      TrieNode const* curr : current node that cannot be affected within method
 * Returns:
 *      bool : whether or not a child was found
 */
        bool Children(TrieNode const* curr){
          // loop through defined char size
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (curr->character[i]) {
            return true;    // child found
        }
    }
 
    return false;
          
        }

/**
* Function name: Locator
 * Description:
 *      Calls overloaded Locator function after traversing thorugh original substring
 * Params:
 *     string key : substing used
 * Returns:
 *      vector<string> : all matches found 
 */ 
        vector<string> Locator(string key){       
    makeUpper(key);          // Sets key to capital letter
    TrieNode* curr = root;   // current pointer to root 
    bool isValidKey = false; // checks if key sent is valid
    results.clear();         // clears results so it can be reused

    // Loops through substring length
    for(int i = 0; i < key.length(); i++) 
    {
        // if key is not a letter, end loop immediatly 
        if(!Letter(key[i]))
        {
            isValidKey = false;
            i = key.length();
        }
        // if the current character at key[i] is null, end loop immediatly 
        else if(curr->character[key[i] - 65] == nullptr)
        {
            isValidKey = false;
            i = key.length();
        }
        else
        {
            // Move to next node
            curr = curr->character[key[i] - 65];
            isValidKey = true;
        }
    }

    if(isValidKey)
    {
        // Call to overloaded function
        Locator(curr,key);
    }
  
    // returns results
    return results;
  }
};

/**
 * Description:
 *      Originally wrote this to count size of input file so
 *      I could allocate enough memory for an array of strings
 *      but I went with a vector below. But I'm keeping it and
 *      using it anyway!
 * Params:
 *      string file_name - file to get the line count
 * 
 * Returns:
 *      int - line count
 */
int CountLines(string file_name) 
{
    ifstream inFile(file_name);
    return (std::count(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>(), '\n'));
}

/**
 * Description:
 *      Loads a file of strings (words, names, whatever) reading them in
 *      with one word per line. So words must be delimited by newlines '\n'
 * Params:
 *      string file_name - file to get the line count
 * Returns:
 *      Trie of dictionary words
 */
Trie LoadDict(std::string file_name) 
{
    ifstream fin;                            // file to get animal names
    int count = (CountLines(file_name) + 1); // get size of input file

    Trie dictTrie;                           // create linkedList object

    fin.open(file_name);                     // open file for reading

    std::string readIn;                      // readIn variable

    // knowing the size of the file lets us treat
    // it like an array without using .push_back(value)
    for (int i = 0; i < count; i++) 
    {
        fin >> readIn;                   // Read in words
        dictTrie.insert(readIn);         // insert words into trie
    }

    return dictTrie;
}

int main() 
{
    char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to
    Trie words;             // trie of all words
    vector<string> matches; // any matches found in trie of words

    ofstream fout("temp.txt"); //temporary output file

    Timer T;   // create a timer
    T.Start(); // start it

    words = LoadDict("dictionary.txt"); // Load Trie with dictionary words

    T.End(); // end the current timer

    // print out how long it took to load the animals file
    cout << T.Seconds() << " seconds to read in dictionary" << endl;
    cout << T.MilliSeconds() << " milli seconds to read in dictionary" << endl;

    // Instructions
    cout << "Type capital Z to quit.\n\n" ;
    
    // Starts new timer
    Timer matchTimer;

    // While capital Z is not typed keep looping
    while((k = getch()) != 'Z') 
    {
        // Start new timer
        matchTimer.Start();

        // Tests for a backspace and if pressed deletes
        // last letter from "word".
        if ((int)k == 8) 
        {
            if (word.size() > 0) 
            {
                word = word.substr(0, word.size() - 1);
            }
        } 
        else 
        {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k)) 
            {
                cout << "Letters only!" << endl;
                continue;
            }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97) 
            {
                k += 32;
            }
            word += k; // append char to word
        }

        // Find any animals in the array that partially match
        // our substr word
        matches = words.Locator(word);

        // Ends Timer
        matchTimer.End();
        
        // Prints Blank Lines to give appearace of overwriting
        for (int i = 0; i < 100; i++) 
        {
            std::cout << "\n";
        }

        // Outputs cute
        std::cout << "String submitted: " << termcolor::bright_red << word << termcolor::reset << "\n\n";
        std::cout << termcolor::blue << matches.size() << " words found in " 
            << std::setprecision(2) << matchTimer.Seconds() << " seconds.\n";

        std::cout << termcolor::red;
        std::cout << "Matches Found: ";

        // Calculates Loop Size variable 
        int loopSize;
        matches.size() < 10 ? loopSize = matches.size() : loopSize = 10;

        // This prints out all found matches
        for (int i = 0; i < loopSize; i++) 
        {
            std::cout << matches[i] << " ";
        }
        std::cout << termcolor::reset << endl << endl;
    }             
    return 0;
}