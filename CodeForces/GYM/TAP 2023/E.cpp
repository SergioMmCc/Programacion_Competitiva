// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

long long form(long long n, long long k, long long S){
    long long r = k *n*(n-1) / 2;
    if((S-r) <= 0  || (S-r) % n != 0) return -1;
    return (S-r)/n;
}

int main() {
    long long A, S, L, R;
    cin>>A>>S>>L>>R;
    if(A==S){
        cout<<1<<"\n";
        return 0;
    }

    long long ans=0;
    for(long long k=1; k<=R-L; k++){
        for(long long n=2; (n-1)*k<=(R-L); n++){
            long long a = form(n, k, S);
            if(a < L || R < a) continue;
            long long na = a + (n-1)*k;
            if (na < L || R < na) continue;
            //cout<<k<<", "<<n<<", "<<(A-a)/n<<", ["<<a<<" - "<<na<<"] -> "<<ans<<"\n";
            if(A < a || A > na || (A-a) % k != 0) continue;
            ans++;
        }
    }
    cout<<ans<<"\n";
}
