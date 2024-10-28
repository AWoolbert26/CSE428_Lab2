/*
 * File: Game.cpp
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the definitions related to the game class
 */

#include "Game.h"
#include "Constants.h"

// In our implementation argv contains all the command line arguments, 
// so the list of names starts from 2
Game::Game(int argc, const char* argv[]) {
    for (int i = PLAYER_NAMES_START; i < argc; ++i) {
        player_names.push_back(argv[i]);
    }
}

// Ask the user if they want to quit the game
bool Game::askUserToQuit() {
    std::cout << "\nDo you want to end the game? (yes or no): ";
    std::string user_input;
    std::getline(std::cin, user_input);
    return user_input == "yes";
}