/******************************************************************************
FFongNAO.cpp
Created on: March 13, 2018
	Author: Florence Fong
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <iostream>
using namespace std;

//functions before main program
int rollDice()
{
    return rand()%6+1;
}

bool is1(int diceRoll) {
    if (diceRoll == 1) {
        return true;
    } 
    else {
        return false;
    }
}

bool isSingleOne(int dice1,int dice2,int dice3)
{
    if ((is1(dice1) && !is1(dice2) && !is1(dice3)) || 
        (is1(dice2) && !is1(dice1) && !is1(dice3)) ||
        (is1(dice3) && !is1(dice1) && !is1(dice2)))
        {
        cout<<"Single one, lose turn\n";
        return true;
    }
    else {
        return false;  
    }
}

bool isTwoOnes(int dice1,int dice2,int dice3)
{
    if ((is1(dice1) && is1(dice2) && !is1(dice3)) || 
        (is1(dice2) && is1(dice3) && !is1(dice1)) ||
        (is1(dice1) && is1(dice3) && !is1(dice2)))
        {
        cout<<"Two ones, lose half of holdings, and lose turn\n";
        return true;
    }
    else {
        return false;  
    }
}

bool isThreeOnes(int dice1,int dice2,int dice3)
{
    if (is1(dice1) && is1(dice2) && is1(dice3)) {
        cout<<"Three ones, lose all holdings, and lose turn\n";
        return true;
    }
    else {
        return false;  
    }
}

//main program
int main()
{
    int bankHuman=0, bankComp=0;
    int d1,d2,d3,sum;
    int currentRound = 1;
    string answer;
    bool turnEnded = false;
    
    // reset random seed
    srand(time(0));
    
    //Human's Turn
    
    do {
        //humanloop
        do {
            d1 = rollDice(); 
            d2 = rollDice();
            d3 = rollDice();
            
            printf("Rolled %i, %i, %i\n",d1,d2,d3);
            
            turnEnded = false;
            
            if (isSingleOne(d1, d2, d3)) {
                // lose turn
                break;
            }
            
            if (isTwoOnes(d1, d2, d3)) {
                // lose turn and half bank
                bankHuman /= 2;
                break;
            }
            
            if (isThreeOnes(d1, d2, d3)) {
                // lose turn and all bank
                bankHuman = 0;
                break;
            }  
            
            sum = d1+d2+d3;
            cout<<"sum = "<<sum<<endl;
            bool reroll = false;
            
            do {
                cout<<"Bank (y/n)?";
                cin>>answer;
                if (answer=="y") {
                    bankHuman += sum;
                    turnEnded = true;
                    break;
                } else if (answer=="n") {
                    reroll = true;
                    break;
                }
            } while(answer!="y" || answer!="n");
            
            if (reroll == true) {
                //human wants to reroll, skip this iteration
                continue;
            }
            
        } while(!turnEnded);
        
        //Computer's Turn
        cout <<"Computer's turn\n";
        
         do {
            //computer loop
            d1 = rollDice(); 
            d2 = rollDice();
            d3 = rollDice();
            
            turnEnded = false;
            
            cout<<"Rolled "<<d1<<", "<<d2<<", "<<d3<<endl;
            
            if (isSingleOne(d1, d2, d3)) {
                // lose turn
                break;
            }
            
            if (isTwoOnes(d1, d2, d3)) {
                // lose turn and half bank
                bankComp /= 2;
                break;
            }
            
            if (isThreeOnes(d1, d2, d3)) {
                // lose turn and all bank
                bankComp = 0;
                break;
            }  
            
            sum = d1+d2+d3;
            
                
            if (sum >= 9 || ((bankComp+sum > bankHuman*1.5) && (bankHuman > 30))) {
                bankComp += sum;
                cout<<"sum = "<<sum<<" bank \n";
                turnEnded = true;
                break;
            } else {
                cout<<"sum = "<<sum<<" no bank \n";
                //computer wants to reroll, skip this iteration
                continue;
            }
            
            
        } while(!turnEnded);
        
        cout<<"After round "<<currentRound<<" human has "<<bankHuman<<" and computer has "<<bankComp<<endl<<endl;
        currentRound++;
        
    } while (bankHuman < 150 && bankComp < 150);
    
    
    if (bankHuman > bankComp) {
        cout<<"Human won"<<endl;
    } else if (bankHuman < bankComp) {
        cout<<"Computer won"<<endl;
    } else {
        cout<<"Tie"<<endl;
    }

    return 0;
}


