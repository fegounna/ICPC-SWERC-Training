#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> vs, rev_vs;

int bfs(const vector<vector<int>>& graph, int u0, int n) {
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(u0);
    visited[u0] = true;
    int count = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        count++;

        for (int v : graph[u])
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
    }
    return count - 1; 
}

int main() {
    int n, a, b, p;
    cin >> a >> b >> n >> p;

    vs.resize(n);
    rev_vs.resize(n);

    for (int i = 0; i < p; i++) {
        int u, v;
        cin >> u >> v;
        vs[u].push_back(v);
        rev_vs[v].push_back(u); 
    }

    int ca = 0, cb = 0, imp = 0;

    for (int i = 0; i < n; i++) {
        int suc = bfs(vs, i, n); 
        int pred = bfs(rev_vs, i, n); 

        if (suc >= n - a) 
            ca++;
        if (suc >= n - b) 
            cb++;
        if (pred >= b)
            imp++;
    }

    cout << ca << endl;
    cout << cb << endl;
    cout << imp << endl;

}
