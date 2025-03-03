#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool isSafe(int row, int col, const vector<int>& board, int N) {
    for (int i = 0; i < row; ++i) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

void solveNQueens(int row, int N, vector<int>& board, vector<vector<int>>& solutions) {
    // If all queens are placed, add the solution to the list
    if (row == N) {
        solutions.push_back(board);
        return;
    }

    for (int col = 0; col < N; ++col) {
        // Check if it's safe to place the queen
        if (isSafe(row, col, board, N)) {
            board[row] = col;  // Place the queen
            solveNQueens(row + 1, N, board, solutions);  // Recur to place the next queen
            board[row] = -1;  // Backtrack
        }
    }
}

void printSolution(const vector<int>& solution, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (solution[i] == j) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int N;
    cout << "Enter the value of N (number of queens): ";
    cin >> N;

    vector<int> board(N, -1);
    vector<vector<int>> solutions;

    solveNQueens(0, N, board, solutions);

    for (const auto& solution : solutions) {
        printSolution(solution, N);
    }
    
    cout << "Found " << solutions.size() << " solutions." << endl;

    return 0;
}
