/*
 * File: lab1.cpp
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the main function.
 */

#include <iostream>
#include <memory>
#include "HoldEmDeck.h"
#include "PinochleDeck.h"
#include "Suit.h"
#include "PinochleGame.h" 
#include "HoldEmGame.h"  
#include "Game.h"   

std::shared_ptr<Game> create(int argc, const char *argv[]) {
    // Error checking is done before hand so we don't have to do it in the create method.
    std::shared_ptr<Game> game_ptr;

    std::string game_name = argv[GAME_NAME]; 
    if (game_name == "Pinochle") {
        game_ptr = std::make_shared<PinochleGame>(argc, argv);
    } else if (game_name == "HoldEm") {
        game_ptr = std::make_shared<HoldEmGame>(argc, argv);
    } 

    return game_ptr;
}

int main(int argc, const char* argv[]) {
    if (argc < REQUIRED_ARGS) {
        std::cerr << "Usage: " << argv[EXECUTABLE] << " <GameType> <PlayerNames...>\n";
        std::cerr << "GameType: Pinochle <Player1> <Player2> <Player3> <Player4>\n";
        std::cerr << "         or HoldEm <Player1> <Player2> [<Player3> ... <Player9>]\n";
        return USAGE_WRONG_NUM_ARGS_ERROR; 
    }

    std::string game_name = argv[GAME_NAME];
    std::shared_ptr<Game> game_ptr;

    if (game_name == "Pinochle") {
        if (argc != PINOCHLE_INPUT_VARS) { 
            std::cerr << "Usage: " << argv[EXECUTABLE] << " Pinochle <Player1> <Player2> <Player3> <Player4>\n";
            return USAGE_PINOCHLE_ERROR; 
        }
        game_ptr = create(argc, argv);
    } else if (game_name == "HoldEm") {
        if (argc < HOLDEM_MIN_INPUT_VARS || argc > HOLDEM_MAX_INPUT_VARS) { 
            std::cerr << "Usage: " << argv[EXECUTABLE] << " HoldEm <Player1> <Player2> [<Player3> ... <Player9>]\n";
            return USAGE_HOLDEM_ERROR; 
        }
        game_ptr = create(argc, argv);
    } else {
        std::cerr << "Unknown game type: " << game_name << "\n";
        std::cerr << "Usage: " << argv[EXECUTABLE] << " <game_name> <PlayerNames...>\n";
        return USAGE_UKNOWN_GAME_ERROR;
    }

    if (game_ptr) {
        return game_ptr->play(); 
    } else {
        std::cerr << "Error: Failed to create the game.\n";
        return GAME_CREATION_ERROR; 
    }
    return SUCCESS;
}