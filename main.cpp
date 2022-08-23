#include <iostream>
#include <vector>

using std::cout;
using std::vector;

void PrintBoard(const vector<vector<int>> board) {
    for (vector<int> line : board) {
        for (int value : line) {
            cout << value;
        }
        cout << "\n";
    }
}

int main() {
    vector<vector <int>> board{{0, 1, 0, 0, 0, 0},
                                {0, 1, 0, 0, 0, 0},
                                {0, 1, 0, 0, 0, 0},
                                {0, 1, 0, 0, 0, 0},
                                {0, 0, 0, 0, 1, 0}};

    PrintBoard(board);
}