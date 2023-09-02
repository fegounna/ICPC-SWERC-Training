#include <bits/stdc++.h>

using namespace std;
const int INF = 1e9;

typedef pair<int, int> ii; 
vector<ii> vs[10001];
vector<ii> parent[10001];

vector<int> dijkstra(int source, int n) {
    vector<int> dist(n, INF);
    priority_queue<ii, vector<ii>, greater<ii>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto &[v, w] : vs[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
                parent[v].clear();
                parent[v].push_back({u,w});
            }
            else if(dist[u]+w == dist[v])
                parent[v].push_back({u,w});
        }
    }
    return dist;
}
struct triple{
    int n1;
    int n2;
    int w;
    bool operator < (const triple& other) const {
        return tie(n1, n2, w) < tie(other.n1, other.n2, other.w);
    }
};
set<triple> unique_paths;
bool visited[10000];
void find_paths(int v){
    if(v==0)    return;
    if(visited[v])  return;
    visited[v]=true;
    for(auto [u,w] : parent[v]){
        triple p;
        p.n1=u;
        p.n2=v;
        p.w=w;
        unique_paths.insert(p);
        find_paths(u);
    }
}
int main() {
    int P,T;
    cin>>P>>T;
    for(int i=0;i<T;i++){
        int n1,n2,w;
        cin>>n1>>n2>>w;
        vs[n1].push_back({n2,w});
        vs[n2].push_back({n1,w});
    }

    vector<int> dist = dijkstra(0, P);
    find_paths(P-1);
    int s=0;
    
    for(triple p : unique_paths) {
        for(auto [v_,w]: vs[p.n1]){
            if(v_==p.n2&&p.w==w){
                s+=w;
            }
        }
    }
    cout<<2*s<<endl;
  
}
