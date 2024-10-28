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


constexpr int HOLD_EM_HAND_SIZE = 2;
constexpr int HOLD_EM_BOARD_HAND_SIZE = 5;
constexpr int PINOCHLE_HAND_SIZE = 13;

constexpr int PINOCHLE_INPUT_VARS = 6;
constexpr int HOLDEM_MIN_INPUT_VARS = 4;
constexpr int HOLDEM_MAX_INPUT_VARS = 11;

enum INPUT_VARS {
    EXECUTABLE,
    GAME_NAME,
    PLAYER_NAMES_START
};

constexpr int REQUIRED_ARGS = 2;