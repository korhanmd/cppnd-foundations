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

enum class State {kEmpty, kObstacle};

// Read a string line, converts the line to a int vector and returns the vector
vector<State> ParseLine(string line) {
    istringstream sline(line);
    int i;
    char c;
    vector<State> line_vector;

    while (sline >> i >> c) {
        line_vector.push_back(i ? State::kObstacle : State::kEmpty);
    }

    return line_vector;
}

// Reads the board file and returns a 2D int vector that contains board
vector<vector<State>> ReadBoardFile(string path) {
    ifstream board_file (path);
    vector<vector<State>> board;

    if (board_file) {
        string line;
        while (getline(board_file, line)) {
            board.push_back(ParseLine(line));
        }
    }

    return board;
}

// Returns formatted string according to input State
string CellString(State s) {
    switch (s) {
    case State::kObstacle:
        return "⛰️   ";
    default:
        return "0   ";
    }
}

// Prints a 2D int vector
void PrintBoard(const vector<vector<State>> board) {
    for (vector<State> line : board) {
        for (State value : line) {
            cout << CellString(value);
        }
        cout << "\n";
    }
}

int main() {
    vector<vector<State>> board = ReadBoardFile("1.board");
    PrintBoard(board);
}