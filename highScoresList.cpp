/* Name: Quinn Pham
 * Date: 4/16/2018
 * Project 2 - highScoresList.cpp
 * Creates, saves and displays a high score board
 */

#include <iostream>
#include <fstream>

#include "highScoresList.h"

using namespace std;

/* Constructor */
HighScoresList::HighScoresList() {
        load();
}

/* Destructor */
HighScoresList::~HighScoresList() {
        Node *toDelete; 
        while (front != NULL) {
                toDelete = front;
                front = front->next;
                delete toDelete;
        }
}

/* load()
 * reads the HIGH_SCORE_FILE and loads the contents of the file
 * if the file does not exist, do nothing.
 * void function that takes no parameters 
 */
void HighScoresList::load() {
        ifstream inFile;
        inFile.open(HIGH_SCORE_FILE);
        if (not inFile) {
                return;
        }
        string user;
        int score;
        
        while (inFile >> user) {
                if (user == SENTINEL) {
                        break;
                }
                else {
                        inFile >> score;
                        Entry entry = {user, score};
                        add_to_back(entry);
                }
        }

        inFile.close();
}
 
/* add_to_back()
 * creates a node, adds it to the back of the linked list
 * void fucntion that takes an Entry struct as a parameter
 */
void HighScoresList::add_to_back(Entry entry) {
        Node *last = new Node; // holds the last node
        last->entry = entry;
        last->next = NULL; // does not point to any other node
        
        if (front == NULL) {
                front = last;
        }
        else {
                Node *temp = front;
                while (temp->next != NULL) {
                        temp = temp->next;
                }
                temp->next = last;
        }
}

/* save()
 * writes the names and scores to the HIGH_SCORE_FILE, followed by the 
 * sentinel.
 * this will overwrite what was originally in HIGH_SCORE_FILE.
 * void function that takes no parameters
 */
void HighScoresList::save() {
        ofstream outFile;
        outFile.open(HIGH_SCORE_FILE);
    
        Node *temp = front;

        while (temp != NULL) {
                outFile << temp->entry.user << ' ' 
                     << temp->entry.score << endl;
                temp = temp->next;
        }
        
        outFile << SENTINEL << endl;
        outFile.close();
}   

/* print()
 * prints out all elements in the linked list
 * void function that takes no parameters
 */
void HighScoresList::print() {
        Node *temp = front;
    
        while (temp != NULL) {
                cout << temp->entry.user << ' '
                     << temp->entry.score << endl;
                temp = temp->next;
        }
}

/* printTop5()
 * prints out the top five entries in the linked list
 * if fewer than 5 entries, prints as many as there are
 * void function that takes no parameters
 */
void HighScoresList::printTop5() {
        Node *temp = front;
        int count = 0;

        while (count < 5 and temp != NULL) {
                cout << temp->entry.user << ' '
                     << temp->entry.score << endl;
                temp = temp->next;
                count++;
        }
}

/* highestScore()
 * finds the highest score in the linked list  
 * if no entries, returns 0
 * takes in no parameters and returns a score
 */
int HighScoresList::highestScore() {
      Node *temp = front;
      int max = 0;

      while (temp != NULL) {
              if (temp->entry.score >= max) {
                      max = temp->entry.score;
              }
              temp = temp->next;   
      }

      return max;
}

/* keepTop10()
 * deletes all but the top 10 entries in the linked list
 * if fewer than 10, keep all
 * void function that takes no parameters
 */
void HighScoresList::keepTop10() {
        Node *newFront = front;
        Node *last = NULL;
        Node *toDelete = NULL;
        int count = 0;

        if (newFront == NULL) {
        } // does nothing

        else {
                while (count < 10 and newFront->next != NULL) {
                        last = newFront;
                        newFront = newFront->next;
                        count++;
                }
                
                last->next = NULL;
                
                while (newFront != NULL) { 
                        toDelete = newFront;
                        newFront = newFront->next;
                        delete toDelete;
                }
        }
}

/* insert()
 * inserts a Node into the linked list
 * void function that takes a string and a score as parameters
 */
void HighScoresList::insert(string user, int score) {
        Node *newEntry = new Node;
        newEntry->entry = {user, score};
        newEntry->next = NULL;
        
        if (front == NULL) { // if there are no elements at all
                front = newEntry;
        }

        else if (newEntry->entry.score >= front->entry.score) {
                newEntry->next = front;
                front = newEntry; // reset front of linked list
        }
        else {
                Node *before = front;
                Node *temp = front;
                
                while (temp != NULL and 
                       newEntry->entry.score < temp->entry.score) {
                        before = temp; 
                        temp = temp->next;
                }
                
                newEntry->next = temp;
                before->next = newEntry;
        }
}

/* clear()
 * clears all entries
 * void function that takes no parameters
 */     
void HighScoresList::clear() {
        Node *toDelete; 
        while (front != NULL) {
                toDelete = front;
                front = front->next;
                delete toDelete;
        }
}

/* printUser()
 * prints all the scores for a user
 * void function that takes a string for a parameter
 */
void HighScoresList::printUser(string user) {
        Node *temp = front;
        
        while (temp != NULL) {
                if (temp->entry.user == user) {
                        cout << temp->entry.score << endl;
                }
                temp = temp->next;
        }
}

/* deleteUser()
 * deletes all scores for a user
 * void function that takes a string for a parameter
 */
void HighScoresList::deleteUser(string user) {
        Node *toDelete = NULL;
        
        if (in_file(user) == false) {
        } // does nothing

        else {
                if (front->entry.user == user) {
                        toDelete = front; 
                        front = front->next; // reset front of linked list
                        delete toDelete;
                }
                Node *before = front;
                Node *temp = front->next;
                while (temp != NULL) {
                        if (temp->entry.user == user) {
                                toDelete = temp; 
                                temp = temp->next;
                                before->next = temp;
                                before = before->next;
                                delete toDelete;
                        }
                        before = temp;
                        temp = temp->next;
                }
        }
}

/* in_file()
 * checks to see if the user name is in the linked list
 * bool function that takes a string user name as a parameter
 */
bool HighScoresList::in_file(string user) {
        Node *temp = front;

        while (temp != NULL) {
                if (temp->entry.user == user) {
                        return true;
                }
        }
        return false;
}

        
