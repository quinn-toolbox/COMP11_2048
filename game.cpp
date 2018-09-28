/* Name: Quinn Pham
 * Date: 4/16/2018
 * Project 2 - game.cpp
 * The entire gamplay
 */

#include <iostream>

#include "game.h"
#include "int-string.h"
#include "highScoresList.h"

using namespace std;

#define RANDOMSEED time(NULL)

int Game::DIMEN; // intializing static const DIMEN 

/* Constructor */
Game::Game() {
}

/* Destructor */
Game::~Game() {
        delete[] game.board;
}

/* play()
 * main function, allocates movements and actions through functions
 * void function that takes no parameters
 */
void Game::play() {
        srand(RANDOMSEED);
        dimen_input();
        populate_board();
        
        while (game.lose == false) {
                cin >> input;
                if (validate_input() == "movement") {
                        allocate_movement();
                        new_num();
                        print_board();
                        if (do_i_lose()) {
                                game_over();
                        }
                }
                else if (validate_input() == "action") {
                        action();
                }
        }
}

/* print_number()
 * prints in the correct format
 * void function that takes a string as a parameter
 */
void Game::print_number(string num) {
        printf("%-6s", num.c_str());
}

/* dimen_input()
 * takes in a dimension, if it is valid, initializes board
 * void function that takes no parameters
 */
void Game::dimen_input() {
        cout << "Enter desired dimension of board: ";
        cin >> DIMEN;
        if (DIMEN >= 2) {
                game.board = new string*[DIMEN];
                for (int i = 0; i < DIMEN; i++) {
                        game.board[i] = new string[DIMEN];
                } 
        }
        else {
                cerr << "Dimension not valid." << endl;
                exit(1);
        }
}

/* validate__input()
 * checks if the input is correct or if the user wants to end game
 * takes in no parameters and returns a string to identify the movement
 */
string Game::validate_input() {
        if (input == LEFT or input == RIGHT or input == UP or 
            input == DOWN) {
                return "movement";
        }
        if (input == QUIT or input == FIVE or input == CLEAR or 
            input == SHOW or input == KEEP or input == DEL) {
                return "action";
        }
        else {
                cerr << "Command not recognized. Please try again."
                     << endl;
                return "";
        }
}

/* action()
 * checks input and calls the correct function
 * void function that takes no parameters
 */
void Game::action() {
        if (input == FIVE) {
                list.printTop5();
        }
        else if (input == QUIT) {
                game_over();
        }
        else if (input == CLEAR) {
                list.clear();
        }
        else if (input == SHOW) {
                string name;
                cin >> name;
                list.printUser(name);
        }
        else if (input == KEEP) {
                list.keepTop10();
        }
        else if (input == DEL) {
                string name;
                cin >> name;
                list.deleteUser(name);
        }                
}

/* populate_board()
 * initialize the board with empty characters and two "2"
 * void function that takes no parameters
 */
void Game::populate_board() {
        int high = list.highestScore();
        cout << "Starting game! High score is " << high << endl;
        for (int i = 0; i < DIMEN; i++) {
                for (int j = 0; j < DIMEN; j++) {
                        game.board[i][j] = EMPTY;
                }
        }
        
        int i = rand() % DIMEN;
        int j = rand() % DIMEN;
        game.board[i][j] = "2";
        
        do {
                i = rand() % DIMEN;
                j = rand() % DIMEN;
        } while (game.board[i][j] != EMPTY); // eliminate overlap
        game.board[i][j] = "2";

        print_board();
}

/* new_num()
 * adds a new 2 or 4 to a random empty space on the board
 * void function that takes no parameters
 */
void Game::new_num() {
        int i, j;
        do {
                i = rand() % DIMEN;
                j = rand() % DIMEN;
        } while (game.board[i][j] != EMPTY);

        if (rand() % 100 <= PROB_2 * 100) {
                game.board[i][j] = "2";
        }
        else {
                game.board[i][j] = "4";
        }       
}

/* print_board()
 * prints out the board with the current score
 * void function that takes no parameters
 */
void Game::print_board() {
        cout << "Current score: " << game.score << endl;
        for (int i = 0; i < DIMEN; i++) {
                for (int j = 0; j < DIMEN; j++) {
                        print_number(game.board[i][j]);
                }
                cout << endl;
        }
        cout << endl;
}

/* allocate_movement() {
 * chooses the right movement for each input
 * void function that takes no parameters
 */
void Game::allocate_movement() {
        if (input == LEFT) {
                left();
        }
        if (input == RIGHT) {
                right();
        }
        if (input == UP) {
                up();
        }
        if (input == DOWN) {
                down();
        }
}

/* left()
 * completes a move to the left, including movement and adding
 * void function that takes no parameters
 */
void Game::left() {
        for (int k = 0; k < DIMEN; k++) {
                for (int i = 0; i < DIMEN; i++) {
                        for (int j = i + 1; j < DIMEN; j++) {
                                if (game.board[k][i] == EMPTY) {
                                        move_left_right(k, i, j);
                                }
                        }
                }
        }
        for (int k = 0; k < DIMEN; k++) {
                for (int i = 0, j = i + 1; i < DIMEN; i++, j++) {
                        add_left_right(k, i, j);
                }
        }
        for (int k = 0; k < DIMEN; k++) {
                for (int i = 0; i < DIMEN; i++) {
                        for (int j = i + 1; j < DIMEN; j++) {
                                if (game.board[k][i] == EMPTY) {
                                        move_left_right(k, i, j);
                                }
                        }
                }
        }
}

/* right()
 * completes a move to the right, including movement and adding
 * void function that takes no parameters
 */
void Game::right() {
        for (int k = 0; k < DIMEN; k++) {
                for (int i = DIMEN - 1; i >= 0; i--) {
                        for (int j = i - 1; j >= 0; j--) {
                                if (game.board[k][i] == EMPTY) {
                                        move_left_right(k, i, j);
                                }
                        }
                }
        }
        for (int k = 0; k < DIMEN; k++) {
                for (int i = DIMEN - 1, j = i - 1; i >= 0; i--, j--) {
                        add_left_right(k, i, j);
                }
        }
        for (int k = 0; k < DIMEN; k++) {
                for (int i = DIMEN - 1; i >= 0; i--) {
                        for (int j = i - 1; j >= 0; j--) {
                                if (game.board[k][i] == EMPTY) {
                                        move_left_right(k, i, j);
                                }
                        }
                }
        }
}

/* up()
 * completes a move upwards, including movement and adding
 * void function that takes no parameters
 */
void Game::up() {
        for (int k = 0; k < DIMEN; k++) {
                for (int i = 0; i < DIMEN; i++) {
                        for (int j = i + 1; j < DIMEN; j++) {
                                if (game.board[i][k] == EMPTY) {
                                        move_up_down(k, i, j);
                                }
                        }
                }
        }
        for (int k = 0; k < DIMEN; k++) {
                for (int i = 0, j = i + 1; i < DIMEN; i++, j++) {
                        add_up_down(k, i, j);
                }
        }
        for (int k = 0; k < DIMEN; k++) {
                for (int i = 0; i < DIMEN; i++) {
                        for (int j = i + 1; j < DIMEN; j++) {
                                if (game.board[i][k] == EMPTY) {
                                        move_up_down(k, i, j);
                                }
                        }
                }
        }
}

/* down()
 * completes a move downwards, including movement and adding
 * void function that takes no parameters
 */
void Game::down() {
        for (int k = 0; k < DIMEN; k++) {
                for (int i = DIMEN - 1; i >= 0; i--) {
                        for (int j = i - 1; j >= 0; j--) {
                                if (game.board[i][k] == EMPTY) {
                                        move_up_down(k, i, j);
                                }
                        }
                }
        }
        for (int k = 0; k < DIMEN; k++) {
                for (int i = DIMEN - 1, j = i - 1; i >= 0; i--, j--) {
                        add_up_down(k, i, j);
                }
        }
        for (int k = 0; k < DIMEN; k++) {
                for (int i = DIMEN - 1; i >= 0; i--) {
                        for (int j = i - 1; j >= 0; j--) {
                                if (game.board[i][k] == EMPTY) {
                                        move_up_down(k, i, j);
                                }
                        }
                }
        }
}

/* move_left_right()
 * moves board left/ right to fill in empty tiles
 * void function that takes 3 integers: row, column, adjacent column
 */
void Game::move_left_right(int k, int i, int j) {
        if (game.board[k][j] != EMPTY) {
                game.board[k][i] = game.board[k][j];
                game.board[k][j] = EMPTY;
        }
}

/* move_up_down()
 * moves board up/ down to fill in empty tiles
 * void function that takes 3 integers: row, column, adjacent row
 */
void Game::move_up_down(int k, int i, int j) {
        if (game.board[j][k] != EMPTY) {
                game.board[i][k] = game.board[j][k];
                game.board[j][k] = EMPTY;
        }
}

/* add_left_right()
 * adds tiles with the same number during movement left/right
 * void function that takes 3 integers: row, column, adjacent column
 */
void Game::add_left_right(int k, int i, int j) {
        if (game.board[k][i] != EMPTY and in_board(j)) {
                if (game.board[k][i] == game.board[k][j]) {
                        int n = string2int(game.board[k][j]) * 2;
                        string m = int2string(n);
                        game.board[k][i] = m;
                        game.board[k][j] = EMPTY;
                        game.score = game.score + n; // update score
                }
        }
}

/* add_up_down()
 * adds tiles with the same number during movement up/ down
 * void function that takes 3 integers: row, column, adjacent row
 */
void Game::add_up_down(int k, int i, int j) {
        if (game.board[i][k] != EMPTY and in_board(j)) {
                if (game.board[i][k] == game.board[j][k]) {
                        int n = string2int(game.board[j][k]) * 2;
                        string m = int2string(n);
                        game.board[i][k] = m;
                        game.board[j][k] = EMPTY;
                        game.score = game.score + n; // update score
                }
        }
}

/* in_board()
 * checks that operations don't go out of boundaries
 * void function that takes an integer (row/ column)
 */
bool Game::in_board(int j) {
        if (j >= 0 and j < DIMEN) {
                return true;
        }
        return false;
}

/* do_i_lose()
 * check to see if the player loses
 * bool function that takes no parameters
 */
bool Game::do_i_lose() {
        for (int i = 0; i < DIMEN; i++) {
                for (int j = 0; j < DIMEN; j++) {
                        if (game.board[i][j] == EMPTY) {
                                return false;
                        }
                }
        }
        for (int i = 0; i < DIMEN; i++) {
                for (int j = 0; j < DIMEN; j++) {
                        if (in_board(i + 1) and 
                            game.board[i][j] == game.board[i + 1][j]) {
                                cerr << "loop 1" << endl;
                                return false;
                        }
                        if (in_board(j + 1) and
                            game.board[i][j] == game.board[i][j + 1]) {
                                cerr << "loop 2" << endl;
                                return false;
                        }
                }
        }
        cerr << "LOSE" << endl;
        return true;
}

/* print_game_over()
 * prints a game over message
 * void function that takes no parameters
 */
void Game::game_over() {
        cout << "Game over! Enter your name to record your score." 
             << endl;
        string name;
        cin >> name;
        list.insert(name, game.score);
        list.printTop5();
        list.save();
        game.lose = true;
}
