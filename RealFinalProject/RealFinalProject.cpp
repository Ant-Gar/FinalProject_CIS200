// RealFinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Blackjack.h"

int main(){
    cout << "Welcome to Blackjack!" << endl;
    cout << endl;
    cout << "Here are the simple rules of this Blackjack game:" << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;
    cout << "* The goal is to get as close to 21 as possible without going over." << endl;
    cout << "* You (the Player) will be facing off against the Bot (the Dealer)." << endl;
    cout << "* At first, you will receive two cards, and the dealer will receive one." << endl;
    cout << "* IMPORTANT: An 11 will be considered BOTH an 11 & 1, depending on if you go over 21." << endl;
    cout << "* After receiving your cards, you can either Hit (H) or Stand (S)." << endl;
    cout << "* Hit means to draw one more card; you can keep hitting until you're satisfied." << endl;
    cout << "* Stand means to not draw any more cards and let the Dealer take his turn." << endl;
    cout << "* When it's the dealer's turn, they cannot stop hitting until they have a total of 17 or more." << endl;
    cout << "* After the dealer is done, the game is decided based on whoever got 21 or is the closest." << endl;
    cout << "* However, if any player goes over 21, they 'bust' and immediately lose the game." << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;
    cout << endl;

    Blackjack game;
    game.playBlackjack();
    
    cout << endl;
    cout << "Thanks for playing my game!" << endl;
    cout << endl;
    cout << endl;

    Blackjack simulation;
    cout << "Results Table Simulating 100,000 Hands:" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Starting Hand |  Hit(W/L/D)  |  Stand(W/L/D)" << endl;
    cout << "--------------------------------------------" << endl;
    simulation.calculateResults();
    
    return 0;
}

