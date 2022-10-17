#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
char mostRep(const vector<string>& values, int pos, int mode) {
    int counter0[20] = { 0 };
    int counter1[20] = { 0 };

    string currentValue;
    for (int i = 0; i < values.size(); i++) {
        currentValue = values[i];
        for (int j = 0; j <= currentValue.length(); j++) {
            if (currentValue[j] == '0') counter0[j]++;
            else if (currentValue[j] == '1') counter1[j]++;
        }
    }

    // Mode:
    // 0 - Return '1' if number of elements is the same
    // 1 - Return '0' if number of elements is the same
    if (mode == 0) {
        if (counter0[pos] > counter1[pos]) return '0';
        else if (counter0[pos] <= counter1[pos]) return '1';
    } else if (mode == 1) {
        if (counter0[pos] > counter1[pos]) return '0';
        else if (counter0[pos] <= counter1[pos]) return '1';
    }
    return 'X';
}

int main() {
    ifstream myFile;
    myFile.open(R"(C:\Users\admin\Documents\Coding\AoC-CPP\2021\03\sample.txt)");

    int i;
    int counter0[20] = { 0 };
    int counter1[20] = { 0 };
    int counterF[20] = { 0 };
    int counterL[20] = { 0 };
    string counterFcc, counterLcc;
    unsigned long long textLength = -1;

    vector<string> storedValues;

    if (myFile.is_open()) {
        string myString;

        while (myFile.good()) {
            getline(myFile, myString);
            if (textLength == -1) textLength = myString.length();

            storedValues.push_back(myString);

            for (i = 0; i < myString.length(); i++) {
                if (myString[i] == '0') counter0[i]++;
                else if (myString[i] == '1') counter1[i]++;
            }
        }
    } else {
        cout << "Couldn't open the file" << endl;
        return -1;
    }

    vector<string> storedValuesCopy = storedValues;

    for (i = 0; i < textLength; i++) {
        if (counter0[i] > counter1[i]) {
            counterF[i] = 0; counterFcc += '0';
            counterL[i] = 1; counterLcc += '1';
        } else if (counter0[i] < counter1[i]) {
            counterF[i] = 1; counterFcc += '1';
            counterL[i] = 0; counterLcc += '0';
        }
    }

    cout << "Gamma Rate: " << counterFcc << '\n';
    cout << "Epsilon Rate: " << counterLcc << endl;

    for (int j = 0; j < textLength; j++) {
        char compareTo = mostRep(storedValues, j, 0);
        string tempString;
        for (i = storedValues.size() - 1; i >= 0; i--) {
            tempString = storedValues[i];

            if (storedValues.size() > 1) {
                if (tempString[j] != compareTo) storedValues.erase(storedValues.begin() + i);
            }
        }
    }

    for (int j = 0; j < textLength; j++) {
        char compareTo = mostRep(storedValuesCopy, j, 1);
        string tempString;
        for (i = storedValuesCopy.size() - 1; i >= 0; i--) {
            tempString = storedValuesCopy[i];

            if (storedValuesCopy.size() > 1) {
                if (tempString[j] == compareTo) storedValuesCopy.erase(storedValuesCopy.begin() + i);
            }
        }
    }

    cout << "Oxygen generator rating: ";
    for (i = 0; i < storedValues.size(); i++) {
        cout << storedValues[i] << endl;
    }

    cout << "CO2 scrubber rating: ";
    for (i = 0; i < storedValuesCopy.size(); i++) {
        cout << storedValuesCopy[i] << endl;
    }


    return 0;
}
