#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int main() {
    ifstream myFile;
    myFile.open(R"(C:\Users\admin\Documents\Coding\AoC-CPP\2021\04\sample.txt)");

    int i, j;
    int lineCounter = 0;
    int boardCount = -1;
    int boardLine = 0;

    vector<string> drawnValues;
    string boards[200][200];

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
                    boards[boardCount][boardLine].append(myString);
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

    for (i = 0; i <= boardCount; i++) {
        cout << "Board number " << i << endl;
        for (j = 0; j < boardLine; j++) {
            cout << boards[i][j] << endl;
        }
    }

    return 0;
}
