/* Name: Quinn Pham
 * Date: 4/16/2018
 * Project 2 - highScoresList.h
 * Creates, saves and displays a high score board
 */

#ifndef HIGHSCORESLIST_H
#define HIGHSCORESLIST_H

#include <string>

class HighScoresList {
    public:
        HighScoresList();
        ~HighScoresList();
        void save(); 
        int highestScore(); 
        void print(); 
        void printTop5(); 
        void keepTop10(); 
        void insert(std::string user, int score); 
        void clear();
        void printUser(std::string user);
        void deleteUser(std::string user);   

    private:
        const std::string SENTINEL = "-1";
        const std::string HIGH_SCORE_FILE = "highScores.txt";

        struct Entry {
                std::string user;
                int score;
        };

        struct Node {
                Entry entry;
                Node *next;
        };
        Node *front = NULL;
        
        void load();
        void add_to_back(Entry entry); // helper for load()
        bool in_file(std::string user); // helper for deleteUser()
};

#endif
