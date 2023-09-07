/* CSI 3344
 * Homework Assignment #1
 * Filename: HW1-driver.cpp
 * Student name: Chas Doughtry
 * Assignment: HW 1
 * Due Date: Sep 1, 2023
 * OS: Windows
 * This program multiplies large integers from user input
 * through Karatsuba's multiplication algorithm.
 *
 * To feed a file as input from the command line enter the file
 * name(s) as program arguments. I've included a file with various
 * test cases called "1TestCase.txt" in the cmake-build-debug folder.
 */

#include <cmath>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

/* karatsuba
 * parameters: x - multiplicand
 *             y - multiplier
 * return: Result
 * Implements Karatsuba's algorithm
 * to multiply large integers.
 */
long long int karatsuba(long int x, long int y) {

    // Base case: a single-digit number
    if (x < 10 || y < 10) {
        return x * y;
    }

    // number of digits in x & y
    int n = max(int(log10(x) + 1), int(log10(y)+1));

    // Split x & y into 2 parts
    long long int a = x / static_cast<long long int>(pow(10, (n / 2))); // high x
    long long int b = x % static_cast<long long int>(pow(10, (n / 2))); // low x
    long long int c = y / static_cast<long long int>(pow(10, (n / 2))); // high y
    long long int d = y % static_cast<long long int>(pow(10, (n / 2))); // low y

    long long int bd = karatsuba(b, d);
    long long int adbc = karatsuba((b + a), (d + c));
    long long int ac = karatsuba(a, c);

    return (ac * static_cast<long long int>(pow(10, 2 * (n / 2)))) +
          ((adbc - ac - bd) * static_cast<long long int>(pow(10, (n / 2)))) + bd;
}

/* main
 * parameters: x - multiplicand
 *             y - multiplier
 * return: 0 indicates successful run.
 * Receives user input and calls karatsuba
 * function. Then prints results.
 */
int main(int argc, char* argv[]) {

    long int x = 0, y = 0;
    long long int result;

    // If given file input
    if(argc > 1){
        fstream inputFile;
        for (int i = 1; i < argc; i++){
            inputFile.open(argv[i]);

            if(inputFile.is_open()) {
                cout << "Input from " << argv[i];
                while (inputFile >> x >> y) {
                    result = karatsuba(x, y);
                    cout << "\nX: " << x;
                    cout << "\nY: " << y;
                    cout << "\nResult of multiplication: " << result << endl;

                }
                inputFile.close();
            } else{
                cerr << "ERROR: " << argv[i] << " not found.\n";
            }
        }
    }
    else {
        cout << "Enter two numbers to multiply: ";
        cin >> x >> y;
        result = karatsuba(x, y);
        cout << "\nX: " << x;
        cout << "\nY: " << y;
        cout << "\nResult of multiplication: " << result << endl;
    }

    return 0;
}
