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

int mcd(int a, int b){
    int temp;
    while (b != 0){
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void solver(){
    int n, p; cin>>n>>p;
    vector<int> a(n+1), edges(n, p); // edge[i] -> weight i <-> i+1
    for(int i = 1; i <= n; i++) cin>>a[i];

    // Recorrer hacia adelante
    for(int i = 1; i < n; i++){
        int mini = a[i], gcdi = a[i];
        int j;
        for(j = i+1; j <= n; j++){
            int last = mini;
            mini = min(mini, a[j]);
            gcdi = mcd(gcdi, a[j]);
            if(mini != gcdi){
                mini = last;
                j--;
                break;
            }
        }
        for(int k = i; k < j && k < n; k++) edges[k] = min(mini, edges[k]);
        i = j;
    }

    // Recorrer hacia atras
    for(int i = n; i > 1; i--){
        int mini = a[i], gcdi = a[i];

        int j;
        for(j = i-1; j > 0; j--){
            int last = mini;
            mini = min(mini, a[j]);
            gcdi = gcd(gcdi, a[j]);
            if(mini != gcdi){
                mini = last;
                j++;
                break;
            }
        }
        for(int k = i; k > j && k > 0; k--) edges[k-1] = min(mini, edges[k-1]);
        i = j;
    }

    ll ans = 0;
    for(int i = 1; i < n; i++) ans += (ll)edges[i];
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