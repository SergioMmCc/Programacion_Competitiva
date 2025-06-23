#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
#define fi first
#define se second
typedef pair<int, int> pii;

const int maxn = 1e5 + 1, inf = 1000, larg = 512;
int dp[larg][maxn];

void solver(){
    int n; cin>>n;
    for(int j = 0; j <= n; j++){
        for(int i = 0; i < larg; i++){
            dp[i][j] = inf;
        }
    }

    vector<int> a(n+1);
    for(int i = 1; i <= n; i++) cin>>a[i];
    dp[0][1] = 0;
    dp[a[1]][1] = a[1];

    for(int j = 1; j < n; j++){
        int num = a[j+1];
        for(int i = 0; i < larg; i++){
            dp[i][j] = min(dp[i][j], dp[i][j-1]);

            if(num > dp[i][j]){
                int next = i ^ num;
                dp[next][j+1] = min(dp[next][j+1], a[j+1]);
            }
        }
    }

    vector<int> ans;
    for(int i = 0; i < larg; i++){
        if(dp[i][n-1] != inf || dp[i][n] != inf) ans.pb(i);
    }

    cout<<ans.sz<<endl;
    for(int i = 0; i < ans.sz; i++) cout<<ans[i]<<' ';
    cout<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}