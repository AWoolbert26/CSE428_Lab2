/*
 * File: Suit.h
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the definitions related to the suits that cards may have 
 * in Pinochle or in Texas hold 'em poker, and the operators involving those suits.
 */

#include "Suit.h"

// Inserts suit representation on ostream
std::ostream& operator<<(std::ostream& os, const Suit& s) {
    switch (s) {
        case Suit::clubs:
            os << 'C';
            break;
        case Suit::diamonds:
            os << 'D';
            break;
        case Suit::hearts:
            os << 'H';
            break;
        case Suit::spades:
            os << 'S';
            break;
        default:
            os << '?';
    }
    return os;
}

// Increments suit by one
Suit& operator++(Suit& s) {
    switch (s) {
        case Suit::clubs:
            s = Suit::diamonds;
            break;
        case Suit::diamonds:
            s = Suit::hearts;
            break;
        case Suit::hearts:
            s = Suit::spades;
            break;
        default:
            s = Suit::undefined;
    }
    return s;
}