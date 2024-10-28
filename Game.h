/*
 * File: Game.h
 * 
 * Andrew Woolbert - a.s.woolbert@wustl.edu
 * Daniel Tymoshenko d.tymoshenko@wustl.edu
 * Rohan Tatikonda r.s.tatikonda@wustl.edu
 * 
 * This file contains the declarations related to the game class
 */

#pragma once

#include <vector>
#include <string>
#include <iostream>

class Game {
protected:
    std::vector<std::string> player_names;
    bool askUserToQuit();

public:
    // Constructor that takes an integer and an array of C-style strings
    Game(int, const char* []);

    virtual int play() = 0;
    
    virtual ~Game() = default;
};