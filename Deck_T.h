/*
 * File: Deck.h
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the declaration of the Deck Class
 */

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>  // For std::shuffle
#include <random>     // For std::random_device and std::mt19937
#include "CardSet_T.h"

template <typename Rank, typename Suits>
class Deck : public CardSet<Rank, Suits> {
public:
    void shuffle(); // Declaration of shuffle member function
    void collect(CardSet<Rank, Suits>&);
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Deck_T.cpp"
#endif