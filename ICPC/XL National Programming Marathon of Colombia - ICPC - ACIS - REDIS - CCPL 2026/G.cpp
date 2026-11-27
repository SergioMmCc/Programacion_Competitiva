#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define for0(i,n) for(int i = 0; i < (int)n; i++)
#define for1(i,n) for(int i = 1; i <= (int)n; i++)
#define forn0(i,n) for(int i = (int)n-1; i >= 0; i--)
#define forn1(i,n) for(int i = (int)n; i > 0; i--)
#define pb push_back
#define sz(a) (int)a.size()
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vii;

void solver(ll b, int n){
    vl a(n);
    for0(i,n) cin>>a[i];

    int ans = 0;
    priority_queue<ll, vl, greater<ll>> pq;
    for(int i = n-1; i >= 0; i--){
        int j = i;
        while(j >= 0 && a[j] <= 0){
            pq.push(-a[j]);
            j--;
        }

        if(j < 0) break;

        ll bud = a[j];
        while(!pq.empty() && pq.top() <= bud){
            // cout<<"ans -> "<<ans<<" top -> "<<pq.top()<<" bud -> "<<bud<<endl;
            ans++;
            bud -= pq.top();
            pq.pop();
        }
        if(bud > 0 && !pq.empty()){
            ll x = pq.top();
            pq.pop();
            x -= bud;
            pq.push(x);
        }

        i = j;
    }

    while(!pq.empty() && pq.top() <= b){
        ans++;
        b -= pq.top();
        pq.pop();
    }

    cout<<ans<<endl;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    ll b; int n;
    while(cin>>b>>n){
        if(!n) break;
        solver(b, n);
    }

    return 0;
}