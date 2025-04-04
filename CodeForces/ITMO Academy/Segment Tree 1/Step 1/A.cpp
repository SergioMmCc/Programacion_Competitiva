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
const int maxn = 100001;

vector<ll> tree(2 * maxn + 1);
int n;

void buildTree(vector<ll>& A){
    for (int i = 0; i < n; i++)tree[i + n] = A[i];
    for (int i = n - 1; i > 0; --i)tree[i] = tree[i << 1] + tree[(i << 1) ^ 1];
    // Si i << 1 es el hijo izquierdo, (i << 1) ^ 1 es el hijo derecho y viceversa
}

void updateTree(int update, ll value){
    tree[n + update] = value;
    update += n;
    for (int i = update; i > 1; i >>= 1) tree[i>>1] = tree[i] + tree[i ^ 1];
}

ll query(int l, int r){
    ll ans = 0;
    l += n; r += n; 
    while (l < r) {
        if (l & 1) ans += tree[l++];
        if (r & 1) ans += tree[--r];
        l >>= 1; r >>= 1;
    }
    
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int q; cin>>n>>q;
    vector<ll> a;
    for(int i = 0; i < n; i++){
        ll save; cin>>save;
        a.push_back(save);
    }
    buildTree(a);
    
    while(q--){
        int op; cin>>op;
        if(op == 1){
            int x; ll w; cin>>x>>w;
            updateTree(x, w);
        }
        else{
            int l, r; cin>>l>>r;
            cout<<query(l, r)<<endl; //La implementacion es [l, r), entonces a r no le resto 1 porque en el ejercicio si necesito incluirlo
        }
    }

    return 0;
}