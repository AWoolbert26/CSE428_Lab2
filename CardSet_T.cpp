/*
 * File: CardSet_T.cpp
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the implementation of the abstract template CardSet class
 */

#include "CardSet_T.h"

template <typename Rank, typename Suits>

void CardSet<Rank, Suits>::print(std::ostream& os, size_t cardsPerLine) const {
    size_t count = 0; 
    for (const auto& c : cards) {
        os << c << ' '; 
        ++count;
        if (count % cardsPerLine == 0) {
            os << '\n';  
        }
    }

    // Final newline if the last line wasn't complete
    if (count % cardsPerLine != 0 || is_empty()) {
        os << '\n';
    }
}

// Checks if the CardSet is empty
template <typename Rank, typename Suits>
bool CardSet<Rank, Suits>::is_empty() const {
    return cards.empty(); 
}

// Right shift operator
template <typename Rank, typename Suits>
CardSet<Rank, Suits>& CardSet<Rank, Suits>::operator>>(CardSet<Rank, Suits>& other) {
    if (is_empty()) {
        throw std::runtime_error("The current CardSet is empty.");
    }    

    Card<Rank, Suits> cardToMove = cards.back();
    other.cards.push_back(cardToMove);
    cards.pop_back();

    return *this;
}

// Return a pointer to the cards member variable of a CardSet object
template <typename Rank, typename Suits>
std::vector<Card<Rank, Suits> >* CardSet<Rank, Suits>::getCards(CardSet<Rank, Suits>& cardSet) {
    return &cardSet.cards;
}