/* Name: Quinn Pham
 * Date: 4/16/2018
 * Project 2 - game.h
 * Creates and implements a 2048 game
 */

#ifndef GAME_H
#define GAME_H

#include <string>
#include "int-string.h"
#include "highScoresList.h" 

class Game {
    public:
        Game();
        ~Game();
        void play();

    private:
        static int DIMEN; 
        const std::string EMPTY = "-";
        const std::string LEFT = "a";
        const std::string RIGHT = "d";
        const std::string UP = "w";
        const std::string DOWN = "s";
        const std::string QUIT = "q";
        const std::string FIVE = "h";
        const std::string CLEAR = "clear";
        const std::string SHOW = "show";
        const std::string KEEP = "keep";
        const std::string DEL = "del";
  
        const double PROB_2 = 0.9; // probability of getting 2
        std::string input;

        struct Gameplay {
                std::string **board;
                int score = 0;
                bool lose = false;
        };
        Gameplay game;
        
        HighScoresList list;

        void print_number(std::string num);
        void dimen_input();
        std::string validate_input();
        void action();
        void populate_board();
        void new_num();
        void print_board();
        void allocate_movement();
        void left();
        void right();
        void up();
        void down();
        void move_left_right(int k, int i, int j);
        void move_up_down(int k, int i, int j);
        void add_left_right(int k, int i, int j);
        void add_up_down(int k, int i, int j);
        bool in_board(int j);
        bool do_i_lose();
        void game_over();
};

#endif
