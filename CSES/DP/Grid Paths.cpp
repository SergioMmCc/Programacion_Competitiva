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

const int mod = 1e9 + 7;

void solver(){
    int n; cin>>n;
    vector<string> maze(n);
    for(int i = 0; i < n; i++) cin>>maze[i];
    if(maze[0][0] == '*'){
        cout<<0<<endl;
        return;
    }

    vector<vector<int>> dp(n, vector<int>(n));
    dp[0][0] = 1;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(maze[i][j] == '*') continue;
            if(i < n - 1 && maze[i+1][j] != '*'){
                dp[i+1][j] += dp[i][j];
                dp[i+1][j] %= mod;
            }
            if(j < n - 1 && maze[i][j+1] != '*'){
                dp[i][j+1] += dp[i][j];
                dp[i][j+1] %= mod;
            }
        }
    }

    cout<<dp[n-1][n-1]<<endl;
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