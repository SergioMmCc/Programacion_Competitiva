// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin>>n;

    vector<int> vec(n);
    for(int i=0; i<n; i++){
        cin>>vec[i];
    }
    int maxx = *max_element(vec.begin(), vec.end());

    cout<<(maxx == vec[0]? "S" : "N")<<"\n";
}
