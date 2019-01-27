# TIC TAC TOE V1

Second Version of a Small Game Implementing a smart (AI) Computer Opponent Using the C++ Programming Language. Update--Implemented Minimax Algorithm

Improvements from V0:

//Design structure is more fluid: Implemented a constructor to set default gamestate, enums to enclose player markers, and used structs for (1) the size of the the board and (2) to create an AI move object. Also the board was of the enum "Marker" type which made it easier
then dealing with the char type. Board was a private member function accessible to the Game class and was no longer passed function to function. 

//Computer now uses minimax alogrithm to decide on the best possible move by playing out every gamestate using recursion 

//Computer moves in order to maximize score

//The game play was removed from main.cpp and placed into its own function 

//checkWin loops were reduced based on winning states 

Goal for future Versions:

//May try to implement pruning strategy to eliminate having to go through every possible gamestate whihc will save on resources

//May try to implement an inheritance hierarchy and sperate board, player and game into seperate classes

//May try to deploy android app

//All in all satisfied with this implementation
