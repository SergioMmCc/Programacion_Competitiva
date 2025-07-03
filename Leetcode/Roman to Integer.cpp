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
    string s; cin>>s;
    map<char, int> t;
    t['I'] = 1;
    t['V'] = 5;
    t['X'] = 10;
    t['L'] = 50;
    t['C'] = 100;
    t['D'] = 500;
    t['M'] = 1000;

    int n = s.sz;
    int ans = 0, biggest = 0;
    for(int i = n - 1; i >= 0; i--){
        if(t[s[i]] >= biggest) ans += t[s[i]];
        else ans -= t[s[i]];
        biggest = max(biggest, t[s[i]]);
    }

    cout<<ans<<endl;
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