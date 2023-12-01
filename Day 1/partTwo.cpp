#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// Finds two-digit number for each line by getting first
// and last digits or numbers written as word in line and 
// then putting them together.
// Then this number is added to a total, which is printed.
int main() {
    string digits[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    string line;
    long total = 0;
    int lines = 0;

    ifstream calibrationVals("calibrationVals.txt");
    ofstream outFile("outCpp.txt");

    if (calibrationVals.is_open() && outFile.is_open()) {
        while (getline(calibrationVals, line)) {
            std::cout << line << endl;
            outFile << line << endl;
            char firstDigit = 0;
            char lastDigit = 0;

            // Find first digit
            for (int i = 0; i < line.length(); i++) {
                if (isdigit(line[i])) {
                    firstDigit = line[i];
                    break;
                } else {
                    for (int j = 0; j < sizeof(digits) / sizeof(digits[0]); j++) {
                        // Create substring, search for digit string
                        if (line.substr(i, digits[j].length()).find(digits[j]) != string::npos) {
                            firstDigit = to_string(j + 1)[0];
                            std::cout<<"First digit str match: "<<firstDigit<<endl;
                            goto endfor_first;      // Exit both for loops
                        }
                    }
                }
            }
        endfor_first:

            // Find last string
            for (int i = line.length() - 1; i >= 0; i--) {
                if (isdigit(line[i])) {
                    lastDigit = line[i];
                    break;
                } else {
                    for (int j = 0; j < sizeof(digits) / sizeof(digits[0]); j++) {
                        // find() searches characters after __pos
                        if (line.find(digits[j], i - digits[j].length()) != string::npos) {
                            lastDigit = to_string(j + 1)[0];
                            std::cout<<"Last digit str match: "<<lastDigit<<endl;
                            goto endfor_last;      // Exit both for loops
                        }
                    }
                }
            }
        endfor_last:

            // Join two digits
            string numString = { firstDigit, lastDigit };
            int number = stoi(numString);
            std::cout << "Got " << number << endl;
            outFile << number << endl;
            total += number;
            lines++;
        }

        // Print total
        std::cout << "The total is: " << total << endl;
        std::cout << "The line count is: " << lines << endl;

        // Close file
        calibrationVals.close();
        outFile.close();

    } else {
        std::cout << "Unable to open file";
    }

    return 0;
}