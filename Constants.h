/*
 * File: Constants.h
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the constants for this program
 */

#pragma once

constexpr int SUCCESS = 0;
constexpr int WRONG_NUM_OF_ARGUMENTS = 1;
constexpr int SUCCESS_END_OF_GAME = 6;
constexpr int USAGE_WRONG_NUM_ARGS_ERROR = 7;
constexpr int USAGE_PINOCHLE_ERROR = 8;
constexpr int USAGE_HOLDEM_ERROR = 9;
constexpr int USAGE_UKNOWN_GAME_ERROR = 10;
constexpr int GAME_CREATION_ERROR = 11;
constexpr int SHIFT_FROM_EMPTY_SET = 12;
constexpr int PLAYERS_HAVE_SAME_NAMES = 13;
constexpr int GAME_PLAY_FAILURE = 14;


constexpr int HOLD_EM_HAND_SIZE = 2;
constexpr int HOLD_EM_BOARD_HAND_SIZE = 5;
constexpr int PINOCHLE_HAND_SIZE = 13;

constexpr int PINOCHLE_INPUT_VARS = 6;
constexpr int HOLDEM_MIN_INPUT_VARS = 4;
constexpr int HOLDEM_MAX_INPUT_VARS = 11;

constexpr int NUM_FLOP_CARDS = 3;
constexpr int HOLD_EM_FULL_HAND_SIZE = 5;
constexpr int ADDITIONAL_CARDS_FOR_VALID_STRAIGHT = 4;
constexpr int FOUR_OF_A_KIND = 4;
constexpr int THREE_OF_A_KIND = 3;
constexpr int PAIR = 2;
constexpr int NUM_OF_HOLD_EM_RANKS = 10;

constexpr int NUM_FOR_PINOCHLE_HIGH_MELD = 2;
constexpr int NUM_FOR_PINOCHLE_LOW_MELD = 1;
constexpr int NUM_OF_PINOCHLE_MELDS = 15;

enum INPUT_VARS {
    EXECUTABLE,
    GAME_NAME,
    PLAYER_NAMES_START
};

enum CARDS {
    FIRST,
    SECOND,
    THIRD,
    FOURTH,
    FIFTH
};

constexpr int REQUIRED_ARGS = 2;