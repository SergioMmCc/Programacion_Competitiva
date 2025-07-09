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
    string s, t; cin>>s>>t;
    int ls = s.sz, lt = t.sz;

    if(s[0] == '1'){
        for(int i = 0; i < ls; i++){
            if(s[i] == '0') s[i] = '1';
            else s[i] = '0';
        }
    }

    int c0 = 0, c1 = 0;
    for(int i = 0; i < ls; i++){
        if(s[i] == '0') c0++;
        else c1++;
    }

    if(c0 == 0){
        cout<<0<<endl;
        return;
    }

    int ans = 0;
    for(int y = 1; y < lt; y++){
        if(((ll)lt - (ll)c1 * (ll)y) % (ll)c0) continue;
        int x = ((ll)lt - (ll)c1 * (ll)y) / (ll)c0;
        // cout<<"x -> "<<x<<" y -> "<<y<<endl;
        if(x >= lt) continue;

        bool cond = 1;
        string r0 = " ", r1 = " ";
        // Aqui el TLE
        for(int i = 0; cond && i < x; i++){
            char c = t[i];
            r0 += c;

            int next = 1, j = i + x;
            while(j < lt){
                while(next < ls && s[next] == '1'){
                    j += y;
                    next++;
                }

                if(j < lt && t[j] != c) cond = 0;
                j += x;
                next++;
            }
        }

        for(int i = 0; cond && i < y; i++){
            int next = 1, j = i + x;
            while(next < ls && s[next] == '0'){
                next++;
                j += x;
            }
            if(j >= lt){
                cond = 0;
                break;
            }
            char c = t[j];
            r1 += c;

            next++; j += y;
            while(j < lt){
                while(next < ls && s[next] == '0'){
                    j += x;
                    next++;
                }

                if(j < lt && t[j] != c) cond = 0;
                j += y;
                next++;
            }
        }

        if(cond && r0 != r1) ans++;
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