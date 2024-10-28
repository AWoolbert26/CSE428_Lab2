/*
 * File: CardSet_T.h
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
    CardSet() = default;
    CardSet(const CardSet<Rank, Suits>&) = default;
    virtual ~CardSet() = default;

    void print(std::ostream&, size_t) const;
    bool is_empty() const; 

    CardSet<Rank, Suits>& operator>>(CardSet<Rank, Suits>& other); 
    static std::vector<Card<Rank, Suits> >* getCards(CardSet<Rank, Suits>&);
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "CardSet_T.cpp"
#endif