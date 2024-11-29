#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

void solver(){
    int n; cin>>n;
    set<int> numbers;
    for(int i = 1; i <= n; i++) numbers.insert(i);
    for(int i = 1; i < n; i++){
        int save; cin>>save;
        numbers.erase(save);
    }

    cout<<*numbers.begin()<<endl;
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