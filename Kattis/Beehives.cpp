#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    double d;
    cin>>d>>n;
    while(n!=0||d!=0.0){
        pair<double,double> vv[n];
        for(int i =0;i<n;i++){
            double x,y;
            cin>>x>>y;
            vv[i]={x,y};
        }
        int sour =0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i==j)
                    continue;
                if( pow(vv[i].first-vv[j].first,2)+pow(vv[i].second-vv[j].second,2) <=d*d){
                    sour++;
                    break;
                }
            }
        }
        cout << sour << " sour, "<<n-sour<<" sweet"<<endl;
        cin>>d>>n;
    }
}
