#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()

typedef pair<ld, ld> pdd;
const int maxn = 110;

bool g[maxn][maxn];
int L, R;

bool assign(int i, int matchL[], int matchR[], bool seen[]){
    for(int j = 1; j <= R; ++j) if(g[i][j] && !seen[j]){
        seen[j] = 1;
        if(matchR[j] < 0 || assign(matchR[j], matchL, matchR, seen)) return matchL[i] = j, matchR[j] = i, 1;
    }
    return 0;
}

int maxBipartiteMatching(int matchL[], int matchR[], bool seen[]){
    for(int i = 1; i <= L; ++i) matchL[i] = -1;
    for(int j = 1; j <= R; ++j) matchR[j] = -1;
    int ans = 0;
    for(int i = 1; i <= L; ++i){
        for(int j = 1; j <= R; ++j) seen[j] = 0; // or memset
        if(assign(i, matchL, matchR, seen)) ans++;
    }
    return ans;
}

void solver(int n, int m, ld s, ld v){
    L = n; R = m;
    v *= v; s *= s;
    int matchL[n+1], matchR[m+1];
    bool seen[m+1];

    // Clean Graph
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            g[i][j] = 0;
        }
    }

    vector<pdd> points1(n + 1), points2(m+1);
    for(int i = 1; i <= n; i++) cin>>points1[i].first>>points1[i].second;
    for(int i = 1; i <= m; i++) cin>>points2[i].first>>points2[i].second;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            ld distance = ((points1[i].first - points2[j].first) * (points1[i].first - points2[j].first) + 
                           (points1[i].second - points2[j].second) * (points1[i].second - points2[j].second));
            if(distance <= s * v){
                g[i][j] = 1;
            }
        }
    }
    
    int ans = n - maxBipartiteMatching(matchL, matchR, seen);
    cout<<ans<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    // cin>>t;
    int n, m; ld s, v;
    while(cin>>n>>m>>s>>v){
        solver(n, m, s, v);
    }

    return 0;
}