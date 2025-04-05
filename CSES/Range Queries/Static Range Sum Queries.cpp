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

void solver(){
    int n, q; cin>>n>>q;
    vector<ll> a(n+1), ps(n+1);

    for(int i = 1; i <= n; i++){
        cin>>a[i];
        ps[i] = ps[i-1] + a[i];
    }

    //Queries
    while(q--){
        int l, r; cin>>l>>r;
        cout<<ps[r] - ps[l-1]<<endl;
    }
}

signed main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}