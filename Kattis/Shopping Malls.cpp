#include<bits/stdc++.h>

using namespace std;

#define ii pair<int,int>

const double INF = 1e9;
const int N = 200;
vector<pair<int, double>> vs[N];
vector<vector<ll>> inf;
int n,m;
int parent[N];

void solve(int source)
{
    vector<double> dist(n, INF);
    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        double d = pq.top().first;
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto &[v, w] : vs[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
                parent[v] = u;
            }
        }
    }
}


int main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++){
        ll f,x,y;
        cin>> f>> x>> y;
        inf.push_back({f,x,y});
    }
    for (int i=0; i<m; i++){
        int a,b;
        cin>>a>>b;
        string s;
        cin>>s;
        if (s=="stairs" ||s=="walking"){
            double d = sqrt(pow(inf[a][1]-inf[b][1],2)+pow(inf[b][2]-inf[a][2],2)+pow(5*(inf[b][0]-inf[a][0]),2));
            vs[a].push_back(make_pair(b,d));
            vs[b].push_back( make_pair(a,d));
        }
        else if (s=="lift"){
            vs[a] .push_back( make_pair(b,1.));
            vs[b] .push_back( {a,1.});
        }
        else{
            double aller = 1.;
            double retour = 3*sqrt(pow(inf[a][1]-inf[b][1],2)+pow(inf[b][2]-inf[a][2],2)+pow(5*(inf[a][0]-inf[b][0]),2));
            vs[a] .push_back( {b,aller});
            vs[b] .push_back( {a,retour});
        }

    }
    int T;
    cin>>T;
    for (int i(1); i<=T; i++)
    {
        int dep,ar;
        cin>>dep>>ar;
        solve(dep);
        stack<int> chemin;
        int curr = ar;

        while(curr!=dep){
            chemin.push(curr);
            curr = parent[curr];
        }
        chemin.push(dep);
        while(!chemin.empty()){
            cout << chemin.top()<< " ";
            chemin.pop();
        }
        cout << endl;

    }
    return 0;
}