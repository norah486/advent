#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
int main() {
    int part;
    cout << "Part: ";
    cin >> part;
    if (part != 1 && part != 2) {
        cout << "Not a valid part";
        return -1;
    }

    ifstream myFile;
    myFile.open(R"(C:\Users\admin\Documents\Coding\AoC-CPP\2021\04\sample.txt)");

    int i, l;
    int lineCounter = 0, boardLine = 0;
    int boardCount = -1;
    int numberCounter = 0;

    vector<string> drawnValues;
    string boards[300][5][5];

    if (myFile.is_open()) {
        string myString;
        string currentNumber;

        while (myFile.good()) {
            getline(myFile, myString);
            if (lineCounter == 0) {
                for (i = 0; i < myString.length(); i++) {
                    if (myString[i] != ',') {
                        currentNumber += myString[i];
                        if (i == myString.length() - 1) {
                            drawnValues.push_back(currentNumber);
                        }
                    } else {
                        drawnValues.push_back(currentNumber);
                        currentNumber = "";
                    }
                }
            } else {
                if (!myString.empty()) {
                    string boardCurrentNumber;
                    // Made this a 3 dimensional array because I didn't have any other good ideas
                    for (i = 0; i < myString.length(); i++) {
                        if (i == 2 || i == 5 || i == 8 || i == 11) {
                            boards[boardCount][boardLine][numberCounter].append(boardCurrentNumber);
                            boardCurrentNumber = "";
                            numberCounter++;
                        } else if (myString[i] != ' ') {
                            boardCurrentNumber += myString[i];
                            if (i == myString.length() - 1) {
                                boards[boardCount][boardLine][numberCounter].append(boardCurrentNumber);
                                boardCurrentNumber = "";
                                numberCounter = 0;
                            }
                        }
                    }
                    boardLine++;
                } else {
                    boardCount++;
                    boardLine = 0;
                }
            }
            lineCounter++;
        }
    } else {
        cout << "Couldn't open file" << endl;
        return -1;
    }

    int storedBoardCount = boardCount;

    int saved_board;
    int saved_number;
    vector<int> winningBoards;
    // Explanation of each variable because I'm too lazy
    // to put actual good name variables that don't repeat themselves
    // (and because C++ doesn't let me parse 3 dimensional arrays to functions easily)
    //
    // i = Currently drawn value
    // j = Current board
    // l = Current line (Compared against 4 because there are only 4 lines for each board)
    // k = Current number
    for (i = 0; i < drawnValues.size(); i++) {
        for (int j = 0; j <= boardCount; j++) {
            // Cycle through each line of the board
            for (l = 0; l <= 4; l++) {
                // Cycle through each value of the line
                for (int k = 0; k <= 4; k++) {
                    if (drawnValues[i] == boards[j][l][k]) {
                        boards[j][l][k] = "X";
                    }
                    if ((boards[j][l][0] == "X" && boards[j][l][1] == "X" && boards[j][l][2] == "X" && boards[j][l][3] == "X" && boards[j][l][4] == "X") || (boards[j][0][k] == "X" && boards[j][1][k] == "X" && boards[j][2][k] == "X" && boards[j][3][k] == "X" && boards[j][4][k] == "X")) {
                        // Part 1
                        if (part == 1) {
                            saved_board = j;
                            saved_number = stoi(drawnValues[i]);
                            cout << "BOARD " << j << ": ";
                            goto break_loop;
                        }
                        // Part 2
                        if (part == 2) {
                            if (find(winningBoards.begin(), winningBoards.end(), j) == winningBoards.end()) {
                                winningBoards.push_back(j);
                                boardCount++;
                            }

                            if (boardCount == (storedBoardCount * 2) + 1) {
                                saved_board = j;
                                saved_number = stoi(drawnValues[i]);
                                goto break_loop;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "Not supposed to be here";
    return -1;

    // Part 1
    break_loop:
    // Cycle through each line
    vector<int> saved_board_numbers;
    for (i = 0; i <= 4; i++) {
        // Cycle through each value
        for (l = 0; l <= 4; l++) {
            if (boards[saved_board][i][l] != "X") {
                int num = stoi(boards[saved_board][i][l]);
                saved_board_numbers.push_back(num);
            }
        }
    }

    int sum = 0;
    for (i = 0; i < saved_board_numbers.size(); i++) {
        sum += saved_board_numbers[i];
    }
    cout << sum << endl;
    cout << "Saved number: " << saved_number << endl;
    cout << "Total: " << (sum * saved_number) << endl;
    return 0;
}
