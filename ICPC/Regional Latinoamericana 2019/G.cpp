#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using vi=vector<int>;
#define F first
#define S second
#define PB push_back
#define all(x) x.begin(),x.end()

vector<int> sa, lcp, rnk;

void build_sa(const auto& s, int lim = 256) {
    int n = size(s) + 1, k = 0, a, b;
    vector<int> x(begin(s), end(s)), y(n), ws(max(n, lim));
    x.PB(0);
    sa = lcp = rnk = y;
    iota(all(sa), 0);
    for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
        p = j;
        iota(all(y), n - j);
        for (int i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
        fill(ws.begin(), ws.begin() + lim, 0);
        for (int i = 0; i < n; ++i) ws[x[i]]++;
        for (int i = 1; i < lim; ++i) ws[i] += ws[i - 1];
        for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
        swap(x, y);
        p = 1, x[sa[0]] = 0;
        for (int i = 1; i < n; ++i) {
            a = sa[i - 1], b = sa[i];
            x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        }
    }
    for (int i = 0; i < n; ++i) rnk[sa[i]] = i;
    for (int i = 0, j; i < n - 1; lcp[rnk[i++]] = k)
        for (k && k--, j = sa[rnk[i] - 1]; max(i, j) + k < n - 1 && s[i + k] == s[j + k]; k++);
}

int get_lcp(const string&C,int c_idx,const string&T,int t_idx) {
    int l=0;
    int len_c=C.size()-c_idx;
    int len_t=T.size()-t_idx;
    int mn=min(len_c,len_t);
    while(l<mn && C[c_idx+l]==T[t_idx+l])l++;
    return l;
}

bool check(const string&C,int c_idx,const string&T,int t_idx) {
    int len_c=C.size()-c_idx;
    int len_t=T.size()-t_idx;
    int mn = min(len_c, len_t);
    for(int i=0;i<mn;i++){
        if(C[c_idx+i]!=T[t_idx+i]){
            return C[c_idx+i]>T[t_idx+i];
        }
    }
    return len_c>=len_t;
}

void solver() {
    string C;cin>>C;
    build_sa(C);
    int n; cin>>n;
    while(n--){
        string T;cin>>T;
        int ans=0,j=0;
        bool ok=true;
        while(j<T.size()){
            int l=1,r=(int)sa.size()-1,pos=sa.size();
            while(l<=r){
                int m=midpoint(l, r);
                if(check(C,sa[m],T,j)){
                    pos=m;
                    r=m-1;
                }else{
                    l=m+1;
                }
            }
            int mx=0;
            if(pos<sa.size())mx=max(mx,get_lcp(C,sa[pos],T,j));
            if(pos-1>=1)mx=max(mx,get_lcp(C,sa[pos-1],T,j));
            if(!mx){
                ok=false;
                break;
            }
            j+=mx;
            ans++;
        }
        if(ok)cout<<ans<<"\n";
        else cout<<"-1\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t=1; // cin>>t;
    while(t--) solver();
}