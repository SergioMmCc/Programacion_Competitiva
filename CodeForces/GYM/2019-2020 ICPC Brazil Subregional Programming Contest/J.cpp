#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using ld=long double;
using pli=pair<ll,int>;
using vi=vector<int>;
#define F first
#define S second
#define PB push_back
#define all(x) x.begin(),x.end()

const string ORDER="A23456789DQJK";

void solver(){
    int n,k;cin>>n>>k;k--;
    vector<vi>hand(n,vi(13,0));
    vector<bool>wild(n,false),locked(n,false);
    wild[k]=locked[k]=true;
    for(auto&h:hand){
        string s;cin>>s;
        for(char c:s)
            h[ORDER.find(c)]++;
    }
    int u=k;
    while(true){
        int win=1e9;
        for(int i=0;i<n;i++){
            if(wild[i])continue;
            for(int cnt:hand[i])
                if(cnt==4) 
                    win=min(win,i);
        }
        if(win!=1e9){
            cout<<win+1<<"\n";
            return;
        }
        int pass_card=-1,min_cnt=1e9;
        bool pass_wild=false;
        if(wild[u] && !locked[u])
            pass_wild=true;
        if(!pass_wild){
            for(int c=0;c<13;c++){
                if(0<hand[u][c] && hand[u][c]<min_cnt){
                    min_cnt=hand[u][c];
                    pass_card=c;
                }
            }
        }
        int v=(u+1)%n;
        locked[u]=false; 
        if(pass_wild){
            wild[u]=false;
            wild[v]=locked[v]=true;
        }else{
            hand[u][pass_card]--;
            hand[v][pass_card]++;
        }
        u=v;
    }
}

int main () {
    cin.tie(0)->sync_with_stdio(0);
    int t=1;//cin>>t;
    while(t--)solver();
}