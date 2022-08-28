#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::cout;
using std::vector;
using std::string;
using std::ifstream;
using std::istringstream;
using std::sort;

enum class State {kEmpty, kObstacle, kClosed, kPath};

// directional deltas
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

// Reads a string line, converts the line to a int vector and returns the vector
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

// Compares two cells according to their F values
bool Compare(vector<int> first, vector<int> second) {
    int first_f = first[2] + first[3];
    int second_f = second[2] + second[3];

    return first_f > second_f;
}

// Sorts the two-dimensional vector in descending order
void CellSort(vector<vector<int>> *v) {
    sort(v->begin(), v->end(), Compare);
}

// Calculates heuristic with Manhattan Distance
int Heuristic(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

// Checks if the cell inside the board and empty
bool CheckValidCell(int x, int y, vector<vector<State>> &board) {
    bool is_x_inside = (x >= 0 && x < board.size());
    bool is_y_inside = (y >= 0 && y < board[0].size());

    if (is_x_inside && is_y_inside)
        return board[x][y] == State::kEmpty;
    
    return false;
}

// Adds cell to the openlist and closes it from the grid
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &openlist, vector<vector<State>> &board) {
    openlist.push_back(vector<int>{x, y, g, h});
    board[x][y] = State::kClosed;
}

// Adds valid neighbors of the current cell to the openlist
void ExpandNeighbors(const vector<int> &current, int goal[2], vector<vector<int>> &openlist, vector<vector<State>> &board) {
    int x = current[0];
    int y = current[1];

    for (const int *d : delta) {
        int x2 = x + d[0];
        int y2 = y + d[1];

        if (CheckValidCell(x2, y2, board)) {
            AddToOpen(x2, y2, current[2] + 1, Heuristic(x2, y2, goal[0], goal[1]), openlist, board);
        }
    }
}

// Returns the board with a path from start to the goal
vector<vector<State>> Search(vector<vector<State>> board, int init[2], int goal[2]) {
    // Openlist vector
    vector<vector<int>> open {};

    // Calculate the heuristic of initial node
    int x = init[0];
    int y = init[1];
    int heuristic = Heuristic(x, y, goal[0], goal[1]);

    // Add the node to the openlist
    AddToOpen(x, y, 0, heuristic, open, board);

    while (open.size() > 0) {
        CellSort(&open);

        // Get the current cell
        auto current = open.back();
        open.pop_back();

        x = current[0];
        y = current[1];
        board[x][y] = State::kPath;

        // If current cell is the goal, return board
        if (x == goal[0] && y == goal[1])
            return board;

        ExpandNeighbors(current, goal, open, board);
    }

    cout << "No path found!\n";
    return vector<vector<State>> {};
}

// Returns formatted string according to input State
string CellString(State s) {
    switch (s) {
    case State::kObstacle:
        return "⛰️   ";
    case State::kPath:
        return "🚗   ";
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

#include "test.cpp"

int main() {
    int init[] {0, 0};
    int goal[] {4, 5};

    vector<vector<State>> board = ReadBoardFile("1.board");
    vector<vector<State>> solution = Search(board, init, goal);

    PrintBoard(solution);

    // Tests
    TestHeuristic();
    TestAddToOpen();
    TestCompare();
    TestSearch();
    TestCheckValidCell();
    TestExpandNeighbors();
}