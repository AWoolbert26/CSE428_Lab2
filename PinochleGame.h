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
#include <array>
#include "Game.h"
#include "PinochleDeck.h"
#include "CardSet_T.h"
#include "Suit.h"
#include "Constants.h"

enum class PinochleMelds {
    dix, 
    offsuitmarriage, 
    fortyjacks, 
    pinochle, 
    insuitmarriage, 
    sixtyqueens, 
    eightykings, 
    hundredaces, 
    insuitrun, 
    doublepinochle, 
    fourhundredjacks, 
    sixhundredqueens, 
    eighthundredkings, 
    thousandaces, 
    insuitdoublerun
};

class PinochleGame: public Game {
private:
    PinochleDeck deck;
    std::vector<CardSet<PinochleRank, Suit> > player_hands;

    virtual void deal();
    void suitIndependentEvaluation(const CardSet<PinochleRank, Suit>&, std::vector<PinochleMelds>&);

    // Modular functions
    void printPlayerHands();
    void collectCards();
public:
    PinochleGame(int, const char* []);
    virtual int play();
    virtual ~PinochleGame() = default;

    static std::array<unsigned int, NUM_OF_PINOCHLE_MELDS> meldPoints;
};

std::ostream& operator<<(std::ostream&, const PinochleMelds&);