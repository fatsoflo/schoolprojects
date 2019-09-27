/******************************************************************************
FFongTypeTut.cpp
Created on: March 31, 2018
	Author: Florence Fong
*******************************************************************************/
#include <stdio.h>
#include <ctime>
#include <ctype.h>
#include <cmath>
#include <string>
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

string generate5Chars() {
    
    string generated5Chars = "";
    string generatedChar = "";
    
    for(int i=0; i < 5; i++) {
        // each loop represents a place/digit in the 5 character long string
        // determine type of charatcter
        int randomType = rand() % 100; // 0 -> 100
        
        if (randomType < 80) {
            // generate alphabetic character 80% of the time
            
            if (randomType < 40) {
                // generate uppercase half the time
                // A= 65, Z=90
                generatedChar = char(65 + rand() % 26);
            } else {
                // generate lowercase half the time
                // a = 97, z = 122
                generatedChar = char(97 + rand() % 26);
            }
        } else {
            //generate wild card character 20% of the time
            
            if (randomType < 90) {
                // generate [0-9] half the time
                generatedChar = "0";
            } else {
                // generate [%-!] half the time
                generatedChar = "*";
            }
        }
        
        generated5Chars += generatedChar;
    }
    
    return generated5Chars;
}

string getExpandedForm(string unexpanded) {
    // accept unexpanded form. eg: "BIy0*"
    
    string expandedForm = "";
    
    for(int i=0; i < 5; i++) {
        if (unexpanded[i] == '0') {
            expandedForm += "[0-9]";
        } else if (unexpanded[i] == '*') {
            expandedForm += "[%-!]";
        } else {
            expandedForm += unexpanded[i];
        }
    }
    
    // return in expanded form. eg: "BIy[0-9][%-!]"
    return expandedForm;
}

int getOffset(string generated, string userInput) {
    int totalOffset = 0;
    
    for (int i=0; i < 5; i++) {
        
        if (generated[i] == '0') {
            // get the offset if the user types a nondigit
            if (!isdigit(userInput[i])) {
                totalOffset += abs( (int)userInput[i] - 48);
            }
            
        } else if (generated[i] == '*') {
            // get the offset if the user types a non-alphanumeric
            
            if (isalnum(userInput[i])) {
                totalOffset += abs( (int)userInput[i] - 42);
            }
        } else {
            
            totalOffset += abs( (int)userInput[i] - (int)generated[i]);
        }
        
    }
    
    return totalOffset;
}

int main()
{
    // reset random seed
    srand(time(0));
    
    // start off with full points
    int currentPoints = 2000;
    string userInput;
    
    do {
        userInput = "";
        string unexpandedChars = generate5Chars();
        string expandedChars = getExpandedForm(unexpandedChars);
        
        cout << "Your current points " << currentPoints << ", just type -> " << expandedChars <<" : ";
        
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        cin >> userInput;
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        
        duration<double> timeTaken = t2 - t1;
        double timeTakenMs = timeTaken.count() * 1000;
        
        int offset = getOffset(unexpandedChars, userInput);
        
        if (timeTakenMs < 10000) {
            cout << timeTakenMs << " milliseconds, you made it within the interval of 10000..." << endl;    
        } else {
            cout << timeTakenMs << " milliseconds, you *failed* it within the interval of 10000..." << endl;
            currentPoints -= (timeTakenMs - 10000);
        }
        
        if (offset != 0) {
            cout << "String offset is " << offset << ", your total penalty is " << offset << "...";
            currentPoints -= offset;
        } else {
            currentPoints += 500;
        }
        
        if (currentPoints >= 5000) {
            cout << "You win! Bye..." << endl;
            break;
        } else if (currentPoints <= 0) {
            cout << "Bye..." << endl;
            break;
        } 
    } while(true);
    
    return 0;
}


