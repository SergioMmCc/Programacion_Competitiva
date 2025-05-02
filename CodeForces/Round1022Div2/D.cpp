#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
#define fi first
#define se second
typedef pair<int, int> pii;

void solver(){
    int n, k; cin>>n>>k;
    if(n == 2*k){
        cout<<"! "<<k<<' '<<k<<endl;
        return;
    }
    if(k == 1){
        cout<<"! -1"<<endl;
        return;
    }
    vector<int> a(k+1), b(k+1);
    for(int i = 1; i <= k; i++){
        cout<<"? "<<i<<endl;
        cin>>a[i];
    }

    int x = n / k;
    for(int i = 1; i <= k; i++){
        int j = x * k + i;
        if(j > n) j -= k;
        cout<<"? "<<j<<endl;
        cin>>b[i];
    }

    int c = 0;
    for(int i = 1; !c && i <= k; i++){
        // cout<<"i -> "<<i<<endl;
        // cout<<"a -> "<<a[i]<<" b -> "<<b[i]<<endl;
        if(a[i] != b[i]) c = i;
    }

    if(!c){
        cout<<"! -1"<<endl;
        return;
    }
    
    // cout<<"x -> "<<x<<" c -> "<<c<<endl;
    // Aqui el problema
    int l = 0, r = x - 1;
    int s = -1;
    while(s == -1){
        int ml = (l + r) / 2; int mr = ml + 1;

        int ans1, ans2;
        cout<<"? "<<k * ml + c<<endl;
        cin>>ans1;
        cout<<"? "<<k * mr + c<<endl;
        cin>>ans2;

        if(ans1 == ans2){
            if(ans1 == a[c]){
                l = mr;
            }
            else{
                r = ml;
            }
        }
        else{
            s = ml;
        }
    }

    // Esto tambien esta mal
    for(int i = k*s + c + 1, aux = c+1; i <= k*s + c + k; i++, aux++){
        cout<<"? "<<i<<endl;
        int ans; cin>>ans;
        int j = aux % k;
        if(!j) j += k;
        if(ans != a[j]){
            cout<<"! "<<i-1<<' '<<n - i + 1<<endl;
            return;
        }
    }
}

int main(){
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}