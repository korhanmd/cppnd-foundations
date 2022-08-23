#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using std::cout;
using std::vector;
using std::string;
using std::ifstream;

void ReadBoardFile(string path) {
    ifstream board (path);

    if (board) {
        string line;
        while (getline(board, line)) {
            cout << line << "\n";
        }
    }
}

void PrintBoard(const vector<vector<int>> board) {
    for (vector<int> line : board) {
        for (int value : line) {
            cout << value;
        }
        cout << "\n";
    }
}

int main() {
    string board = "1.board";
    ReadBoardFile(board);
}