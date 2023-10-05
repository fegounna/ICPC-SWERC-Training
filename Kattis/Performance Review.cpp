#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ii pair<int,int>
#define v vector<int>
#define vii vector<ii>
#define ll long long
#define pb push_back
#define all(x) (x).begin(),(x).end()


ll st[524288],ans[100005];
int tab[100005],T[100005],to_idx[100005],sub[100005];
v vec[100005],pre;
vii to_ord;

void update(int node,int l,int r,int val,int idx){
    if(l==r){
        st[node]+=val;
        return;
    }
    int med=(l+r)/2;
    if(idx<=med)
        update(node*2,l,med,val,idx);
    else
        update(node*2+1,med+1,r,val,idx);
    st[node]=st[node*2]+st[node*2+1];
}

ll query(int node,int l,int r,int L,int R){
    int med=(l+r)/2;
    if(L<=l && R>=r)
        return st[node];
    else if(L>r || R<l)
        return 0;
    return query(node*2,l,med,L,R)+query(node*2+1,med+1,r,L,R);


}

void dfs(int node,int parent){
    to_idx[node]=pre.size();
    pre.pb(node);
    sub[node]=1;
    for (auto it:vec[node])
        if(it!=parent){
            dfs(it,node);
            sub[node]+=sub[it];
        }

}

int32_t main(){
    int E,p,r,curr,paren,rank;
    cin>>E;
    for (int i = 0; i < E; ++i)
    {
        cin>>p>>r>>T[i];
        if(p==-1){
            paren=i;
            to_ord.pb({r,i});
            continue;
        }
        p--;
        vec[p].pb(i);
        vec[i].pb(p);
        to_ord.pb({r,i});
    }
    sort(all(to_ord));
    dfs(paren,-1);
    for (int i = 0; i < E;)
    {
        v to_pro;
        curr=to_ord[i].se;
        rank=to_ord[i].fi;
        ans[curr]=query(1,0,E-1,to_idx[curr],to_idx[curr]+sub[curr]-1);
        to_pro.pb(curr);
        i++;
        while(i<E && to_ord[i].fi==rank){
            curr=to_ord[i].se;
            ans[curr]=query(1,0,E-1,to_idx[curr],to_idx[curr]+sub[curr]-1);
            to_pro.pb(curr);
            i++;
        }
        for (auto it:to_pro)
            update(1,0,E-1,T[it],to_idx[it]);
    }
    for (int i = 0; i < E; ++i)
        cout<<ans[i]<<"\n";
    return 0;
}
