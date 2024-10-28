Lab 1
Daniel Tymoshenko d.tymoshenko@wustl.edu
Rohan Tatikonda r.s.tatikonda@wustl.edu
Andrew Woolbert a.s.woolbert@wustl.edu

Development Process:

    Steps 1-6:
     - These went smoothly. Didn't run into any issues while setting up the lab.

    Step 7:
     - Switched Deck from an abstract class to a template parameterized by rank and suit types which is derived from the CardSet class template.
       Ran into several issues while coding + compiling. Ran into redefinition errors because I did not include the header guards for the .cpp file
       for the deck template. Also ran into errors because we forgot to switch the template source files to the TMPL_SRCS variable in the makefile.
    
    Step 8:
     - Didn't run into any errors while creating the shuffle method for the deck class.

    Step 9:
     - Decided to throw a runtime error if the shift operator is called on an empty set.

    Step 10:
     - Ran into an error. Forgot that I needed to insert into the object itself rather than the cards variable.

    Step 11:
     - Decided to pass argc and argv and just start iterating at the third object within argv. We though this would overall lead to more consistency.

    Step 12:
     - Attempted to modularize the code as much as possible. We abstracted the askUseToQuit function to the Game class in order to not have to 
       redefine it in every single game class that we create in the future. Since printing player hands and card collection should be dependent
       on the type of game we decided to leave these methods in the PinochleGame and HoldEmGame classes.

    Step 13:
     - Again implemented the features for the play method in a mdular manner. Broke them out into seperate member functions. Used the methods in the game class relating to user interaction.

    Step 14:
     - The create function should only be called with valid inputs. However, in case it is called with an invalid input it will return an error.

    Step 15:
     - Updated the main function to reflect the two different types of games which can be played, Pinochle and HoldEm. The usage statements originally were output to cerr but we decided
       to print them to the standard output stream and then return a non-success integer all of which are defined in constants in the returnTypes enum.

    Step 16:
     - We got a couple of warnings. Notably "destructor called on non-final 'PinochleGame' that has virtual functions but non-virtual destructor [-Wdelete-non-abstract-non-virtual-dtor]". 
       Adding default virtual destructors to Game.h PinochleGame.h and HoldEmGame.h solved this issue.

Design Choices:
  -We used camelCase style to name our variables and functions, and PascalCase for calss names. The only exception from this rule were template classes for which we put _T at the end of the name to highlight that they are template.
  -We decided to make CardSet::print() a const method since it shouldn't change anything in the internal class. This decision allowed us to later iterate over decks using const reference, which is a good practice. 
  -For functions working with argc, argv we just work on the whole array of all command line arguments. In our code we iterate starting from the third element since that's where players name start.
  -The width of the lines in cards list output is saved as a constexp WIDTH_OF_OUTPUT, this allows to adjust the output format easily.

Return Values:

Testing:
  -The first thing we noticed when running the program is that it outputs cards separating them with comma, while in the assignment we were asked to use spaces. So we quickly fixed the print() function for that.
  -Testing for different command line arguments:
    1) No arguments: running, ./lab1:
      Usage: ./lab1 <GameType> <PlayerNames...>
        GameType: Pinochle <Player1> <Player2> <Player3> <Player4>
          or HoldEm <Player1> <Player2> [<Player3> ... <Player9>]
      This is a correct output.
    
    2) Only one argument being the name of the Pinochle game, ./lab1 Pinochle:
        Usage: ./lab1 Pinochle <Player1> <Player2> <Player3> <Player4>
      That's a correct correct.
    
    3) Only one argument being the name of the HoldEm game, ./lab1 HoldEm:
        Usage: ./lab1 HoldEm <Player1> <Player2> [<Player3> ... <Player9>]
      That's a correct correct.
    
    4) Wrong name of the game, ./lab1 Poker:
        Unknown game type: Poker
        Usage: ./lab1 <GameType> <PlayerNames...>
      That's a correct correct.
    
    5) Too few player names for the Pinochle game, ./lab1 Pinochle 1 2 3:
        Usage: ./lab1 Pinochle <Player1> <Player2> <Player3> <Player4>
      That's a correct correct.
    
    6) Too many player names for the Pinochle game, ./lab1 Pinochle 1 2 3 4 5:
        Usage: ./lab1 Pinochle <Player1> <Player2> <Player3> <Player4>
      That's a correct correct.
    
    7) Exactly 4 player names for the Pinochle game, ./lab1 Pinochle 1 2 3 4:
        1's hand:
        KC AC 10D KD JC 9D QH AS KD 9C 9S 10H 
        2's hand:
        KS AD 10S 9H QS QH JH 10S 10C AD 9H 10H 
        3's hand:
        AC QC 10C 9D JD KC KS JD AH QS 9C 9S 
        4's hand:
        JS QC AS JH AH 10D KH QD JS KH JC QD 
        Do you want to end the game? (yes or no): 
      
      This is a correct output, we have randomized hands for each player and all the cards are from the Pinochle game.
    
    8) Too few player names for the HoldEm game, ./lab1 HoldEm 1:
        1's hand:
        2S 6S 
        BOARD (flop): Board (community cards):
        4H 9C 4S 
        BOARD (turn): Board (community cards):
        4H 9C 4S QS 
        BOARD (river): Board (community cards):
        4H 9C 4S QS 3S 
      BUG: Here we run into a bug, the HoldEm cannot be played by only one player. The problem was in the if branch in lab1.cpp checking the correct number of arguments for this case.
      We changed statement "argc < 3" to "argc < 4".
      Running the test again we get:
        Usage: ./lab1 HoldEm <Player1> <Player2> [<Player3> ... <Player9>]
      Now this is a correct output.
    
    9) Two player names for HoldEm game, ./lab1 HoldEm 1 2:
        1's hand:
        AC 2S 
        2's hand:
        QD KS 
        BOARD (flop): Board (community cards):
        7D AD JD 
        BOARD (turn): Board (community cards):
        7D AD JD 7H 
        BOARD (river): Board (community cards):
        7D AD JD 7H AH 
      That's a correct output. The player hands are displayed right, the board is also well displayed.

  -Test if on each turn the hands are different
    1) Pinochle game, ./lab1 Pinochle 1 2 3 4:
      1's hand:
      10S AH 10D AD 10C AC AS KD QH 10H QS JH 
      2's hand:
      JC KH JC JH 9D JD AS KC KS 9H AD 10D 
      3's hand:
      10H AH 9S QD 9C 9S JD QC JS KS 9D QS 
      4's hand:
      10S KD KC QC QH QD 9H AC 9C KH JS 10C 

      Do you want to end the game? (yes or no): no
      1's hand:
      AD 9H AC JS KD AS KH AH QS JD KC QH 
      2's hand:
      KS 9C 10S 9S QH AH KS JC 9S QC KH JH 
      3's hand:
      AD 9C QC 10H 10D QD JC AS 9D 9H JS 10C 
      4's hand:
      QD JD AC KD 10C 9D 10S JH KC QS 10D 10H 

      Do you want to end the game? (yes or no): no
      1's hand:
      10D QS 9S AH AD 10C QC 9D QD 9H KD JC 
      2's hand:
      QH 10D JD 9C JS KS 10C AS 9D 10S 10S AD 
      3's hand:
      KS JD 9C AC 10H AC KH 10H QH JH AH JH 
      4's hand:
      KD QC KH JC KC 9S 9H AS QD QS KC JS 

  This is a perfect output. The hands are different at every turn and they do look random.

  2) HoldEm game, ./lab1 HoldEm 1 2 3:
    1's hand:
    AH 9S 
    2's hand:
    3S AS 
    3's hand:
    KD 5H 
    BOARD (flop): Board (community cards):
    10H QD 8H 
    BOARD (turn): Board (community cards):
    10H QD 8H QH 
    BOARD (river): Board (community cards):
    10H QD 8H QH 2H 

    Do you want to end the game? (yes or no): no
    1's hand:
    2S KD 
    2's hand:
    7H 3C 
    3's hand:
    7C 6S 
    BOARD (flop): Board (community cards):
    3D 8H KS 
    BOARD (turn): Board (community cards):
    3D 8H KS 6C 
    BOARD (river): Board (community cards):
    3D 8H KS 6C 7D 

    Do you want to end the game? (yes or no): no
    1's hand:
    6C 8D 
    2's hand:
    QC QD 
    3's hand:
    7D 10S 
    BOARD (flop): Board (community cards):
    AS JD QH 
    BOARD (turn): Board (community cards):
    AS JD QH 6H 
    BOARD (river): Board (community cards):
    AS JD QH 6H 4D 
  
  This is a perfect output. The hands are different at every turn and they do look random, the boards outputs make sense.