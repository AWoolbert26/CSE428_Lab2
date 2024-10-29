/*
 * File: HoldEmGame.h
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the declaration of the HoldEmGame class.
 */

#pragma once

#include "Game.h"
#include "HoldEmDeck.h"
#include "CardSet_T.h"
#include <iostream>
#include <vector>
#include <string>

// Enum class for representing different stages of a HoldEm
enum class HoldEmState {
    preflop,   
    flop,      
    turn,      
    river,     
    undefined  
};

enum class HoldEmHandRank {
    xhigh, 
    pair, 
    twopair, 
    threeofakind, 
    straight, 
    flush, 
    fullhouse, 
    fourofakind, 
    straightflush, 
    undefined
};

class HoldEmGame : public Game {
private:

    HoldEmState game_state;
    HoldEmDeck deck;
    std::vector<CardSet<HoldEmRank, Suit> > player_hands;
    CardSet<HoldEmRank, Suit> board_cards;

    virtual void deal();
    void printPlayerHands();
    void printBoard();
    void collectCards();

    HoldEmHandRank holdEmHandEvaluation(const CardSet<HoldEmRank, Suit>&);

protected:

    // Helper functions to extract ranks and values
    static HoldEmRank getPairRank(const CardSet<HoldEmRank, Suit>& hand);
    static std::vector<HoldEmRank> getKickers(const CardSet<HoldEmRank, Suit>& hand);
    static HoldEmRank getHigherPairRank(const CardSet<HoldEmRank, Suit>& hand);
    static HoldEmRank getLowerPairRank(const CardSet<HoldEmRank, Suit>& hand);
    static HoldEmRank getThreeOfAKindRank(const CardSet<HoldEmRank, Suit>& hand);
    static HoldEmRank getFourOfAKindRank(const CardSet<HoldEmRank, Suit>& hand);
    static HoldEmRank getHighestCard(const CardSet<HoldEmRank, Suit>& hand);
    static std::vector<HoldEmRank> getSortedRanks(const CardSet<HoldEmRank, Suit>& hand);

public:

    struct Player {
        CardSet<HoldEmRank, Suit> hand; // CardSet containing the player's hand
        std::string name;                // Player's name
        HoldEmHandRank handRank;         // Player's hand rank

        // Constructor for Player struct
        Player(const CardSet<HoldEmRank, Suit>&, const std::string&, HoldEmHandRank);
    };

    friend bool operator<(const HoldEmGame::Player& player1, const HoldEmGame::Player& player2);

    HoldEmGame(int, const char* []);
    virtual int play() override;
    virtual ~HoldEmGame() = default;
};

// Print the Rank to the console
std::ostream& operator<<(std::ostream&, const HoldEmHandRank&);

// Check which player has the higher ranked hand
bool operator<(const HoldEmGame::Player& player1, const HoldEmGame::Player& player2);

