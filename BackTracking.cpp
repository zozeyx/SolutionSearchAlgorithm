#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>

using namespace std;

// 그래프: adjacency list로 정의
unordered_map<char, vector<pair<char, int>>> graph = {
    {'A', {{'B', 2}, {'C', 7}, {'D', 3}, {'E', 10}}},
    {'B', {{'A', 2}, {'C', 3}, {'D', 5}, {'E', 4}}},
    {'C', {{'A', 7}, {'B', 3}, {'D', 6}, {'E', 1}}},
    {'D', {{'A', 3}, {'B', 5}, {'C', 6}, {'E', 9}}},
    {'E', {{'A', 10}, {'B', 4}, {'C', 1}, {'D', 9}}}
};

vector<char> best_path;    // 최적 경로
int min_distance = INT_MAX; // 최소 거리

// 백트래킹 함수
void backtrack(char current, vector<char>& path, int current_distance, vector<bool>& visited, char start) {
    // 모든 노드를 방문하고, 다시 시작점으로 돌아올 수 있는지 확인
    if (path.size() == graph.size() && graph[current][0].second > 0) {
        int total_distance = current_distance + graph[current][0].second; // 시작점으로의 거리 추가
        if (total_distance < min_distance) {
            min_distance = total_distance; // 최소 거리 갱신
            best_path = path;
            best_path.push_back(start); // 시작점을 추가해 경로 완성
        }
        return;
    }

    // 현재 노드의 모든 이웃 탐색
    for (auto& neighbor : graph[current]) {
        char next = neighbor.first; // 이웃 노드
        int weight = neighbor.second; // 거리

        if (!visited[next - 'A']) { // 방문하지 않은 노드인지 확인
            visited[next - 'A'] = true;
            path.push_back(next);
            backtrack(next, path, current_distance + weight, visited, start);
            path.pop_back();       // 백트래킹
            visited[next - 'A'] = false;
        }
    }
}

int main() {
    vector<bool> visited(26, false); // 방문한 노드 기록 (A-Z 기준)
    vector<char> path;               // 현재 경로 저장
    char start = 'A';                // 시작점

    // 초기화: 시작점 방문 처리
    visited[start - 'A'] = true;
    path.push_back(start);

    // 백트래킹 시작
    backtrack(start, path, 0, visited, start);

    // 결과 출력
    cout << "Optimal Path: ";
    for (char node : best_path) {
        cout << node << " ";
    }
    cout << "\nTotal Distance: " << min_distance << endl;

    return 0;
}
