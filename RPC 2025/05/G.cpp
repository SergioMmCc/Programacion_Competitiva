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
using i128 = __int128;
#define int i128
#define ll i128

const ll b = 31;
i128 mod = 2305843009213693951;
vector<i128> potB(27);
void calcPotB(){
    potB[0] = 1;
    for(int i = 1; i < 27; i++) potB[i] = (potB[i-1] * (i128)b) % mod;
}

ll hashFreq(vector<int>& freq){
    ll ans = 0;
    for(int i = 0; i < 27; i++) ans = ((i128)ans + (((i128)freq[i] * potB[i]) % mod)) % mod;
    return ans;
}

void calc(string a, map<ll, int>& fa){
    for(int i = 0; i < a.sz; i++){
        vector<int> freq(27);
        for(int j = i; j < a.sz; j++){
            freq[a[j] - 'a']++;
            fa[hashFreq(freq)]++;
        }
    }
}

void solver(){
    string a, b; cin>>a>>b;
    map<ll, int> fa, fb;
    // cout<<"en a -> "<<endl;
    calc(a, fa);
    // cout<<endl<<"en b -> "<<endl;
    calc(b, fb);

    ll ans = 0;
    for(auto it : fa){
        ll h = it.fi; int f = it.se;
        auto it2 = fb.find(h);
        if(it2 != fb.end()) ans += (ll)f * (ll)fb[h];
    }

    string pri = "";
    while(ans){
        pri += '0' + (ans % 10);
        ans /= 10;
    }

    reverse(pri.begin(), pri.end());
    cout<<pri<<endl;
}

#undef int
int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    calcPotB();
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}