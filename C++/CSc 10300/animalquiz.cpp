/******************************************************************************
FFongAnimalQuiz.cpp
Created on: May 4, 2018
	Author: Florence Fong
*******************************************************************************/
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

void outputVector(vector<string> vstring) {
    for (int i = 0; i<vstring.size(); i++) {
        cout << i << ": " << vstring[i] << endl;
    }
}

vector<string> getVectorFromSentence(string sentence) {
    
    int start = 0;
    vector<string> v;
    for(int i=0; i <= sentence.length(); i++) {
        char letter = sentence[i]; 
        int length = i - start;
        if (letter == ' ' || letter == NULL) {
            if (length != 0) {
                v.push_back(sentence.substr(start, length));
            }
            start = i + 1;
        }
    }
    
    return v;
}

vector<string> getAnimals() {
    vector<string> animals;
    string names;
    
    cout << "Enter at least five animals, e.g., cat, dog, etc..." << endl;
    while(true)
    {
        getline(cin,names);
        if(names=="") {
            if (animals.size() < 5) {
                continue;
            } else {
                break;
            }
        }
        
        
        vector<string> words = getVectorFromSentence(names);
        animals.insert(animals.end(), words.begin(), words.end());
        
        if (animals.size() >= 5) {
            break;
        }
    }
    return animals;
}

bool doesIndecesContainIndex(vector<int> indeces, int index) {
    bool contains = false;
    for (int j = 0; j<indeces.size(); j++) {
        if (index == indeces[j]) {
            contains = true;
            break;
        }
    }
    return contains;
}

vector<string> getOneToThreeAnimals(vector<string> animals, int amount) {
    
    vector<string> chosenAnimals;
    vector<int> chosenIndexes;
    
    for (int i=0; i<amount; i++){
        
        while(true) {
            int index = rand() % animals.size();
            bool duplicate = doesIndecesContainIndex(chosenIndexes, index);
            
            if (duplicate) {
                continue;
            }
            
            chosenIndexes.push_back(index);
            chosenAnimals.push_back(animals[index]);
            break;
        }
    }
    return chosenAnimals;
}

string getShuffledText(vector<string> v) {
    vector<char> text;
    for(int i =0; i< v.size(); i++) {
        string word = v[i];
        for(int j =0; j < word.length(); j++) {
            text.push_back(word[j]);
        }
    }
    
    random_shuffle ( text.begin(), text.end() );
    
    string textAsString = "";
    
    for(int i=0; i< text.size();i++) {
        textAsString += text[i];
    }
    
    return textAsString;
}

bool doesVectorContainWord(vector<string> v1, string word) {
    for(int i=0; i<v1.size(); i++) {
        if (v1[i] == word) {
            return true;
        }
    }
    return false;
}

bool areVectorsContainingSameWords (vector<string> v1, vector<string> v2) {
    for (int i = 0; i<v1.size(); i++) {
        if (!doesVectorContainWord(v2, v1[i])) {
            return false;
        }
    }
    return true;
}

string replaceTextWithBlanks(string word, int blanks) {
    vector<int> chosenIndexes;
    for(int i=0; i < blanks; i++) {
        while(true) {
            int index = rand() % word.length();
            bool duplicate = doesIndecesContainIndex(chosenIndexes, index);
            
            if (duplicate) {
                continue;
            }
            chosenIndexes.push_back(index);
            break;
        }
    }
    
    string replaced = "";
    for (int i=0; i<word.length(); i++) {
        if (doesIndecesContainIndex(chosenIndexes, i)) {
            replaced = replaced + "_";
        } else {
            replaced = replaced + word[i];
        }
    }
    return replaced;
}

int main()
{
    srand(time(0));
    
    vector<string> animals = getAnimals();
    outputVector(animals);
    
    bool quitGame = false;
    int success = 0, fail = 0, difficulty = 0;
    
    while(true) {
        int amount = rand() % 3 + 1;
        vector<string> chosenAnimals = getOneToThreeAnimals(animals, amount);
        
        string shuffledAnimals = getShuffledText(chosenAnimals);
        int maxDifficulty = shuffledAnimals.length();
        string shuffledAnimalsWithBlanks = replaceTextWithBlanks(shuffledAnimals, min(difficulty, maxDifficulty));
        
        
        while (true) {
            cout << "What are the " << amount << " animals in \"" << shuffledAnimalsWithBlanks << "\"?";
            
            string input;
            getline(cin, input);
            
            if (input == "?") {
                outputVector(animals);
                cout << "Enter again: ";
                continue;
            } else if (input == "quit") {
                cout << "Bye...";
                return 0;
            } else if (input == "") {
                continue;
            }
            
            vector<string> userInput = getVectorFromSentence(input);
            
            if (userInput.size() != chosenAnimals.size()) {
                continue;
            } else  if (areVectorsContainingSameWords(userInput, chosenAnimals)) {
                cout << "Yes!" << endl;
                success++;
                fail = 0;
            } else {
                cout << "Nope!" << endl;
                fail++;
                success = 0;
            }
            
            if (success == 2) {
                cout << "Succeeded two consecutive times, challenge goes up!" << endl;
                difficulty++;
                success = 0;
            } else if (fail == 2 && difficulty > 0) {
                cout << "Missed two consecutive times, challenge goes down!" << endl;
                difficulty--;
                fail = 0;
            }
            break;
        }
        
    };
    return 0;
}



