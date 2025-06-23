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

const int inf = 1e9;

void solver(){
    int n; cin>>n;
    map<int, int> c;
    for(int i = 1; i <= n; i++){
        int save; cin>>save;
        c[save] = i;
    }

    vector<int> a(n);
    for(int i = 0; i < n; i++){
        int save; cin>>save;
        a[i] = c[save];
    }

    // Hallar el LIS
    vector<int> d(n+1, inf); d[0] = -inf;
    for(int i = 0; i < n; i++){
        auto it = upper_bound(d.begin(), d.end(), a[i]);
        if(it == d.end()) continue;
        int index = it - d.begin();
        if(d[index-1] < a[i]) d[index] = a[i];
    }

    int l = 0;
    for(int i = 1; i <= n; i++){
        if(d[i] != inf) l = i;
    }

    cout<<l<<endl;
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