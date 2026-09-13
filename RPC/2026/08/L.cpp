// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int main() {
    int n, a, b;
    cin>>n>>a>>b;
    vector<int> vec(n-1);
    for(int i=0; i<n-1; i++){
        cin>>vec[i];
    }

    sort(vec.begin(), vec.end());

    if(vec[0] == a && vec.back() == b){
        for(int i=a; i<=b; i++){
            cout<<i<<" \n"[i==b];
        }
    }else if(vec[0] == a){
        cout<<b<<"\n";
    }else if(vec.back() == b){
        cout<<a<<"\n";
    }else{
        cout<<"-1\n";
    }
}
