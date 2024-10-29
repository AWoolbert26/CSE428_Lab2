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

