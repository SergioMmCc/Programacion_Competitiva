#include <bits/stdc++.h>
using namespace std;

const int MOD = 998'244'353;
const int MAXN = 2001;
using State = bitset<MAXN>;

struct cmp {
    bool operator()(const State& a, const State& b) const {
        for(int i=MAXN-1;i>=0;i--)
            if(a[i]!=b[i])
                return a[i]<b[i];
        return false;
    }
};

void solver(){
    int n,k;cin>>n>>k;
    string s;cin>>s;
    array<State,26>v{};
    for(int i=0;i<n;i++)
        v[s[i]-'a'][i]=1;
    vector<State>st{State{}};
    vector<vector<int>>go(1);
    map<State,int,cmp>id;
    st[0][0]=1;
    id[st[0]]=0;
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int c=0;c<26;c++){
            State nx=(st[u]&v[c])<<1;
            if(nx.any())
                nx[0]=1;
            if(!nx.any())
                continue;
            if(!id.count(nx)){
                id[nx]=st.size();
                st.push_back(nx);
                go.push_back({});
                q.push(st.size()-1);
            }
            go[u].push_back(id[nx]);
        }
    }
    vector<int>dp(st.size());
    dp[0]=1;
    while(k--){
        vector<int>ndp(st.size());
        for(int i=0;i<(int)st.size();i++)
            for(int&j:go[i])
                ndp[j]=(ndp[j]+dp[i])%MOD;
        dp.swap(ndp);
    }
    int ans=0;
    for(auto&x:dp)
        ans=(ans+x)%MOD;
    cout<<ans<<"\n";
}

int main () {
  ios_base::sync_with_stdio(0);cin.tie(0);
  int t=1;cin>>t;
  while(t--)solver();
}
