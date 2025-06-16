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
    int n; cin>>n;

    vector<pii> a(n);
    set<int> sets;
    for(int i = 0; i < n; i++) cin>>a[i].fi>>a[i].se;
    sort(a.begin(), a.end());

    for(int i = 0; i < n; i++){
        int num = a[i].se;
        auto it = sets.upper_bound(num);
        if(it != sets.begin()){
            --it;
            sets.erase(it);
        }
        sets.insert(num);
    }

    cout<<sets.sz<<endl;
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