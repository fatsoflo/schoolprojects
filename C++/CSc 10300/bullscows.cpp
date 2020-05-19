/******************************************************************************
Fong2A.cpp
Created on: April 23, 2018
	Author: Florence Fong
*******************************************************************************/
#include <vector>
#include <chrono>
#include <iostream>
#include <ctime>
using namespace std;
using namespace std::chrono;

bool vectorContainsDigit(vector<int> digitsComputer, int digitGenerated){
    for(int i = 0; i < digitsComputer.size(); i++) {
        if (digitsComputer[i] == digitGenerated) {
            return true;
        }
    }
    return false;
}

int main()
{
    srand(time(0));
    vector<int> digitsComputer;
    int oneDigitComp;
    
    for (int i = 0; i < 4; i++) {
        
        do{
            oneDigitComp = rand()%10; //generate a random number from 0-9
            //check if it's already in digitsComputer. if not, add into that vector . if it is, try again (inside a while loop)
            if (vectorContainsDigit(digitsComputer, oneDigitComp) == false){
                digitsComputer.push_back(oneDigitComp);
                break;
            }   
        }while(true);
        
        
    }
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    int numberGuesses = 0;
    
    do{
        vector<int> digitsHuman;
        int userGuess;
        cout << "Enter a 4 digit number(unique digits): " << endl;
        cin >> userGuess;
        
        for (int i = 0; i < 4; i++){
            digitsHuman.push_back (userGuess % 10);
            userGuess /= 10;    
        }  
        
        numberGuesses += 1;
        
        int bull = 0, cow = 0;
        
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (digitsComputer[i] == digitsHuman[j]){
                    if (i == j){
                        bull += 1;
                    }else{
                        cow += 1;  
                    }
                }
            }
        }
        
        cout << "bulls = " << bull << " and cows = " << cow << endl;
        
        if (bull == 4){
            high_resolution_clock::time_point t2 = high_resolution_clock::now();
            duration<int> timeTaken = duration_cast<duration<int>>(t2 - t1);
            
            int timeMinute = timeTaken.count()/60;
            int timeSecond = timeTaken.count()%60;
            
            cout << "You guessed it in " << numberGuesses << " tries, taking " << timeMinute << " minutes and " << timeSecond << " seconds" << endl;
            
            break;
        }
        
    }while(true);
    
    
    
    return 0;
}

