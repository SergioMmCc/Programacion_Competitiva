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
    int n, k; cin>>n>>k;
    vector<int> freq((int)1e6 + 1);

    vector<int> a(n+1);
    for(int i = 1; i <= n; i++) cin>>a[i];

    int maxi = 0, l = 0, r = 0;

    int j = 1, elements = 0;
    for(int i = 1; i <= n; i++){
        int num = a[i];
        if(!freq[num]) elements++;
        freq[num]++;

        while(elements > k){
            int num2 = a[j];
            freq[num2]--;
            if(!freq[num2]) elements--;
            j++;
        }

        int len = i - j + 1;
        if(len > maxi){
            maxi = len;
            l = j;
            r = i;
        }

    }

    cout<<l<<' '<<r<<endl;
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