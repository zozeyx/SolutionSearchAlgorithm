import java.util.*;

public class BranchAndBoundAG {
    static final int INF = Integer.MAX_VALUE; // Infinite cost for non-existing edges
    static int N = 5; // Number of nodes
    static char[] nodes = {'A', 'B', 'C', 'D', 'E'}; // Node labels
    static int[][] graph = {
        // Adjacency matrix representation of the graph
        {0, 2, 7, 3, 10},  // Distances from A
        {2, 0, 3, 5, 4},   // Distances from B
        {7, 3, 0, 6, 1},   // Distances from C
        {3, 5, 6, 0, 9},   // Distances from D
        {10, 4, 1, 9, 0}   // Distances from E
    };

    static int minCost = INF; // Store minimum cost
    static List<Character> bestPath = new ArrayList<>(); // Store best path

    // Branch and Bound Algorithm
    static void branchAndBound(int current, int cost, int visitedCount, boolean[] visited, List<Character> path) {
        if (visitedCount == N && graph[current][0] > 0) { // Return to the starting node
            int totalCost = cost + graph[current][0];
            if (totalCost < minCost) {
                minCost = totalCost;
                bestPath = new ArrayList<>(path);
                bestPath.add('A'); // Complete the cycle
            }
            return;
        }

        for (int i = 0; i < N; i++) {
            if (!visited[i] && graph[current][i] > 0) { // If not visited and edge exists
                visited[i] = true;
                path.add(nodes[i]);

                branchAndBound(i, cost + graph[current][i], visitedCount + 1, visited, path);

                // Backtracking
                visited[i] = false;
                path.remove(path.size() - 1);
            }
        }
    }

    public static void main(String[] args) {
        boolean[] visited = new boolean[N];
        List<Character> path = new ArrayList<>();

        // Start from node A
        visited[0] = true; // Mark A as visited
        path.add('A');

        branchAndBound(0, 0, 1, visited, path);

        // Output the result
        System.out.println("Path: " + bestPath);
        System.out.println("Total Distance: " + minCost);
    }
}
