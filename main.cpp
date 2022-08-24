#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using std::cout;
using std::vector;
using std::string;
using std::ifstream;
using std::istringstream;

vector<int> ParseLine(string line) {
    istringstream sline(line);
    int i;
    char c;
    vector<int> line_vector;

    while (sline >> i >> c) {
        line_vector.push_back(i);
    }

    return line_vector;
}

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

#include "test.cpp"

int main() {
    ReadBoardFile("1.board");
    TestParseLine();
}