#include <bits/stdc++.h>
using namespace std;

vector<int> sa, lcp, rnk;

void build_sa(const auto& s, int lim = 256) {
    int n = size(s) + 1, k = 0, a, b;
    vector<int> x(begin(s), end(s)), y(n), ws(max(n, lim));
    x.push_back(0);
    sa = lcp = rnk = y;
    iota(begin(sa), end(sa), 0);
    for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
        p = j;
        iota(begin(y), end(y), n - j);
        for (int i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
        fill(begin(ws), begin(ws) + lim, 0);
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


void solver() {
    int n,m;cin>>n>>m;
    string s,w;cin>>s;
    vector<int>t;
    for(char c:s+s)
        t.push_back(c-'a'+1);
    int sep=27;
    t.push_back(sep++);
    while(m--){
        cin>>w;
        for(char c:w)
            t.push_back(c-'a'+1);
        t.push_back(sep++);
    }
    int sz=t.size();
    build_sa(t,sep);
    vector<int>match(n);
    for (int i=1,cur=0;i<=sz;i++) {
        cur=(sa[i]>=2*n) ? n : min(cur,lcp[i]);
        if(sa[i]<n)
            match[sa[i]]=max(match[sa[i]],cur);
    }
    for (int i=sz,cur=0;i>=1;i--) {
        if(sa[i]<n)
            match[sa[i]]=max(match[sa[i]],cur);
        cur=min(lcp[i],(sa[i]>=2*n) ? n : cur);
    }
    int ans=n,bad=-1;
    vector<int>last(n+1,-1);
    for (int i=0;i<2*n;i++) {
        int x=match[i%n];
        last[x]=i;
        if(x>=ans)bad=i;
        if(ans && i-bad>=n-ans+1)
            bad=max(bad,last[--ans]);
    }
    cout<<ans<<"\n";
}

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solver();
}