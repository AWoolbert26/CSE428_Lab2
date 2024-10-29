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
#include "PinochleDeck.h"
#include "Suit.h"
#include "Constants.h"
#include <iostream>
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

// Independent suit evaluation function: 
void PinochleGame::suitIndependentEvaluation(const CardSet<PinochleRank, Suit>& hand, std::vector<PinochleMelds>& melds) {
    CardSet<PinochleRank, Suit> localHand = hand;

    // Track counts of aces, kings, queens, and jacks
    std::unordered_map<Suit, int> aceSuitCount;
    std::unordered_map<Suit, int> kingSuitCount;
    std::unordered_map<Suit, int> queenSuitCount;
    std::unordered_map<Suit, int> jackSuitCount;

    // Count the occurrences of each specific card rank per suit
    for (const auto& card : *(localHand.getCards(localHand))) { // Dereference the pointer here
        if (card.rank == PinochleRank::ace) {
            aceSuitCount[card.suit]++;
        } else if (card.rank == PinochleRank::king) {
            kingSuitCount[card.suit]++;
        } else if (card.rank == PinochleRank::queen) {
            queenSuitCount[card.suit]++;
        } else if (card.rank == PinochleRank::jack) {
            jackSuitCount[card.suit]++;
        }
    }

    // Check for Ace Melds
    if (
        aceSuitCount[Suit::spades] == NUM_FOR_PINOCHLE_HIGH_MELD &&
        aceSuitCount[Suit::hearts] == NUM_FOR_PINOCHLE_HIGH_MELD &&
        aceSuitCount[Suit::diamonds] == NUM_FOR_PINOCHLE_HIGH_MELD &&
        aceSuitCount[Suit::clubs] == NUM_FOR_PINOCHLE_HIGH_MELD
    ) {
        melds.push_back(PinochleMelds::thousandaces);
    } else if  (
        aceSuitCount[Suit::spades] >= NUM_FOR_PINOCHLE_LOW_MELD &&
        aceSuitCount[Suit::hearts] >= NUM_FOR_PINOCHLE_LOW_MELD &&
        aceSuitCount[Suit::diamonds] >= NUM_FOR_PINOCHLE_LOW_MELD &&
        aceSuitCount[Suit::clubs] >= NUM_FOR_PINOCHLE_LOW_MELD
    ) {
        melds.push_back(PinochleMelds::hundredaces);
    }

    // Check for King Melds
    if (
        kingSuitCount[Suit::spades] == NUM_FOR_PINOCHLE_HIGH_MELD &&
        kingSuitCount[Suit::hearts] == NUM_FOR_PINOCHLE_HIGH_MELD &&
        kingSuitCount[Suit::diamonds] == NUM_FOR_PINOCHLE_HIGH_MELD &&
        kingSuitCount[Suit::clubs] == NUM_FOR_PINOCHLE_HIGH_MELD
    ) {
        melds.push_back(PinochleMelds::eighthundredkings);
    } else if (
        kingSuitCount[Suit::spades] >= NUM_FOR_PINOCHLE_LOW_MELD &&
        kingSuitCount[Suit::hearts] >= NUM_FOR_PINOCHLE_LOW_MELD &&
        kingSuitCount[Suit::diamonds] >= NUM_FOR_PINOCHLE_LOW_MELD &&
        kingSuitCount[Suit::clubs] >= NUM_FOR_PINOCHLE_LOW_MELD
    ) {
        melds.push_back(PinochleMelds::eightykings);
    }

    // Check for Queen Melds
    if (
        queenSuitCount[Suit::spades] == NUM_FOR_PINOCHLE_HIGH_MELD &&
        queenSuitCount[Suit::hearts] == NUM_FOR_PINOCHLE_HIGH_MELD &&
        queenSuitCount[Suit::diamonds] == NUM_FOR_PINOCHLE_HIGH_MELD &&
        queenSuitCount[Suit::clubs] == NUM_FOR_PINOCHLE_HIGH_MELD
    ) {
        melds.push_back(PinochleMelds::sixhundredqueens);
    } else if (
        queenSuitCount[Suit::spades] >= NUM_FOR_PINOCHLE_LOW_MELD &&
        queenSuitCount[Suit::hearts] >= NUM_FOR_PINOCHLE_LOW_MELD &&
        queenSuitCount[Suit::diamonds] >= NUM_FOR_PINOCHLE_LOW_MELD &&
        queenSuitCount[Suit::clubs] >= NUM_FOR_PINOCHLE_LOW_MELD
    ) {
        melds.push_back(PinochleMelds::sixtyqueens);
    }

    // Check for Jack Melds
    if (
        jackSuitCount[Suit::spades] == NUM_FOR_PINOCHLE_HIGH_MELD &&
        jackSuitCount[Suit::hearts] == NUM_FOR_PINOCHLE_HIGH_MELD &&
        jackSuitCount[Suit::diamonds] == NUM_FOR_PINOCHLE_HIGH_MELD &&
        jackSuitCount[Suit::clubs] == NUM_FOR_PINOCHLE_HIGH_MELD
    ) {
        melds.push_back(PinochleMelds::fourhundredjacks);
    } else if (
        jackSuitCount[Suit::spades] >= NUM_FOR_PINOCHLE_LOW_MELD &&
        jackSuitCount[Suit::hearts] >= NUM_FOR_PINOCHLE_LOW_MELD &&
        jackSuitCount[Suit::diamonds] >= NUM_FOR_PINOCHLE_LOW_MELD &&
        jackSuitCount[Suit::clubs] >= NUM_FOR_PINOCHLE_LOW_MELD
    ) {
        melds.push_back(PinochleMelds::fortyjacks);
    }

    // Check for Pinochle melds
    if (jackSuitCount[Suit::diamonds] >= NUM_FOR_PINOCHLE_HIGH_MELD && queenSuitCount[Suit::spades] >= NUM_FOR_PINOCHLE_HIGH_MELD) {
        melds.push_back(PinochleMelds::doublepinochle);
    } else if (jackSuitCount[Suit::diamonds] >= NUM_FOR_PINOCHLE_LOW_MELD && queenSuitCount[Suit::spades] >= NUM_FOR_PINOCHLE_LOW_MELD) {
        melds.push_back(PinochleMelds::pinochle);
    }
};

// Print function: Print the name and hand of each player
void PinochleGame::printPlayerHands() {
    for (size_t i = 0; i < player_names.size(); ++i) {
        std::cout << player_names[i] << "'s hand:\n";

        player_hands[i].print(std::cout, PINOCHLE_HAND_SIZE);  // Print player's hand

        std::vector<PinochleMelds> possibleMelds;

        suitIndependentEvaluation(player_hands[i], possibleMelds);

        for (PinochleMelds meld: possibleMelds) {
            std::cout << meld << std::endl;
        }

        std::cout << std::endl;
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

// Point values for varius PinochleMelds
std::array<unsigned int, NUM_OF_PINOCHLE_MELDS> PinochleGame::meldPoints = {
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

// Overloaded operator<< for printing PinochleMelds
std::ostream& operator<<(std::ostream& os, const PinochleMelds& meld) {
    // Array of string names corresponding to each PinochleMelds value
    static const std::array<std::string, 15> meldNames = {
        "dix", "offsuitmarriage", "fortyjacks", "pinochle", "insuitmarriage",
        "sixtyqueens", "eightykings", "hundredaces", "insuitrun", "doublepinochle",
        "fourhundredjacks", "sixhundredqueens", "eighthundredkings", "thousandaces",
        "insuitdoublerun"
    };

    // Convert meld to an integer index
    int index = static_cast<int>(meld);
    
    // Print the name and point value associated with the meld
    os << meldNames[index] << " " << PinochleGame::meldPoints[index];
    return os;
}