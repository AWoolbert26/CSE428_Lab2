/*
 * File: Card_T.h
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the implementation of the abstract template Card class and its methods
 */

#include "Card_T.h"

template <typename Rank, typename Suits>

Card<Rank, Suits>::Card(Rank _rank, Suits _suit) : rank(_rank), suit(_suit) {}

template <typename Rank, typename Suits>

std::ostream& operator<<(std::ostream& os, const Card<Rank, Suits>& card) {
    return os << card.rank << card.suit;
}