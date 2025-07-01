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
typedef pair<ll, ll> pll;
typedef pair<pll, int> plli;

const ll inf = 1e18;

void solver(){
    int n; cin>>n;
    vector<pll> ori(n);
    vector<plli> cha(n);
    for(int i = 0; i < n; i++){
        cin>>ori[i].fi>>ori[i].se;
        cha[i] = {{-ori[i].fi + ori[i].se, ori[i].fi + ori[i].se}, i};
    }

    sort(cha.begin(), cha.end());

    vector<int> parent(n, -1);
    map<ll, int> sol;
    for(int i = 0; i < n; i++){
        ll num = cha[i].fi.se;
        int index = cha[i].se, par = -1;

        auto it = sol.upper_bound(num);
        if(it != sol.begin()){
            --it;
            par = it->se;
            sol.erase(it);
        }

        parent[index] = par;
        sol[num] = index;
    }

    cout<<sol.sz<<endl;
    int carry = 1;
    vector<int> ans(n);
    for(const auto& it : sol){
        int index = it.se;
        while(index != -1){
            ans[index] = carry;
            index = parent[index];
        }

        carry++;
    }

    for(int i = 0; i < n; i++) cout<<ori[i].fi<<' '<<ori[i].se<<' '<<ans[i]<<endl;
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