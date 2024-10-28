/*
 * File: Suit.h
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the declarations related to the suits that cards may have 
 * in Pinochle or in Texas hold 'em poker, and the operators involving those suits.
 */

#pragma once

#include <iostream>

enum class Suit {
    clubs,
    diamonds,
    hearts,
    spades,
    undefined
};

std::ostream& operator<<(std::ostream&, const Suit&);

Suit& operator++(Suit&);