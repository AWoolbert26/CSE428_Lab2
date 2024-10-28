/*
 * File: HoldEmGame.cpp
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the definitions of the HoldEmGame class.
 */

#include "HoldEmGame.h"
#include "Game.h"
#include "Constants.h"
#include <algorithm>

// Initialize the state to preflop and pass parameters to the game base class
HoldEmGame::HoldEmGame(int argc, const char* argv[]): Game(argc, argv), game_state(HoldEmState::preflop), deck(), board_cards() {
    // Push hands into the player hands vector.
    for (size_t i = 0; i < player_names.size(); ++i) {
        player_hands.emplace_back();
    }
}

// Deal cards to each player and manage the game state
void HoldEmGame::deal() {
    switch (game_state) {
        case HoldEmState::preflop:
            // Deal two cards to each player
            for (size_t player_index = 0; player_index < player_hands.size(); ++player_index) {
                for (int i = 0; i < HOLD_EM_HAND_SIZE; ++i) {
                    deck >> player_hands[player_index];
                }
            }
            game_state = HoldEmState::flop;  
            break;

        case HoldEmState::flop:
            // Deal three cards to the board
            for (size_t i = 0; i < 3; ++i) {
                deck >> board_cards;
            }
            game_state = HoldEmState::turn;  
            break;

        case HoldEmState::turn:
            // Deal one card to the board
            deck >> board_cards;
            game_state = HoldEmState::river;  
            break;

        case HoldEmState::river:
            // Deal one card to the board
            deck >> board_cards;
            game_state = HoldEmState::undefined;  
            break;

        case HoldEmState::undefined:
            break;

        default:
            std::cerr << "Error: Invalid game state." << std::endl;
            break;
    }
}

void HoldEmGame::printBoard() {
    board_cards.print(std::cout, HOLD_EM_BOARD_HAND_SIZE);  
}

void HoldEmGame::printPlayerHands() {
    for (size_t i = 0; i < player_names.size(); ++i) {
        std::cout << player_names[i] << "'s hand:\n";
        player_hands[i].print(std::cout, HOLD_EM_HAND_SIZE); 
    }
}

// Collect cards: Move all cards back from the players' hands and board into the deck
void HoldEmGame::collectCards() {
    for (size_t i = 0; i < player_hands.size(); ++i) {
        deck.collect(player_hands[i]); 
    }
    deck.collect(board_cards); 
}

HoldEmHandRank HoldEmGame::holdEmHandEvaluation(const CardSet<HoldEmRank, Suit>& hand) {

    CardSet<HoldEmRank, Suit> localHand = hand;

    std::vector<Card<HoldEmRank, Suit>>& cards = *(localHand.getCards(localHand));

    // Check if the hand has exactly five cards
    if (cards.size() != 5) {
        return HoldEmHandRank::undefined;
    }

    std::sort(cards.begin(), cards.end(), [](const Card<HoldEmRank, Suit>& a, const Card<HoldEmRank, Suit>& b) {
        return compareByRankThenSuit(a, b);
    });

    // Check for Flush
    bool isFlush = std::all_of(cards.begin(), cards.end(), [&](const Card<HoldEmRank, Suit>& card) {
        return card.suit == cards[0].suit; 
    });

    // Check for Straight
    bool isStraight = true;
    for (size_t i = 0; i < 4; ++i) {
        if (static_cast<int>(cards[i + 1].rank) != static_cast<int>(cards[i].rank) + 1) {
            isStraight = false;
            break;
        }
    }

    // Special case for A, 2, 3, 4, 5
    if (
        !isStraight && cards[0].rank == HoldEmRank::two && cards[1].rank == HoldEmRank::three &&
        cards[2].rank == HoldEmRank::four && cards[3].rank == HoldEmRank::five &&
        cards[4].rank == HoldEmRank::ace) {
        isStraight = true;
    }

    // Check for four of a kind, full house, three of a kind, two pair, and pair
    std::unordered_map<HoldEmRank, int> rankCount;
    for (const auto& card : cards) {
        rankCount[card.rank]++;
    }

    bool hasFourOfAKind = false;
    bool hasThreeOfAKind = false;
    bool hasPair = false;
    int pairCount = 0;

    for (const auto& [rank, count] : rankCount) {
        if (count == 4) {
            hasFourOfAKind = true;
        } else if (count == 3) {
            hasThreeOfAKind = true;
        } else if (count == 2) {
            hasPair = true;
            pairCount++;
        }
    }

    // Determine hand rank
    if (isFlush && isStraight) {
        return HoldEmHandRank::straightflush;
    } else if (hasFourOfAKind) {
        return HoldEmHandRank::fourofakind;
    } else if (hasThreeOfAKind && pairCount == 1) {
        return HoldEmHandRank::fullhouse;
    } else if (isFlush) {
        return HoldEmHandRank::flush;
    } else if (isStraight) {
        return HoldEmHandRank::straight;
    } else if (hasThreeOfAKind) {
        return HoldEmHandRank::threeofakind;
    } else if (pairCount == 2) {
        return HoldEmHandRank::twopair;
    } else if (hasPair) {
        return HoldEmHandRank::pair;
    } else {
        return HoldEmHandRank::xhigh;
    }
}

int HoldEmGame::play() {
    std::string user_input;

    do {
        deck.shuffle();
        game_state = HoldEmState::preflop;

        deal();

        printPlayerHands();

        deal();

        std::cout << "BOARD (flop): \n";
        printBoard();

        deal();

        std::cout << "BOARD (turn): \n";
        printBoard();

        deal();

        std::cout << "BOARD (river): \n";
        printBoard();

        collectCards();
    } while (!askUserToQuit());

    return SUCCESS;
}

// Overloaded operator<< for printing HoldEmHandRanks
std::ostream& operator<<(std::ostream& os, const HoldEmHandRank& rank) {
    // Array of string names corresponding to each PinochleMelds value
    static const std::array<std::string, 15> rankNames = {
        "xhigh", 
        "pair", 
        "twopair", 
        "threeofakind", 
        "straight", 
        "flush", 
        "fullhouse", 
        "fourofakind", 
        "straightflush", 
        "undefined"
    };

    // Convert meld to an integer index
    int index = static_cast<int>(rank);
    
    // Print the name and point value associated with the meld
    os << rankNames[index];
    return os;
}