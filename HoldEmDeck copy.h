/*
 * File: HoldEmDeck.h
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the declarations related to the HoldEm deck and its class
 */

#pragma once

#include <iostream>
#include <vector>
#include "Deck_T.h"
#include "Card_T.h"
#include "Suit.h"

enum class HoldEmRank {
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace,
    undefined
};

std::ostream& operator<<(std::ostream&, const HoldEmRank&);

HoldEmRank& operator++(HoldEmRank&);

class HoldEmDeck : public Deck<HoldEmRank, Suit> {
public:
    HoldEmDeck();
};