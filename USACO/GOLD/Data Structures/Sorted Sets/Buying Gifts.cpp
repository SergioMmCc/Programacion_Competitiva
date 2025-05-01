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

struct comp{
    bool operator() (pii a, pii b){
        if(a.fi == b.fi) return a.se > b.se;
        return a.fi < b.fi;
    }
};

void solver(){
    int n; cin>>n;
    vector<pii> a(n);
    for(int i = 0; i < n; i++) cin>>a[i].fi>>a[i].se;

    sort(a.begin(), a.end(), comp());

    vector<int> maxi(n); maxi[n-1] = a[n-1].se;
    for(int i = n - 2; i >= 0; i--) maxi[i] = max(maxi[i+1], a[i].se);

    int ans = 1e9;
    set<int> nums;
    for(int i = 0; i < n; i++){
        int use = a[i].fi;
        if(i == n-1){
            set<int>::iterator it = nums.lower_bound(use), it2 = nums.upper_bound(use);
            if(it != nums.end()) ans = min(ans, abs(use - *it));
            if(it2 != nums.begin()){
                --it2;
                ans = min(ans, abs(use - *it2));
            }

            continue;
        }

        int r = maxi[i+1], m = -1, l = -1;
        int aux = abs(r - use);

        if(r < use){
            set<int>::iterator it = nums.lower_bound(use), it2 = nums.upper_bound(use);
            if(it != nums.end()){
                m = *it;
                aux = min(aux, abs(use - m));
            }
            if(it2 != nums.begin()){
                --it2;
                l = *it2;
                aux = min(aux, abs(use - l));
            }
        }

        ans = min(ans, aux);
        nums.insert(a[i].se);
    }

    cout<<ans<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}