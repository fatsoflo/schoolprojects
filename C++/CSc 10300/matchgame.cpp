/******************************************************************************
FFongMatchGame.cpp
Created on: May 17, 2018
    Author: Florence Fong
*******************************************************************************/
#include <stdio.h>
#include <ctime>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
using namespace std::chrono;

#ifdef __WIN32__
#define sleep(n) Sleep(1000 * n)  //Windows Sleep in ms

#define clear() system("cls")
#endif

#ifdef __APPLE__
#include <unistd.h>

#define clear() system("clear")
#endif

struct BoardInfo {
    int rows;
    int cols;
    int product;
    int pairs;
};

struct Coord {
    int row;
    int col;
};

struct Cell {
    Coord coord;
    int slot;
    char symbol;
    bool guessed;
};

struct Guesses {
    int slot1;
    int slot2;
};

Guesses getUserGuesses(BoardInfo boardInfo) {
    Guesses guesses;
    string input;
    int guess;
    while (true) {
        cout << "Enter first slot to view: ";
        cin >> input;
        guess = stoi(input);
        if (guess <= boardInfo.product) {
            guesses.slot1 = guess;
            break;
        }
    }
    while (true) {
        cout << "Enter second slot to view: ";
        cin >> guess;
        if (guess <= boardInfo.product && guess != guesses.slot1) {
            guesses.slot2 = guess;
            break;
        }
    }
    return guesses;
}

Cell createCell(int row, int col, int slot) {
    Coord coord = {row, col};
    Cell cell;
    cell.coord = coord;
    cell.slot = slot;
    cell.guessed = false;
    return cell;
}

Coord mapSlotToCoord(int slot, BoardInfo boardInfo) {
    Coord c;
    c.row = (slot - 1) / boardInfo.cols;
    c.col = (slot - 1) % boardInfo.cols;
    return c;
}

BoardInfo getBoardInfo() {
    BoardInfo b;
    string input;

    while(true){
        cout << "Size requirement: product of row x col must be between 16 and 64 and be even\n";
        cout << "Enter rows: ";
        cin >> input;
        b.rows = stoi(input);
        cout << "Enter columns: ";
        cin >> b.cols;
        b.cols = stoi(input);

        b.product = b.rows * b.cols;

        if (b.product >= 16 && b.product <= 64 && b.product %2 == 0){
            break;
        }
    }
    cout << "\n\n";

    b.pairs = b.product / 2;
    return b;
}

void printBoard(const vector <vector <Cell> >& board, Coord revealedC1, Coord revealedC2, bool revealAll) {
    for (int i = 0; i < board.size(); i++) {
        vector <Cell> row = board[i];
        for (int j = 0; j < row.size(); j++) {
            Cell cell = row[j];
            if (revealAll == true ||
                cell.guessed == true ||
                (cell.coord.row == revealedC1.row && cell.coord.col == revealedC1.col) ||
                (cell.coord.row == revealedC2.row && cell.coord.col == revealedC2.col)) {
                cout << " " << (char)cell.symbol << " ";
            } else {
                if (cell.slot <= 9) {
                    cout << " ";
                }
                cout << cell.slot << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

vector <vector <Cell> > createBoard(BoardInfo boardInfo) {
    vector <vector <Cell> > board;

    // First, initialize a grid of cells with slot values
    int slot = 1;
    for (int i = 0; i < boardInfo.rows; i++) {
        // set up a vector for each row
        vector <Cell> row;
        for (int j = 0; j < boardInfo.cols; j++) {
            // Just create a cell without a symbol for now.
            row.push_back(createCell(i, j, slot));
            slot++;
        }
        // add this row vector to the outer vector
        board.push_back(row);
    }

    // Next, generate symbols for coord pairs, and assign them to cells

    // Set up a vector that corresponds to unassigned slots
    vector <int> unusedSlots;
    for(int i = 1; i <= boardInfo.product; i++) {
        unusedSlots.push_back(i);
    }
    // randomize the slots
    random_shuffle ( unusedSlots.begin(), unusedSlots.end() );

    for (int symbol = 65; symbol < 65 + boardInfo.pairs; symbol++) {
        // get the last slot, and remove it from the vector
        int slot1 = unusedSlots.back();
        unusedSlots.pop_back();

        int slot2 = unusedSlots.back();
        unusedSlots.pop_back();

        Coord coord1 = mapSlotToCoord(slot1, boardInfo);
        Coord coord2 = mapSlotToCoord(slot2, boardInfo);
        board[coord1.row][coord1.col].symbol = symbol;
        board[coord2.row][coord2.col].symbol = symbol;
    }

    return board;
}

int main() {
    // reset random seed
    srand(time(0));

    char alert = 7;
    Coord nullCoord = {-1, -1};

    // Get board info from the user
    BoardInfo boardInfo = getBoardInfo();

    // Create the board based on the board size
    vector <vector <Cell> > board = createBoard(boardInfo);

    // Display initial instructions
    double timeAllowed = boardInfo.pairs * 30; // in seconds
    cout << "Allowing 30 seconds per pair" << endl;
    cout << "You will have " << timeAllowed / 60 << " minutes and " << (int)timeAllowed % 60 << " seconds to find the " << boardInfo.pairs << " pairs." << endl;
    cout << "Let's play \n\n";

    // Output the entire board the first time (without supplying user guesses)
    printBoard(board, nullCoord, nullCoord, false);

    int guessedPairs = 0;

    // Start the game timer
    high_resolution_clock::time_point timeStart = high_resolution_clock::now();

    while (true) {
        Guesses guesses = getUserGuesses(boardInfo);

        high_resolution_clock::time_point timeNow = high_resolution_clock::now();
        duration<double> timeTaken = timeNow - timeStart;
        double timeTakenSeconds = timeTaken.count();

        // End game condition: time expired
        if (timeTakenSeconds > timeAllowed) {
            cout << "Time has expired \n You revealed: \n";
            printBoard(board, nullCoord, nullCoord, false);
            cout << "All the pairs were at: \n";
            printBoard(board, nullCoord, nullCoord, true);
            return 0;
        }

        Coord guess1 = mapSlotToCoord(guesses.slot1, boardInfo);
        Coord guess2 = mapSlotToCoord(guesses.slot2, boardInfo);

        printBoard(board, guess1, guess2, false);

        Cell& c1 = board[guess1.row][guess1.col];
        Cell& c2 = board[guess2.row][guess2.col];

        if (c1.symbol == c2.symbol) {
            if (c1.guessed) {
                cout << "Previously matched \n";
            } else {
                c1.guessed = true;
                c2.guessed = true;
                guessedPairs++;
                cout << "Match \n" << alert;
            }
        } else {
            cout << "No Match \n";
            sleep(3);
            clear();
        }

        // End game condition: all matches found
        if (guessedPairs == boardInfo.pairs) {
            cout << "All matched within " << timeTakenSeconds / 60 << " minutes and " << (int)timeTakenSeconds % 60 << " seconds";
            return 0;
        }
    }

    return 0;
}



