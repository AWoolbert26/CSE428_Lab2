/*
 * File: HoldEmGame.cpp
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the definitions of the HoldEmGame class.
 */

#include "HoldEmGame.h"
#include "Game.h"
#include "Constants.h"

// Initialize the state to preflop and pass parameters to the game base class
HoldEmGame::HoldEmGame(int argc, char* argv[]): Game(argc, argv), game_state(HoldEmState::preflop), deck(), board_cards() {
    // Push hands into the player hands vector.
    for (size_t i = 0; i < player_names.size(); ++i) {
        player_hands.emplace_back();
    }
}

// Deal cards to each player and manage the game state
void HoldEmGame::deal() {
    switch (game_state) {
        case HoldEmState::preflop:
            // Deal two cards to each player
            for (size_t player_index = 0; player_index < player_hands.size(); ++player_index) {
                for (int i = 0; i < HOLD_EM_HAND_SIZE; ++i) {
                    deck >> player_hands[player_index];
                }
            }
            game_state = HoldEmState::flop;  
            break;

        case HoldEmState::flop:
            // Deal three cards to the board
            for (size_t i = 0; i < 3; ++i) {
                deck >> board_cards;
            }
            game_state = HoldEmState::turn;  
            break;

        case HoldEmState::turn:
            // Deal one card to the board
            deck >> board_cards;
            game_state = HoldEmState::river;  
            break;

        case HoldEmState::river:
            // Deal one card to the board
            deck >> board_cards;
            game_state = HoldEmState::undefined;  
            break;

        case HoldEmState::undefined:
            break;

        default:
            std::cerr << "Error: Invalid game state." << std::endl;
            break;
    }
}

void HoldEmGame::printBoard() {
    board_cards.print(std::cout, HOLD_EM_BOARD_HAND_SIZE);  
}

void HoldEmGame::printPlayerHands() {
    for (size_t i = 0; i < player_names.size(); ++i) {
        std::cout << player_names[i] << "'s hand:\n";
        player_hands[i].print(std::cout, HOLD_EM_HAND_SIZE); 
    }
}

// Collect cards: Move all cards back from the players' hands and board into the deck
void HoldEmGame::collectCards() {
    for (size_t i = 0; i < player_hands.size(); ++i) {
        deck.collect(player_hands[i]); 
    }
    deck.collect(board_cards); 
}

int HoldEmGame::play() {
    std::string user_input;

    do {
        deck.shuffle();
        game_state = HoldEmState::preflop;

        deal();

        printPlayerHands();

        deal();

        std::cout << "BOARD (flop): \n";
        printBoard();

        deal();

        std::cout << "BOARD (turn): \n";
        printBoard();

        deal();

        std::cout << "BOARD (river): \n";
        printBoard();

        collectCards();
    } while (!askUserToQuit());

    return SUCCESS;
}