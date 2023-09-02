// Online C++ compiler to run C++ program online
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

vector<int> primes;
bool is_prime(int n){
    if(n<=1)
        return false;
    for(int i=2;i<=sqrt(n);i++){
        if (n % i ==0)
            return false;
    }
    return true;
}
void primes_gen(){
    for(int i=1001;i<9999;i++){
        if(is_prime(i))
            primes.push_back(i);
    }
}
bool test(int a,int b){
    int s=0;
    if (a%10!=b%10)
        s++;
    if ((a/10)%10!=(b/10)%10)
        s++;
    if ((a/100)%10!=(b/100)%10)
        s++;
    if (a/1000!=b/1000)
        s++;
    return s==1;
}
int n;
vector<int> bfs(int u0,vector<int> vs[]) {
    vector<int> dist(n, n + 1);
    queue<int> q;
    dist[u0] = 0;
    q.push(u0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : vs[u]) if (dist[v] == n + 1) {
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    return dist;
}
int find(int p){
    for(int i=0;i<primes.size();i++){
        if(primes[i]==p)
            return i;
    }
}
int main() {
    primes_gen();
    n=primes.size();
    vector<int> vs[n];
    int C;
    cin>>C;
    for(int j=0;j<primes.size();j++){
        for(int k=j+1;k<primes.size();k++){
            if(test(primes[j],primes[k])){
                vs[j].push_back(k);
                vs[k].push_back(j);
            }
        }
    }
    for(int i=0;i<C;i++){
        int n1,n2;
        cin>>n1>>n2;
        int res = bfs(find(n1),vs)[find(n2)];
        if(res==n+1)
            cout<<"Impossible"<<endl;
        else
            cout<<res<<endl;
    }
    
}