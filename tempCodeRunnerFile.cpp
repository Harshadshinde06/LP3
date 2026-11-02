/*
    DAA Assignment A4: N-Queens using Backtracking
    Requirement: The first queen is already placed. Place the remaining
                 queens so that no two queens attack each other.

    This program asks for the position of the pre-placed queen.
    Row and column are entered using 1-based indexing.

    Compile:
        g++ -std=c++17 -O2 A4_N_Queens_Preplaced_Queen.cpp -o A4_NQueens

    Input example:
        4
        1 2
*/

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int n;
int fixedRow, fixedCol;
vector<int> queenColumn; // queenColumn[row] = column; -1 means empty.

// Check whether a queen can be placed at (row, col).
bool isSafe(int row, int col) {
    // Check all rows because the fixed queen may be above OR below this row.
    for (int otherRow = 0; otherRow < n; otherRow++) {
        if (otherRow == row || queenColumn[otherRow] == -1) {
            continue;
        }

        int otherCol = queenColumn[otherRow];

        // Same column means the queens attack vertically.
        if (otherCol == col) return false;

        // Equal row-distance and column-distance means same diagonal.
        if (abs(otherRow - row) == abs(otherCol - col)) {
            return false;
        }
    }

    return true;
}

// Place one queen per row. The pre-placed queen's row is skipped.
bool solveNQueens(int row) {
    // All rows have been processed, so a valid arrangement is complete.
    if (row == n) return true;

    // Do not move or replace the queen that was already placed.
    if (row == fixedRow) {
        return solveNQueens(row + 1);
    }

    // Try each column in the current row.
    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {
            queenColumn[row] = col; // Place the queen.

            if (solveNQueens(row + 1)) {
                return true;        // Keep the first complete solution.
            }

            queenColumn[row] = -1;  // Backtrack: remove the failed placement.
        }
    }

    return false; // No column works in this row.
}

void printBoard() {
    cout << "\nOne valid N-Queens arrangement:\n";

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (queenColumn[row] == col) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << '\n';
    }

    cout << "\nThe pre-placed queen was at row "
         << fixedRow + 1 << ", column " << fixedCol + 1 << ".\n";
}

int main() {
    cout << "Enter N: ";
    cin >> n;

    if (n <= 0 || n > 15) {
        cout << "Enter N from 1 to 15 for practical execution.\n";
        return 0;
    }

    cout << "Enter pre-placed queen position (row column, 1-based): ";
    cin >> fixedRow >> fixedCol;

    // Convert the entered 1-based coordinates to 0-based array indices.
    fixedRow--;
    fixedCol--;

    if (fixedRow < 0 || fixedRow >= n ||
        fixedCol < 0 || fixedCol >= n) {
        cout << "Invalid pre-placed queen position.\n";
        return 0;
    }

    queenColumn.assign(n, -1);
    queenColumn[fixedRow] = fixedCol; // Place the given queen first.

    if (solveNQueens(0)) {
        printBoard();
    } else {
        cout << "No solution exists for this pre-placed queen position.\n";
    }

    cout << "\nApproach: Backtracking.\n";
    cout << "Worst-case time complexity: O(N!) (upper-bound analysis).\n";
    cout << "Auxiliary space: O(N) for the queen-position array and recursion.\n";

    return 0;
}
