/*
 * File: Deck.h
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the definitions of the Deck Class
 */

#include "Deck_T.h"

// Shuffle member function
template <typename Rank, typename Suits>
void Deck<Rank, Suits>::shuffle() {
    std::random_device rd;                        // Random device
    std::mt19937 gen(rd());                       // Seed the generator using the random device

    // Shuffle the cards in the vector
    std::shuffle(this->cards.begin(), this->cards.end(), gen); // Using this-> to access the protected member
}

template <typename Rank, typename Suits>
void Deck<Rank, Suits>::collect(CardSet<Rank, Suits>& set) {
    while (!set.is_empty()) {
        // We don't need a try catch here because we've already checked the set is not empty.
        set >> *this;
    }
}
