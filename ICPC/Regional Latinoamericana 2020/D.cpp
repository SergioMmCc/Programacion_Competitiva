#include <bits/stdc++.h>
using namespace std;

void solver() {
	int n;cin>>n;
	multiset<int>st;
	for(int i=0;i<n;i++){
	    int x;cin>>x;
	    st.insert(x);
	}
	int ans=0;
	while(st.size()>=2){
	    int x=*st.begin();st.erase(st.begin());
	    int y=*st.begin();
	    if(x==y){
	        st.erase(st.begin());
	        st.insert(y+1);
	    } else
	        ans++;
	}
	if(ans>=2 || n==1)
	    cout<<"N\n";
	else 
	    cout<<"Y\n";
}


int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t=1;//cin>>t;
	while(t--)solver();
}