#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

#define N  10000
#define INF  1e9

int j=0;
int b;

struct edge{
    int des;
    int weight;
    int pres;
};

vector<edge> graph[N];
bool indegree[N] = {false};
int prix[N];
int pres[N]={0};
stack<int> Stack;

void dfs(int v,bool visited[],stack<int> &Stack){
    visited[v] = true;
    for(edge &e:graph[v]){
        if(!visited[e.des]){
            dfs(e.des,visited,Stack);
        }
    }
    Stack.push(v);
}

void topologicalSort(){
    bool visited[N]={false};
    for(int i =0;i<j;i++)
        if(!visited[i])
            dfs(i,visited,Stack);
}

void weights(){
    while(!Stack.empty()){
        int v = Stack.top();
        Stack.pop();
        if (!indegree[v]) {
            prix[v] = 0;
            pres[v] = 0;
        }
        for(edge e : graph[v]){
            int p = prix[v]+e.weight;
            int pr = pres[v]+e.pres;
            if( p < prix[e.des] ||(prix[e.des]==p&&pres[e.des]<pr)){
                pres[e.des] = pr;
                prix[e.des] =  p;
            }
        }
    }
}

void dynamic(){
     int dp[j+1][b+1];
     for(int i=0;i<=j;i++){
         for(int w=0;w<=b;w++){
             if(i==0||w==0)
                dp[i][w]=0;
            else if(prix[i-1]<=w)
                dp[i][w] = max (dp[i-1][w-prix[i-1]]+pres[i-1],dp[i-1][w]);
            else
                dp[i][w] = dp[i-1][w];
         }
     }
     int res = dp[j][b];
     int w = b;
     int s=0;
     for(int i=j;i>0 && res >0;i--){
         if(res!=dp[i-1][w]){
             s+= prix[i-1];
             res -= pres[i-1];
             w -= prix[i-1];
         }
     }
     cout<<dp[j][b]<<endl<<s;
 }

int main() {
    int n;
    cin>>b>>n;
    unordered_map<string,int> m;
    for(int i =0;i<n;i++){
        string s1,s2,ingredient;
        int p,pr;
        cin>>s2>>s1>>ingredient>>p>>pr;
        if(m.find(s1)==m.end()){
            m[s1]=j;
            prix[j]=INF;
            j++;
        }
        if(m.find(s2)==m.end()){
            m[s2]=j;
            prix[j]=INF;
            j++;
        }
        edge e;
        e.des = m[s2];
        e.weight = p;
        e.pres = pr;
        graph[m[s1]].push_back(e);
        indegree[m[s2]]=true;
    }
    topologicalSort();
    weights();
    dynamic();
}
