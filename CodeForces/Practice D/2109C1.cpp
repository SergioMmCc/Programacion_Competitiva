#include<bits/stdc++.h>
using namespace std;
// #define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
#define fi first
#define se second
typedef pair<int, int> pii;

void solver(){
    int n, ans; cin>>n;
    cout<<"digit"<<endl;
    cin>>ans;
    
    cout<<"digit"<<endl;
    cin>>ans;

    cout<<"add -8"<<endl;
    cin>>ans;

    cout<<"add -4"<<endl;
    cin>>ans;

    cout<<"add -2"<<endl;
    cin>>ans;

    cout<<"add -1"<<endl;
    cin>>ans;

    cout<<"add "<<n-1<<endl;
    cin>>ans;

    cout<<'!'<<endl;
    cin>>ans;
}

int main(){
    // ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}