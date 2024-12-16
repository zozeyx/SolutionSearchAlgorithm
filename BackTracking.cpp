#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>

using namespace std;

// Graph represented as adjacency list with weights
unordered_map<char, vector<pair<char, int>>> graph = {
    {'A', {{'B', 2}, {'C', 7}, {'D', 3}, {'E', 10}}},
    {'B', {{'A', 2}, {'C', 3}, {'D', 5}, {'E', 4}}},
    {'C', {{'A', 7}, {'B', 3}, {'D', 6}, {'E', 1}}},
    {'D', {{'A', 3}, {'B', 5}, {'C', 6}, {'E', 9}}},
    {'E', {{'A', 10}, {'B', 4}, {'C', 1}, {'D', 9}}}
};

vector<char> best_path;
int min_distance = INT_MAX;

// Backtracking function
void backtrack(char current, vector<char>& path, int current_distance, vector<bool>& visited, char start) {
    // If all nodes are visited and we can return to the start node, check the distance
    if (path.size() == graph.size() && current == start) {
        if (current_distance < min_distance) {
            min_distance = current_distance;
            best_path = path;
            best_path.push_back(start); // Complete the cycle
        }
        return;
    }

    // Explore neighbors
    for (auto& neighbor : graph[current]) {
        char next = neighbor.first;
        int weight = neighbor.second;

        if (!visited[next - 'A']) { // Check if the neighbor is visited
            visited[next - 'A'] = true;
            path.push_back(next);
            backtrack(next, path, current_distance + weight, visited, start);
            path.pop_back();       // Backtrack
            visited[next - 'A'] = false;
        }
    }
}

int main() {
    vector<bool> visited(26, false); // Mark visited nodes (assuming A-Z nodes)
    vector<char> path;               // To store the current path
    char start = 'A';                // Starting node

    // Initialize the backtracking process
    visited[start - 'A'] = true;
    path.push_back(start);
    backtrack(start, path, 0, visited, start);

    // Output the result
    cout << "Optimal Path: ";
    for (char node : best_path) {
        cout << node << " ";
    }
    cout << "\nTotal Distance: " << min_distance << endl;

    return 0;
}
