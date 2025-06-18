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
const int maxn = 200001, mod = 1e9 + 7;

vector<int> tree(4 * maxn + 1);
int n;

void updateTree(int update, int value){
    tree[n + update] = value % mod;
    update += n;
    for (int i = update; i > 1; i >>= 1) tree[i>>1] = (tree[i] + tree[i ^ 1]) % mod; //Si i es el hijo por izquierda de i/2, entonces i ^ 1 es el hijo por derecha, y viceversa
    //i >> i -> i/2
}

// La implementacion es [l, r)
int query(int l, int r){
    int ans = 0;
    l += n; r += n; 
    while (l < r) {
        if (l & 1){
            ans += tree[l++];
            ans %= mod;
        }
        if (r & 1){
            ans += tree[--r];
            ans %= mod;
        }
        l >>= 1; r >>= 1;
    }
    
    return ans;
}

void solver(){
    cin>>n;
    vector<int> ori(n), sorted(n), a(n);
    for(int i = 0; i < n; i++) cin>>ori[i];
    sorted = ori;
    sort(sorted.begin(), sorted.end());

    // Comprimir
    int next = 0;
    map<int, int> comp;
    for(int i = 0; i < n; i++){
        if(!comp.count(sorted[i])){
            comp[sorted[i]] = next;
            next++;
        }
    }

    for(int i = 0; i < n; i++) a[i] = comp[ori[i]];

    for(int i = 0; i < n; i++){
        int add;
        if(!a[i]) add = 0;
        else add = query(0, a[i]);
        updateTree(a[i],(((query(a[i], a[i] + 1) + add) % mod) + 1) % mod);
    }

    cout<<query(0, n)<<endl;
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