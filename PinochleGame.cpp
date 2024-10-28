/*
 * File: PinochleGame.cpp
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the implementation of the PinochleGame class.
 */

#include "PinochleGame.h"
#include "Constants.h"
#include <array>

// PinochleGame constructor: Initializes player hands based on number of players
PinochleGame::PinochleGame(int argc, const char* argv[]): Game(argc, argv), deck() {
    // Push back a hand (CardSet) for each player in the game
    for (size_t i = 0; i < player_names.size(); ++i) {
        player_hands.push_back(CardSet<PinochleRank, Suit>());
    }
}

// Deal function: Distribute three cards to each player in sequence
void PinochleGame::deal() {
    size_t player_index = 0;
    while (!deck.is_empty()) {
        for (size_t i = 0; i < 3 && !deck.is_empty(); ++i) {
            deck >> player_hands[player_index];  // Right shift operator transfers cards
        }
        player_index = (player_index + 1) % player_hands.size();  // Move to the next player
    }
}

// Print function: Print the name and hand of each player
void PinochleGame::printPlayerHands() {
    for (size_t i = 0; i < player_names.size(); ++i) {
        std::cout << player_names[i] << "'s hand:\n";
        player_hands[i].print(std::cout, PINOCHLE_HAND_SIZE);  // Print player's hand
    }
}

// Collect cards: Move all cards back from the players' hands into the deck
void PinochleGame::collectCards() {
    for (size_t i = 0; i < player_hands.size(); ++i) {
        deck.collect(player_hands[i]);
    }
}

// Play function: Modularized
int PinochleGame::play() {
    do {
        deck.shuffle();
        deal();
        printPlayerHands();
        collectCards();

    } while (!askUserToQuit());

    return SUCCESS_END_OF_GAME;  
}

std::array<unsigned int, 15> PinochleGame::meldPoints = {
    10,   // dix
    20,   // offsuitmarriage
    40,   // fortyjacks
    40,   // pinochle
    40,   // insuitmarriage
    60,   // sixtyqueens
    80,   // eightykings
    100,  // hundredaces
    150,  // insuitrun
    300,  // doublepinochle
    400,  // fourhundredjacks
    600,  // sixhundredqueens
    800,  // eighthundredkings
    1000, // thousandaces
    1500  // insuitdoublerun
};