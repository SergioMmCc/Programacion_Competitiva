#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define db(x) cerr<< #x<<" "<<x<<endl
#define pb push_back
#define sz(a) ((int)a.size())
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define pqueue priority_queue
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<pll> vll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

pair<int, int> fx[] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

void solver(){
    int n, m;
    cin>>n>>m;

    vector<vector<int>> vec(n+3, vector<int>(m+3));
    for(int i=1; i<=n; i++)for(int j=1; j<=m; j++) cin>>vec[i][j];

    int s, f, r;
    cin>>s>>f>>r;


    for(int y=1; y<=n; y++){
        for(int x=1; x<=m; x++){
            if(vec[y][x] != s) continue;
            for(int i=0; i<4; i++){
                int ax = x + fx[i].fi;
                int ay = y + fx[i].se;
                int bx = x + fx[(i+1)%4].fi;
                int by = y + fx[(i+1)%4].se;
                if(f == vec[ay][ax] && r == vec[by][bx]){
                    cout<<y-1<<" "<<x-1<<"\n";
                    break;
                }
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}