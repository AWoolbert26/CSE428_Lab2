/*
 * File: PinochleDeck.h
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the declarations related to the pinochle deck and its class
 */

#pragma once

#include <iostream>
#include <vector>
#include "Deck_T.h"
#include "Card_T.h"
#include "Suit.h"

enum class PinochleRank {
    nine,
    jack,
    queen,
    king,
    ten,
    ace,
    undefined
};

std::ostream& operator<<(std::ostream&, const PinochleRank&);

PinochleRank& operator++(PinochleRank&);

class PinochleDeck : public Deck<PinochleRank, Suit> {
public:
    PinochleDeck();
};