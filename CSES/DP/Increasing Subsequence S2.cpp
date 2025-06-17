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

const int maxn = 200001, ninf = -1e9 - 5;

// Esta implementacion es 0-index
/* 
    Para minimo simplemente cambiar los max por min y cambiar el ninf por inf
*/
vector<int> tree(4*maxn);
int n;

void buildTree(vector<int>& a){
    for(int i = 0; i < n; i++) tree[i + n] = a[i];
    for(int i = n - 1; i > 0; --i) tree[i] = max(tree[i << 1], tree[(i << 1) ^ 1]); //i << 1 -> i*2
    // Si i << 1 es el hijo izquierdo,(i << 1) ^ 1 es el hijo derecho y viceversa
}

void updateTree(int update, int value){
    tree[n + update] = value;
    update += n;
    for(int i = update; i > 1; i >>= 1) tree[i>>1] = max(tree[i], tree[i ^ 1]); //Si i es el hijo por izquierda de i/2, entonces i ^ 1 es el hijo por derecha, y viceversa
    //i >> i -> i/2
}

// La implementacion es [l, r)
int query(int l, int r){
    int ans = ninf;
    l += n; r += n; 
    while(l < r){
        if(l & 1) ans = max(ans, tree[l++]);
        if(r & 1) ans = max(ans, tree[--r]);
        l >>= 1; r >>= 1;
    }
    
    return ans;
}

void solver(){
    cin>>n;
    map<int, int> comp;
    int next = 0;
    vector<int> ori(n), sorted(n), a(n);

    for(int i = 0; i < n; i++) cin>>ori[i];
    sorted = ori;
    sort(sorted.begin(), sorted.end());

    // Comprimir
    for(int i = 0; i < n; i++){
        if(!comp.count(sorted[i])){
            comp[sorted[i]] = next;
            next++;
        }
    }
    for(int i = 0; i < n; i++) a[i] = comp[ori[i]];

    for(int i = 0; i < n; i++){
        int maxi;
        if(!a[i]) maxi = 0;
        else maxi = query(0, a[i]);
        updateTree(a[i], maxi + 1);
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