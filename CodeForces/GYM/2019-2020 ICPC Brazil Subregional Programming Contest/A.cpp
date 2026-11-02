// Source: https://usaco.guide/general/io

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


struct P{
    int x, y;

    int dist(P o){
        return (x-o.x)*(x-o.x) + (y-o.y)*(y-o.y);
    }
};
struct C{
    P p;
    int r;
};

struct DSU {
    vi p, len; int comp; // p es el lider de cada nodo
    DSU(int n) : p(n), len(n, 1), comp(n-1) { iota(all(p), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool join(int a, int b){
        if((a = find(a)) == (b = find(b))) return 0;
        if(len[a] < len[b]) swap(a, b);
        p[b] = a; len[a] += len[b]; --comp;
        return 1;
    }
};

int n, m;

bool intersect(C a, C b){
    return a.p.dist(b.p) <= (a.r+b.r)*(a.r+b.r);
}

bool interDown(C a){ return a.p.y - a.r <= 0;}
bool interUp(C a){ return a.p.y + a.r >= n;}
bool interLeft(C a){ return a.p.x - a.r <= 0;}
bool interRight(C a){ return a.p.x + a.r >= m;}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int k;
    cin>>m>>n>>k;

    int UP=k;
    int DOWN=k+1;
    int LEFT=k+2;
    int RIGHT=k+3;

    DSU map(k + 4);
    vector<C> pts(k);
    for(int i=0; i<k; i++){
        cin>>pts[i].p.x>>pts[i].p.y>>pts[i].r;
        if(interDown(pts[i])) map.join(i, DOWN);
        if(interUp(pts[i])) map.join(i, UP);
        if(interLeft(pts[i])) map.join(i, LEFT);
        if(interRight(pts[i])) map.join(i, RIGHT);
    }


    for(int i=0; i<k; i++){
        for(int j=i+1; j<k; j++){
            if(intersect(pts[i], pts[j])){
                map.join(i, j);
            }
        }
    }

    bool flag = 
                map.find(LEFT) == map.find(DOWN) || 
                map.find(LEFT) == map.find(RIGHT) || 
                map.find(UP) == map.find(DOWN) || 
                map.find(UP) == map.find(RIGHT);

    cout<<(!flag? "S" : "N")<<"\n";

}
