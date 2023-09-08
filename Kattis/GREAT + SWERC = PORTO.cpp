#include <iostream>
using namespace std;

int n;
string words[10];
int tab[26];
bool num[10]={false};
bool zeros[26]={false};
int count = 0;

void func(int i,int carry){
    if(i==words[n-1].length()){
        if (carry ==0){
            count ++;
        }
        return;
    }
    
    int s = carry;
    for(int j=0;j<n-1;j++){
        int o = words[j].length() - 1 - i;
        if(o>=0){
            if(tab[words[j][o]-'A']==-1){
                for(int k=(zeros[words[j][o]-'A'] ? 1 : 0);k<10;k++){
                    if(num[k])  continue;
                    tab[words[j][o]-'A']=k;
                    num[k]=true;
                    func(i,carry);
                    tab[words[j][o]-'A']=-1;
                    num[k]=false;
                }
                return;
            } 
            else {
                s+=tab[words[j][o]-'A'];
            }
        }
    }
    int o = words[n-1].length() - 1 - i;
    if(tab[words[n-1][o]-'A']==-1&&!num[s%10]&&!(s%10==0&&zeros[words[n-1][o]-'A'])){
        tab[words[n-1][o]-'A']=s%10;
        num[s%10]=true;
        func(i+1,s/10);
        tab[words[n-1][o]-'A']=-1;
        num[s%10]=false;
    }
    else if (tab[words[n - 1][o] - 'A'] == s%10)
        func(i + 1,s/10);
    else
        return;
}

int main() {
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>words[i];
        zeros[words[i][0]-'A']=true;
    }
    for (int i = 0; i < 26; i++)
        tab[i] = -1;
    func(0,0);
    cout<<count;

}
