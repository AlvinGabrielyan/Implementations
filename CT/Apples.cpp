#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int dfs(int node, int parent, vector<vector<int>>& adj, vector<bool>& hasApple) {
        int totalTime = 0;
        
        for (int neighbor : adj[node]) {
            if (neighbor == parent) continue; 
            
            int time = dfs(neighbor, node, adj, hasApple);
            if (time > 0 || hasApple[neighbor]) {
                totalTime += time + 2;  
            }
        }
        
        return totalTime;
    }
    
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        vector<vector<int>> adj(n); 
        
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        return dfs(0, -1, adj, hasApple);
    }
};

int main() {
    Solution solution;
    // int n = 7;
    // vector<vector<int>> edges = {{0,1}, {0,2}, {1,4}, {1,5}, {2,3}, {2,6}};
    // vector<bool> hasApple = {false, false, true, false, true, true, false};

    // int n = 7;
    // vector<vector<int>> edges = {{0,1}, {0,2}, {1,4}, {1,5}, {2,3}, {2,6}};
    // vector<bool> hasApple = {false, false, true, false, false, true, false};

    int n = 7;
    vector<vector<int>> edges = {{0,1}, {0,2}, {1,4}, {1,5}, {2,3}, {2,6}};
    vector<bool> hasApple = {false, false, false, false, false, false, false};

    cout << "Minimum time to collect all apples: " << solution.minTime(n, edges, hasApple) << endl;
    return 0;
}
