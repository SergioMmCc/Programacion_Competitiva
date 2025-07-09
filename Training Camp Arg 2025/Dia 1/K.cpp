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
typedef pair<pii, pii> piiii;

const int maxn = 300001, ninf = -1e9;

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
    set<int> used;
    vector<int> a(n), inv(n), mini(n);
    for(int i = 0; i < n; i++){
        cin>>a[i]; a[i]--;
        inv[a[i]] = i;
    }

    for(int i = 0; i < n; i++){
        int ind = inv[i];
        auto it = used.upper_bound(ind);
        if(it == used.end()) mini[inv[i]] = n;
        else mini[inv[i]] = *it;

        used.insert(inv[i]);
    }

    // Se estan construyendo bien
    // cout<<"a ->";
    // for(int i = 0; i < n; i++) cout<<' '<<a[i];
    // cout<<endl<<"inv ->";
    // for(int i = 0; i < n; i++) cout<<' '<<inv[i];
    // cout<<endl<<"mini ->";
    // for(int i = 0; i < n; i++) cout<<' '<<mini[i];
    // cout<<endl;

    int q; cin>>q;
    vector<piiii> queries; vector<bool> ans(q);
    for(int i = 0; i < q; i++){
        int l, r; cin>>l>>r; l--; r--;
        queries.pb({{a[l], i}, {l, r}});
    }

    sort(queries.begin(), queries.end(), greater());

    // Si se estan ordenando bien
    int lastUpd = n;
    for(int i = 0; i < q; i++){
        // cout<<"a[l] -> "<<queries[i].fi.fi<<" index -> "<<queries[i].fi.se<<" l -> "<<queries[i].se.fi<<" r -> "<<queries[i].se.se<<endl;
        int j = queries[i].fi.fi, l = queries[i].se.fi, r = queries[i].se.se, index = queries[i].fi.se;
        
        while(lastUpd > j){
            updateTree(inv[j], mini[inv[j]]);
            lastUpd--;
        }

        int val = query(l, r);
        ans[index] = val > r;
    }

    for(int i = 0; i < q; i++) cout<<(ans[i] ? "Yes" : "No")<<endl;
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