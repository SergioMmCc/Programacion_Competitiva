#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

void solver() {
    ll n, a, b, x;
    cin>>n>>a>>b>>x;
    ld nu = (ld)n, au = (ld)a, bu = (ld)b, xu = (ld)x;
    ld ans = nu * (au * 0.5 + bu * 0.5 + xu * 0.2);
    cout<<fixed<<setprecision(4)<<ans<<endl;
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