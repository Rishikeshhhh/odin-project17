#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm> // Include the algorithm header for reverse

using namespace std;

// Structure to represent a square on the board
struct Square {
    int x, y;
    Square(int _x, int _y) : x(_x), y(_y) {}
};

// Function to generate all possible moves for a knight from a given square
vector<Square> generateKnightMoves(const Square& square) {
    vector<Square> moves;
    int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
    int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};
    for (int i = 0; i < 8; ++i) {
        int newX = square.x + dx[i];
        int newY = square.y + dy[i];
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            moves.push_back(Square(newX, newY));
        }
    }
    return moves;
}

// Function to find the shortest path between two squares using Breadth-First Search
vector<Square> shortestPath(const Square& start, const Square& end) {
    vector<vector<Square>> parent(8, vector<Square>(8, Square(-1, -1)));
    queue<Square> q;
    q.push(start);

    while (!q.empty()) {
        Square current = q.front();
        q.pop();
        if (current.x == end.x && current.y == end.y) {
            break;
        }

        vector<Square> moves = generateKnightMoves(current);
        for (const auto& move : moves) {
            if (parent[move.x][move.y].x == -1 && parent[move.x][move.y].y == -1) {
                parent[move.x][move.y] = current;
                q.push(move);
            }
        }
    }

    vector<Square> path;
    Square current = end;
    while (current.x != -1 && current.y != -1) {
        path.push_back(current);
        current = parent[current.x][current.y];
    }
    reverse(path.begin(), path.end()); // Reverse the path
    return path;
}

// Function to display the path
void displayPath(const vector<Square>& path) {
    cout << "You made it in " << path.size() - 1 << " moves! Here's your path:" << endl;
    for (const auto& square : path) {
        cout << "[" << square.x << "," << square.y << "]" << endl;
    }
}

// Main function
int main() {
    Square start(0, 0);
    Square end(7, 7);
    vector<Square> path = shortestPath(start, end);
    displayPath(path);
    return 0;
}
