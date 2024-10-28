/*
 * File: CardSet.h
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the declaration of the abstract template CardSet class
 */

#pragma once

#include <iostream>
#include "Card_T.h"

template <typename Rank, typename Suits>
class CardSet {
protected:
    // Protected vector of cards (parameterized by Rank and Suit)
    std::vector<Card<Rank, Suits> > cards;
public:
    void print(std::ostream&, size_t) const;
    bool is_empty() const; 
    CardSet<Rank, Suits>& operator>>(CardSet<Rank, Suits>& other); 
    virtual ~CardSet() = default;
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "CardSet_T.cpp"
#endif