/*
 * File: PinochleGame.h
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the declarations related to the PinochleGame class
 */

#pragma once

#include <vector>
#include "Game.h"
#include "PinochleDeck.h"
#include "CardSet_T.h"
#include "Suit.h"
#include "Constants.h"

class PinochleGame: public Game {
protected:
    PinochleDeck deck;
    std::vector<CardSet<PinochleRank, Suit> > player_hands;

    virtual void deal();

    // Modular functions
    void printPlayerHands();
    void collectCards();
public:
    PinochleGame(int, char* []);
    virtual int play();
    virtual ~PinochleGame() = default;
};