#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define db(x) cerr<< #x<<" "<<x<<endl
#define for0(i,n) for(int i = 0; i < (int)n; i++)
#define for1(i,n) for(int i = 1; i <= (int)n; i++)
#define forlr(i,l,r) for(int i = (int)l; i <= (int)r; i++)
#define forn1(i,n) for(int i = (int)n; i > 0; i--)
#define forn0(i,n) for(int i = (int)(n) - 1; i >= 0; i--)
#define forrl(i,l,r) for(int i = (int)r; i >= (int)l; i--)
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

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

map<int,int> cr = {{0,1},{2,2},{4,3},{5,4},{7,5},{9,6},{10,7},{12,8},{14,9}}, cc = {{1,2},{3,3},{6,5},{8,6},{11,8},{13,9}};
vector<vi> rowres(11, vi(11)), colres(11, vi(11));
vi auxr = {2,3,5,6,8,9};

int wsq(int r, int c){
    return 3*((r-1)/3) + ((c+2)/3);
}

pii next(int r, int c){
    if(c == 9 && r == 9) return {0,0};
    if(c == 9) return {r+1, 1};
    return {r, c+1}; 
}

bool div(int uno, int otro, int res){
    if(!uno || !otro) return 1;
    return max(uno, otro) / min(uno, otro) == res;
}

bool go(int r, int c, vector<vi>& sudo, vector<vb>& row, vector<vb>& col, vector<vb>& sq){
    if(!r) return 1;
    pii n = next(r, c);
    // assert(c >= 1 && c <= 9 && r >= 1 && r <= 9);
    if(sudo[r][c]){
        return go(n.fi, n.se, sudo, row, col, sq);
    }

    for1(i,9){
        int s = wsq(r,c);
        if(s < 1 || s > 9){
            db(s);
            db(r);
            db(c);
            return 0;
        }
        
        if(row[r][i] || col[c][i] || sq[s][i]) continue;
        if((rowres[r][c]   && !div(i, sudo[r][c-1], rowres[r][c]  )) ||
           (rowres[r][c+1] && !div(i, sudo[r][c+1], rowres[r][c+1])) ||
           (colres[r][c]   && !div(i, sudo[r-1][c], colres[r][c]  )) ||
           (colres[r+1][c] && !div(i, sudo[r+1][c], colres[r+1][c]))
        ) continue;

        sudo[r][c] = i;
        row[r][i] = 1;
        col[c][i] = 1;
        sq[s][i] = 1;
        if(go(n.fi, n.se, sudo, row, col, sq)) return 1;

        sudo[r][c] = 0;
        row[r][i] = 0;
        col[c][i] = 0;
        sq[s][i] = 0;
    }

    return 0;
}

void solver(){
    int k; cin>>k;
    for0(i,15){
        if(cr.find(i) != cr.end()){
            for(int x : auxr) cin>>rowres[cr[i]][x];
        }
        else{
            for1(j,9) cin>>colres[cc[i]][j];
        }
    }

    vector<vi> sudo(11, vi(11));
    vector<vb> col(11, vb(11)), row(11, vb(11)), sq(11, vb(11));
    for0(i,k){
        int r, c, num; cin>>r>>c>>num;
        sudo[r][c] = num;
        row[r][num] = 1;
        col[c][num] = 1;
        sq[wsq(r,c)][num] = 1;
    }

    go(1, 1, sudo, row, col, sq);
    for1(i,9){
        for1(j,9){
            if(j > 1) cout<<' ';
            cout<<sudo[i][j];
        }
        cout<<endl;
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
