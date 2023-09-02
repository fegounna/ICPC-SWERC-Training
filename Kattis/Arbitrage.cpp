#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
using namespace std;

int C;
double dist[201];
vector<tuple<int, int, double>> edge;
map<string, int> tmap;

bool bellmanford() {
    for(int i = 0; i <= C; i++) {
        dist[i] = 1e9; 
    }
    dist[0] = 0.0;

    for (int t = 0; t < C; t++) {
        for (auto[u, v, c] : edge) {
            if (dist[u] + c < dist[v]) {
                dist[v] = dist[u] + c;
            }
        }
    }

    for (auto[u, v, c] : edge) {
        if(dist[u] + c < dist[v])
            return true;
    }

    return false;
}

int main() {
    while(cin >> C && C != 0) {
        edge.clear();
        tmap.clear();

        for(int i = 0; i < C; i++) {
            string s;
            cin >> s;
            tmap[s] = i + 1;
        }

        for(int i = 1; i <= C; i++) {
            edge.push_back(make_tuple(0, i, 0.0)); 
        }

        int R;
        cin >> R;

        for(int i = 0; i < R; i++) {
            string n1, n2;
            char db;
            int num1, num2;
            cin >> n1 >> n2 >> num1 >> db >> num2;
            edge.push_back(make_tuple(tmap[n1], tmap[n2], -log((double)num2 / num1)));
        }

        if (bellmanford()) {
            cout << "Arbitrage" << endl;
        } else {
            cout << "Ok" << endl;
        }
    }
}
