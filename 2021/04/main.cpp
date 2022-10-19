#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int main() {
    ifstream myFile;
    myFile.open(R"(C:\Users\admin\Documents\Coding\AoC-CPP\2021\04\sample.txt)");

    int i;
    int lineCounter = 0, boardLine = 0;
    int boardCount = -1;
    int numberCounter = 0;

    vector<string> drawnValues;
    string boards[10][5][5];

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

    // Explanation of each variable because I'm too lazy
    // to put actual good name variables that don't repeat themselves
    // (and because C++ doesn't let me parse 3 dimensional arrays to functions easily)
    //
    // i = Currently drawn value
    // j = Current board
    // l = Current line (Compared against 4 because there are only 4 lines for each board)
    // k = Current number
    for (i = 0; i < drawnValues.size(); i++) {
        cout << drawnValues[i] << '\n';
        for (int j = 0; j <= boardCount; j++) {
            // Cycle through each line of the board
            for (int l = 0; l <= 4; l++) {
                for (int k = 0; k <= 4; k++) {
                    cout << boards[j][l][k] << " ";
                }
            }
        }
    }

    return 0;
}
