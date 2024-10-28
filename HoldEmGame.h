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

public:

    HoldEmGame(int, const char* []);
    int play() override;
    virtual ~HoldEmGame() = default;
};

std::ostream& operator<<(std::ostream&, const HoldEmHandRank&);