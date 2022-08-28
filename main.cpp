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

// Returns the board with a path from start to the goal
vector<vector<State>> Search(vector<vector<State>> board, int init[2], int goal[2]){
    cout << "No path found!\n";
    return vector<vector<State>> {};
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
    int init[] {0, 0};
    int goal[] {4, 5};

    vector<vector<State>> board = ReadBoardFile("1.board");
    vector<vector<State>> solution = Search(board, init, goal);

    PrintBoard(solution);
}