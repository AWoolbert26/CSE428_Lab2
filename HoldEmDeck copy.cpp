/*
 * File: HoldEmDeck.cpp
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the defintion related to the HoldEm deck and its class
 */

#include "HoldEmDeck.h"

// Inserts HoldEm rank representation on ostream
std::ostream& operator<<(std::ostream& os, const HoldEmRank& rank) {
    switch (rank) {
        case HoldEmRank::two:
            os << '2';
            break;
        case HoldEmRank::three:
            os << '3';
            break;
        case HoldEmRank::four:
            os << '4';
            break;
        case HoldEmRank::five:
            os << '5';
            break;
        case HoldEmRank::six:
            os << '6';
            break;
        case HoldEmRank::seven:
            os << '7';
            break;
        case HoldEmRank::eight:
            os << '8';
            break;
        case HoldEmRank::nine:
            os << '9';
            break;
        case HoldEmRank::ten:
            os << "10";
            break;
        case HoldEmRank::jack:
            os << 'J';
            break;
        case HoldEmRank::queen:
            os << 'Q';
            break;
        case HoldEmRank::king:
            os << 'K';
            break;
        case HoldEmRank::ace:
            os << 'A';
            break;
        default:
            os << '?';
    }
    return os;
}

// Increments HoldEm rank
HoldEmRank& operator++(HoldEmRank& rank) {
    switch (rank) {
        case HoldEmRank::two:
            rank = HoldEmRank::three;
            break;
        case HoldEmRank::three:
            rank = HoldEmRank::four;
            break;
        case HoldEmRank::four:
            rank = HoldEmRank::five;
            break;
        case HoldEmRank::five:
            rank = HoldEmRank::six;
            break;
        case HoldEmRank::six:
            rank = HoldEmRank::seven;
            break;
        case HoldEmRank::seven:
            rank = HoldEmRank::eight;
            break;
        case HoldEmRank::eight:
            rank = HoldEmRank::nine;
            break;
        case HoldEmRank::nine:
            rank = HoldEmRank::ten;
            break;
        case HoldEmRank::ten:
            rank = HoldEmRank::jack;
            break;
        case HoldEmRank::jack:
            rank = HoldEmRank::queen;
            break;
        case HoldEmRank::queen:
            rank = HoldEmRank::king;
            break;
        case HoldEmRank::king:
            rank = HoldEmRank::ace;
            break;
        default:
            rank = HoldEmRank::undefined;
    }
    return rank;
}


HoldEmDeck::HoldEmDeck() {
    for (Suit s = Suit::clubs; s != Suit::undefined; ++s) {
        for (HoldEmRank r = HoldEmRank::two; r != HoldEmRank::undefined; ++r) {
            this->cards.push_back({r, s});
        }
    }
}