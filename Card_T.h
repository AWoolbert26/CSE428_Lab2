/*
 * File: Card_T.h
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the declaration of the abstract template Card class and its methods
 */

#pragma once

#include <iostream>

template <typename Rank, typename Suits>
struct Card {
    Rank rank;
    Suits suit;

    Card(Rank, Suits);
};

template <typename Rank, typename Suits>
std::ostream& operator<<(std::ostream&, const Card<Rank, Suits>&);

template <typename Rank, typename Suits>
bool compareByRankThenSuit(const Card<Rank, Suits>&, const Card<Rank, Suits>&);

template <typename Rank, typename Suits>
bool compareBySuitThenRank(const Card<Rank, Suits>&, const Card<Rank, Suits>&);


#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Card_T.cpp"
#endif