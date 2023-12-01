#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Finds two-digit number for each line by getting first
// and last digits in line and then putting them together.
// Then this number is added to a total, which is printed.
int main() {
  string line;
  int total = 0;

  ifstream calibrationVals("calibrationVals.txt");

  if (calibrationVals.is_open()) {

    while (getline(calibrationVals, line)) {
      char firstDigit;
      char lastDigit;

      // Find first digit
      for (int i = 0; i < line.length(); i++) {
        if (isdigit(line[i])) {
          firstDigit = line[i];
          break;
        }
      }

      // Find last string
      for (int i = line.length() - 1; i >= 0; i--) {
        if (isdigit(line[i])) {
          lastDigit = line[i];
          break;
        }
      }

      // Join two digits
      string numString = {firstDigit, lastDigit};
      int number = stoi(numString);
      total += number;
    }

    // Print total
    cout << "The total is: " << total << endl;

    // Close file
    calibrationVals.close();

  } else {
    cout << "Unable to open file";
  }

  return 0;
}
