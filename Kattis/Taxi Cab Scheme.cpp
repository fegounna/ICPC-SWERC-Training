#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; 

const int NL = 500;
const int NR = 500;

vector<int> vs[NL]; 
int lmatch[NL];
int rmatch[NR];
int visited[NR], iter;

bool dfs(int u) {
    if (visited[u] < iter) {
        visited[u] = iter;
        for (int v : vs[u]) {
            if (rmatch[v] == -1 || dfs(rmatch[v])) {
                lmatch[u] = v;
                rmatch[v] = u;
                return true;
            }
        }
    }
    return false;
}

int maxmatching(int nl,int nr) {
    fill(lmatch, lmatch + nl, -1);
    fill(rmatch, rmatch + nr, -1);
    fill(visited, visited + nr, 0);
    iter = 1;
    int m = 0, dm = 1;
    while (dm > 0) {
        dm = 0;
        iter++;
        for (int u = 0; u < nl; u++)
            if (lmatch[u] == -1)
                dm += dfs(u);
        m += dm;
    }
    return m;
}
struct taxi{
  int hour;
  int min;
  int a;
  int b;
  int c;
  int d;
};
int main() {
    int N;
    cin >> N;
    for(int i=0;i<N;i++){
        int nl;
        cin>>nl;
        taxi tab[nl];
        for(int j=0;j<nl;j++){
            int hour,min,a,b,c,d;
            char dp;
            cin>>hour>>dp>>min>>a>>b>>c>>d;
            tab[j].hour=hour;
            tab[j].min=min;
            tab[j].a=a;
            tab[j].b=b;
            tab[j].c=c;
            tab[j].d=d;
        }
        for(int j=0;j<nl;j++){
            int duration = abs(tab[j].c-tab[j].a)-abs(tab[j].d-tab[j].b);
            int fin = tab[j].hour*60+tab[j].min+duration;
            for(int k=j+1;k<nl;k++){
                int debut = tab[k].hour*60+tab[k].min;
                if( debut - abs(tab[j].c-tab[k].a)-abs(tab[j].d-tab[k].b)-fin >=1){
                    vs[j].push_back(k);
                }
            }
        }
        cout<<nl-maxmatching(nl,nl)<<endl;
        for(int i = 0; i < NL; i++) {
            vs[i].clear();
        }

    }



}
