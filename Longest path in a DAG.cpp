#include<bits/stdc++.h>

using namespace std;

const int N = 100000;
int n;
vector<int> vs[N];
vector<bool> flag(N,false);
vector<int> destination(N,-1);
vector<int> dist(N,0);


int solve(int u0)
{
    if (flag[u0]) return dist[u0];
    int intM = -1;
    for (auto v:vs[u0]){
        int f = solve(v);
        if (f>intM){
            intM = f;
            destination[u0] = v;
        }
    }
    dist[u0] = 1+intM;
    flag[u0] = true;
    return 1+intM;
}


int main()
{
    int T;
    cin>>n>>T;
    for (int i(1); i<=T; i++)
    {
        int x,y;
        cin>>x>>y;
        vs[x-1].push_back(y-1);
    }
    int ans = -1;
    int dep = 0;
    for (int i(0); i<n; i++){
        if (flag[i]) continue;
        int temp = solve(i);
        if (ans<temp){
            ans = temp;
            dep  =i;
        }
    }
    if (ans==-1){
        cout << 1 << endl;
        cout << 1;
        return 0;
    }

    cout << ans+1 << endl;
    int curr = dep;
    while(curr!=-1){
        cout << curr+1 << " ";
        curr = destination[curr];
    }
    cout << endl;
    return 0;
}