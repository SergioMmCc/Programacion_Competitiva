// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    int B, L;
    cin>>B>>L;

    vector<int> dig(L+1);
    int val=0;
    for(int i=1; i<=L; i++){
        cin>>dig[i];
        val = val + dig[i] * (((i%2) == (L%2))? 1 : -1) + B+1;
        val %= B+1;
    }

    if(val == 0){
        cout<<"0 0\n";
        return 0;
    }

    //cout<<val<<" | "<<((L % 2 == 0)+1)<<" *\n";
    for(int i=1; i<=L; i++){
        int x = -1;

        if(i%2 == L%2){
            x = (dig[i] - val + B+1) % (B+1);
        }else{
            x = (dig[i] + val) % (B+1);
        }

        if(x < dig[i]){
            cout<<i<<" "<<x<<"\n";
            return 0;
        }
    }

    cout<<"-1 -1\n";
}
