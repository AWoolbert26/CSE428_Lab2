Lab 2
Daniel Tymoshenko d.tymoshenko@wustl.edu
Rohan Tatikonda r.s.tatikonda@wustl.edu
Andrew Woolbert a.s.woolbert@wustl.edu

Development Process:

    Steps 1-6:
     - These went smoothly. Didn't run into any issues while setting up the lab.

    Step 7:
     - Accidentally called the two functions the same thing which lead to an error when making. Fixed this quite easily.

    Step 8:
     - We decided to use the default copy constructor which the compiler provides rather than declare and define my own. The one that the compiler supplies is sufficient
       because cards is a std::vector of Card elements and std::vector handles deep copying of its own elements. Thus using the compiler copy constructor is valid and 
       less complex.

    Step 9:
     - Fairly simple implementation. We didn't quite get the syntax to return a pointer the first time around so we ran into an error when making the project.

    Step 10:
     - Implemented the PinochleMelds type in the header file and implemented a meld points array which w declared in the header file and defined in the cpp file. we used
       the fact that enum class labels start at 0 to index them appropriately with the point values.

    Step 11:
     - Used the pinochleMelds enumerated type and the meld points array to print out the meld to the console.

    Step 12:
     - This function was a little more tricky than the previous steps. We implemented the suitIndependentEvaluation member function by implementing a aceSuitCount, kingSuitCount, queenSuitCount and
       jackSuitCount dictionary, running through the cards in the hand. And then checking if the required cards were in the hand in order to make each meld. We started with the less likely ones i.e.
       thousand aces over hundred aces in order to simplify some logic. We luckily didn't run into any compilation errors during this step.

    Step 13:
     - In the play member function of the PinochleGame class we printed out each players hand and then whether or not they had made any melds and what those meld point values were. We didn't run 
       into any compilation errors during this step.

    Step 14:
     - Created a HoldEmHandRank enum type and a left shift operator as requested. We didn't run into any compilation errors during this step.

    Step 15:
     - The holdemHandEvaluation member function was one of the most difficult sections to implement. We ran a number of trails in order to solidify our logic for each situation that can occur
       in a game of Texas HoldEm poker. But in the end were able to create a working handEvaluation function which returns the correct rank.

    Step 16:
     - Using a number of helper functions we created a < operator which is able to determine whether the first hand is less than the second hand. We made these helper functions protected in order
       to prevent these methods being used outside of a HoldEmGame object. We ran into a couple of compilation errors while developing but were thankfully able to creat this function.

    Step 17:
     - Managed to implement handRank assignment and sorting without a compilation error!

    Steps 18-20:
     - We gradually made each part as we coded it so we did not run into any errors or warnings when making it for the final time!
     - Tests are documented below.
     - Added names and emails of all contributers at the top of this file.


Testing:

-Testing for different command line arguments:
    Note that I'm using IDE which displays the exit code differently that the usual terminal would do.
    1) No arguments: executing ./lab2 gives us:
        Usage: ./lab2 <GameType> <PlayerNames...>
        GameType: Pinochle <Player1> <Player2> <Player3> <Player4>
            or HoldEm <Player1> <Player2> [<Player3> ... <Player9>] 
            (Exit code 7)
        
        That's a proper usage message describing two games implemented and number of players we need to specify for each of them. 

    2) Only one argument specifying wrong type of game: ./lab2 Poker
        Unknown game type: Poker
        Usage: ./lab2 <game_name> <PlayerNames...> 
        (Exit code 10)

        Proper usage message telling that there's no such game.

    3) Wrong game name and some players specified: ./lab2 Poker Bob Alica
        Unknown game type: Poker
        Usage: ./lab2 <game_name> <PlayerNames...>
        (Exit code 10)

        The exit code is also 10 meaning wrong game type argument.

    4) Pinochle game, no players: ./lab2 Pinochle
        Wrong number of players, Pinochle requires exactly four players.
        Usage: ./lab2 Pinochle <Player1> <Player2> <Player3> <Player4>
        (Exit code 8)

        The error code is different this time and the mesage displays that the problem is in the number of players.

    5) Pinochle game, not enough players: ./lab2 Pinochle 1 2 3
        Wrong number of players, Pinochle requires exactly four players.
        Usage: ./lab2 Pinochle <Player1> <Player2> <Player3> <Player4>
        (Exit code 8)

        Again the error is the same as in 4) which is correct.

    6) Pinochle game, too many players: ./lab2 Pinochle 1 2 3 4 5
        Wrong number of players, Pinochle requires exactly four players.
        Usage: ./lab2 Pinochle <Player1> <Player2> <Player3> <Player4>
        (Exit code 8)

        Again the error is the same as in 4) which is correct.
    
    7) Pinochle game, correct number of players: ./lab2 Pinochle 1 2 3 4
        1's hand:
        KC 9S QC 9D 9H KC 10C KS 10C AC 9C KD 

        2's hand:
        AD AD QS 9D JD JH JC AC 9S 10S JS JC 
        fortyjacks 40
        pinochle 40

        3's hand:
        10H KH QS 9C QC KS QD QH AS 10S 9H AS 
        sixtyqueens 60

        4's hand:
        JH JD QD AH QH 10D KD AH KH 10D JS 10H 


        Do you want to end the game? (yes or no): 

        The game started successfully which is a correct behavior. 

    8) Pinochle game, correct number of players but two of gthem have the same name: ./lab2 Pinochle 1 1 3 4
        1's hand:
        QD 9H QH 10C AC QC AH 9S QC KH KC JD 

        1's hand:
        KH QS QS 10D 10S 9H 9C 10H AS 10D 10C KD 

        3's hand:
        9C JH 10H QD KD JS AC KS 9D JD JC JS 
        fortyjacks 40

        4's hand:
        AS 10S JH KS 9S KC AH QH AD JC 9D AD 

        BUG! The game cannot doesn't really make sense when some players have absolutely the same names.
        I added an additional check for that into both Pinochle and HoldEm games.
        Implementation strategy: usually to check if an array has two equal elements we would sort it or use set/map, but here since the number of players is at most 9 a regular nested for range loop will be really fast and will avoid unnecessary library #includes
        Also we implement this check on the initialization stages for both games instead of implementing it for the whole Game class, because, in theory, some games might allow having players with the same name (for example a game might have 2 players but they play in some specific order which is specified in this way).

        Let's test again: ./lab2 Pinochle 1 1 3 4
        In Pinochle, players can't have the same names.
        All player names should be unique.

        (Exit code 13)

        Now the output is correct.

    9) Since we added additional check for players let's see again if the game start correctly if all names are unique: ./lab2 Pinochle 1 2 3 4
        1's hand:
        QC KD QH JD 9D 10C JS JC KH 10D 10H 10C 

        2's hand:
        9C 9S QS 9D AH 10H QC 9H AC JC AH QD 

        3's hand:
        9H JS AC 9S JH KC KD KH 9C AS AS 10S 

        4's hand:
        JD 10D KS KC JH QH AD KS QS QD AD 10S 
        pinochle 40


        Do you want to end the game? (yes or no): 

        The game started correctly.

    10) HoldEm game, no players provided: ./lab2 HoldEm
        Wrong number of players, HoldEm requires from 2 to 9 players.
        Usage: ./lab2 HoldEm <Player1> <Player2> [<Player3> ... <Player9>]
        (Exit code 9)

        The message is correct and the exit code is different from when Pinochle game didn't have the right amount of players. 
        This is a correct behavior because HoldEm is a separate game which has different exectuion rules, so it should have a unique command line error code.

    11) HoldEm game, not enought players provided: ./lab2 HoldEm Bob
        Wrong number of players, HoldEm requires from 2 to 9 players.
        Usage: ./lab2 HoldEm <Player1> <Player2> [<Player3> ... <Player9>]
        (Exit code 9)

        We got the same error which is correct.

    12) HoldEm game, too many players provided: ./lab2 HoldEm Bob1 Bob2 Bob3 Bob4 Bob5 Bob6 Bob7 Bob8 Bob9 Alex
        Wrong number of players, HoldEm requires from 2 to 9 players.
        Usage: ./lab2 HoldEm <Player1> <Player2> [<Player3> ... <Player9>]
        (Exit code 9)

        Again that's a correct behavior since we provided a wrong number of players.

    13) HoldEm game, nine players provided, which is correct: ./lab2 HoldEm Bob1 Bob2 Bob3 Bob4 Bob5 Bob6 Bob7 Bob8 Bob9
        Bob1's hand:
        QS 5H 
        Bob2's hand:
        AS 8C 
        Bob3's hand:
        4H 9H 
        Bob4's hand:
        6S KH 
        Bob5's hand:
        2C 10S 
        Bob6's hand:
        10C AC 
        Bob7's hand:
        JH 5C 
        Bob8's hand:
        AH 6C 
        Bob9's hand:
        KD 8D 
        BOARD (flop): 
        10D 2H JC 
        Bob5 2C 10S JC 2H 10D 
        twopair
        Bob7 JH 5C JC 2H 10D 
        pair
        Bob6 10C AC JC 2H 10D 
        pair
        Bob2 AS 8C JC 2H 10D 
        xhigh
        Bob8 AH 6C JC 2H 10D 
        xhigh
        Bob9 KD 8D JC 2H 10D 
        xhigh
        Bob4 6S KH JC 2H 10D 
        xhigh
        Bob1 QS 5H JC 2H 10D 
        xhigh
        Bob3 4H 9H JC 2H 10D 
        xhigh
        BOARD (turn): 
        10D 2H JC 7H 
        BOARD (river): 
        10D 2H JC 7H 3S 

        Do you want to end the game? (yes or no):

        The game started successfully which is totally right! This passes cases 2 and 3 in step 19 of the lab. the correct combination of cards is produced for each player with everyone having
        the three cards from the common board in addition to their own two unique card and the list of ranked hands being displayed correctly. They are printed from highest ranked to lowest with
        two pair winning, the pairs beneath, and then the high cards listed below those. Even thi high cards are listed in correct order!

    14) HoldEm game, only two players provided, which is also correct: ./lab2 HoldEm Bob1 Bob2
        Bob1's hand:
        JC 9S 
        Bob2's hand:
        2H QD 
        BOARD (flop): 
        5D AC 8H 
        Bob2 2H QD 8H AC 5D 
        xhigh
        Bob1 JC 9S 8H AC 5D 
        xhigh
        BOARD (turn): 
        5D AC 8H QS 
        BOARD (river): 
        5D AC 8H QS JH 

        Do you want to end the game? (yes or no): 

        Again the game started successfully, which is right.

    15) HoldEm game, a correct number of players is provided but they two of them are have the same name: ./lab2 HoldEm Bob 1 2 Bob
        In HoldEm, players can't have the same names.
        All player names should be unique.

        (Exit code 13)

        The error is treated correctly.