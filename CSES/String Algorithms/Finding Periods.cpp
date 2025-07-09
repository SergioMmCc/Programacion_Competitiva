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

void precalc_hashing(string s, vector<ll>& h, vector<ll>& ph){
    ll p = 31;
    ll m = 1000000009LL;

    h[0] = s[0] - 'a' + 1;
    ph[0] = 1;

    for(int i = 1; i < s.sz; i++){
        h[i] = (((h[i-1] * p) % m) + (s[i] - 'a' + 1)) % m;
        ph[i] = (ph[i-1] * p) % m;
    }
}

ll queries(ll l, ll r, vector<ll>& h, vector<ll>& ph){
    ll m = 1000000009;
    if(!l) return h[r];
    return (h[r] - ((h[l-1] * ph[r-l+1]) % m) + m) % m;
}

void solver(){
    string s; cin>>s;
    int n = s.sz;
    vector<ll> h(n), ph(n);
    precalc_hashing(s, h, ph);
    for(int len = 1; len < n; len++){
        ll ori = queries(0, len - 1, h, ph);
        bool cond = 1;
        for(int l = len; cond && l < n; l += len){
            if(l + len - 1 >= n){
                int dif = n - l - 1;
                ori = queries(0, dif, h, ph);
                if(ori != queries(l, n - 1, h, ph)) cond = 0;
            }
            else if(ori != queries(l, l + len - 1, h, ph)) cond = 0;
        }

        if(cond) cout<<len<<' ';
    }

    cout<<n<<endl;
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