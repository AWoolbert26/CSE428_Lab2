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

    int index = static_cast<int>(rank);
    
    os << rankNames[index];
    return os;
}

bool operator<(const HoldEmGame::Player& player1, const HoldEmGame::Player& player2) {
    if (player1.handRank != player2.handRank) {
        return player1.handRank < player2.handRank; 
    }

    switch (player1.handRank) {
        case HoldEmHandRank::pair: {
            auto player1PairRank = getPairRank(player1.hand);
            auto player2PairRank = getPairRank(player2.hand);
            if (player1PairRank != player2PairRank) {
                return player1PairRank < player2PairRank;
            }
         
            auto player1Kickers = getKickers(player1.hand);
            auto player2Kickers = getKickers(player2.hand);
            for (size_t i = 0; i < std::min(player1Kickers.size(), player2Kickers.size()); ++i) {
                if (player1Kickers[i] != player2Kickers[i]) {
                    return player1Kickers[i] < player2Kickers[i];
                }
            }
            return false; 
        }

        case HoldEmHandRank::twopair: {
            auto player1HigherPairRank = getHigherPairRank(player1.hand);
            auto player2HigherPairRank = getHigherPairRank(player2.hand);
            if (player1HigherPairRank != player2HigherPairRank) {
                return player1HigherPairRank < player2HigherPairRank;
            }
            auto player1LowerPairRank = getLowerPairRank(player1.hand);
            auto player2LowerPairRank = getLowerPairRank(player2.hand);
            if (player1LowerPairRank != player2LowerPairRank) {
                return player1LowerPairRank < player2LowerPairRank;
            }
            auto player1Kicker = getKickers(player1.hand)[0];
            auto player2Kicker = getKickers(player2.hand)[0];
            return player1Kicker < player2Kicker;
        }

        case HoldEmHandRank::threeofakind: {
            auto player1ThreeRank = getThreeOfAKindRank(player1.hand);
            auto player2ThreeRank = getThreeOfAKindRank(player2.hand);
            return player1ThreeRank < player2ThreeRank;
        }

        case HoldEmHandRank::straight: {
            auto player1HighestCard = getHighestCard(player1.hand);
            auto player2HighestCard = getHighestCard(player2.hand);
            return player1HighestCard < player2HighestCard;
        }

        case HoldEmHandRank::flush:
        case HoldEmHandRank::xhigh: {
            auto player1Ranks = getSortedRanks(player1.hand);
            auto player2Ranks = getSortedRanks(player2.hand);
            for (size_t i = 0; i < std::min(player1Ranks.size(), player2Ranks.size()); ++i) {
                if (player1Ranks[i] != player2Ranks[i]) {
                    return player1Ranks[i] < player2Ranks[i];
                }
            }
            return false; 
        }

        case HoldEmHandRank::fullhouse: {
            auto player1ThreeRank = getThreeOfAKindRank(player1.hand);
            auto player2ThreeRank = getThreeOfAKindRank(player2.hand);
            return player1ThreeRank < player2ThreeRank;
        }

        case HoldEmHandRank::fourofakind: {
            auto player1FourRank = getFourOfAKindRank(player1.hand);
            auto player2FourRank = getFourOfAKindRank(player2.hand);
            return player1FourRank < player2FourRank;
        }

        case HoldEmHandRank::straightflush: {
            auto player1HighestCard = getHighestCard(player1.hand);
            auto player2HighestCard = getHighestCard(player2.hand);
            return player1HighestCard < player2HighestCard;
        }

        default:
            return false; 
    }
}

// Implementation of helper functions

HoldEmRank getPairRank(const CardSet<HoldEmRank, Suit>& hand) {
    std::unordered_map<HoldEmRank, int> rankCount;

    CardSet<HoldEmRank, Suit> localHand = hand;

    std::vector<Card<HoldEmRank, Suit>>& cards = *(localHand.getCards(localHand));

    for (const auto& card : cards) {
        rankCount[card.rank]++;
    }
    for (const auto& [rank, count] : rankCount) {
        if (count == 2) {
            return rank; 
        }
    }

    return HoldEmRank::undefined; 
}

std::vector<HoldEmRank> getKickers(const CardSet<HoldEmRank, Suit>& hand) {
    std::unordered_map<HoldEmRank, int> rankCount;

    CardSet<HoldEmRank, Suit> localHand = hand;

    std::vector<Card<HoldEmRank, Suit>>& cards = *(localHand.getCards(localHand));

    for (const auto& card : cards) {
        rankCount[card.rank]++;
    }

    std::vector<HoldEmRank> kickers;

    for (const auto& [rank, count] : rankCount) {
        if (count == 1) {
            kickers.push_back(rank);
        }
    }

    std::sort(kickers.rbegin(), kickers.rend());

    return kickers;
}

HoldEmRank getHigherPairRank(const CardSet<HoldEmRank, Suit>& hand) {
    std::unordered_map<HoldEmRank, int> rankCount;
    CardSet<HoldEmRank, Suit> localHand = hand;
    std::vector<Card<HoldEmRank, Suit>>& cards = *(localHand.getCards(localHand));

    for (const auto& card : cards) {
        rankCount[card.rank]++;
    }

    HoldEmRank higherPairRank = HoldEmRank::undefined;

    for (const auto& [rank, count] : rankCount) {
        if (count >= 2) {
            if (higherPairRank == HoldEmRank::undefined || rank > higherPairRank) {
                higherPairRank = rank;
            }
        }
    }

    return higherPairRank;
}

HoldEmRank getLowerPairRank(const CardSet<HoldEmRank, Suit>& hand) {
    std::unordered_map<HoldEmRank, int> rankCount;
    CardSet<HoldEmRank, Suit> localHand = hand;
    std::vector<Card<HoldEmRank, Suit>>& cards = *(localHand.getCards(localHand));

    for (const auto& card : cards) {
        rankCount[card.rank]++;
    }

    HoldEmRank lowerPairRank = HoldEmRank::undefined;

    for (const auto& [rank, count] : rankCount) {
        if (count >= 2) {
            if (lowerPairRank == HoldEmRank::undefined || rank < lowerPairRank) {
                lowerPairRank = rank;
            }
        }
    }

    return lowerPairRank;
}

HoldEmRank getFourOfAKindRank(const CardSet<HoldEmRank, Suit>& hand) {
    std::unordered_map<HoldEmRank, int> rankCount;
    CardSet<HoldEmRank, Suit> localHand = hand;
    std::vector<Card<HoldEmRank, Suit>>& cards = *(localHand.getCards(localHand));

    for (const auto& card : cards) {
        rankCount[card.rank]++;
    }

    for (const auto& [rank, count] : rankCount) {
        if (count == 4) {
            return rank;
        }
    }

    return HoldEmRank::undefined;
}

HoldEmRank getThreeOfAKindRank(const CardSet<HoldEmRank, Suit>& hand) {
    std::unordered_map<HoldEmRank, int> rankCount;
    CardSet<HoldEmRank, Suit> localHand = hand;
    std::vector<Card<HoldEmRank, Suit>>& cards = *(localHand.getCards(localHand));

    for (const auto& card : cards) {
        rankCount[card.rank]++;
    }

    for (const auto& [rank, count] : rankCount) {
        if (count == 3) {
            return rank;
        }
    }

    return HoldEmRank::undefined;
}

HoldEmRank getHighestCard(const CardSet<HoldEmRank, Suit>& hand) {
    CardSet<HoldEmRank, Suit> localHand = hand;
    std::vector<Card<HoldEmRank, Suit>>& cards = *(localHand.getCards(localHand));

    HoldEmRank highestRank = HoldEmRank::undefined;

    for (const auto& card : cards) {
        if (card.rank > highestRank) {
            highestRank = card.rank;
        }
    }

    return highestRank;
}

std::vector<HoldEmRank> getSortedRanks(const CardSet<HoldEmRank, Suit>& hand) {
    CardSet<HoldEmRank, Suit> localHand = hand;
    std::vector<Card<HoldEmRank, Suit>>& cards = *(localHand.getCards(localHand));

    std::vector<HoldEmRank> ranks;

    for (const auto& card : cards) {
        ranks.push_back(card.rank);
    }

    std::sort(ranks.begin(), ranks.end(), std::greater<HoldEmRank>());
    
    return ranks;
}