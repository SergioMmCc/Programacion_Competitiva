#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define db(x) cerr<< #x<<" "<<x<<endl
#define for0(i,n) for(int i = 0; i < (int)n; i++)
#define for1(i,n) for(int i = 1; i <= (int)n; i++)
#define forlr(i,l,r) for(int i = (int)l; i <= (int)r; i++)
#define forn1(i,n) for(int i = (int)n; i > 0; i--)
#define forn0(i,n) for(int i = (int)(n) - 1; i >= 0; i--)
#define forrl(i,l,r) for(int i = (int)r; i >= (int)l; i--)
#define pb push_back
#define sz(a) ((int)a.size())
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define pqueue priority_queue
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<pll> vll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

bool isNum(char c){
    return c >= '0' && c <= '9';
}
bool isLetter(char c){
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

void solver(){
    string aux; getline(cin,aux);
    int cnt = 0;
    for0(i,sz(aux)){
        cnt *= 10;
        cnt += aux[i] - '0';
    }

    bool cond = 1;
    for0(i,cnt){
        string s; getline(cin,s);
        if(!cond) continue;

        int n = sz(s);

        for0(j,n){
            if((!isLetter(s[j])) && (!isNum(s[j])) && s[j] != ' ' && s[j] != '!' && s[j] != '?' && s[j] != '.' && s[j] != ',' && s[j] != ';' && s[j] != '$' && s[j] != '#' && s[j] != '^' && s[j] != '{' && s[j] != '}' && s[j] != '_' && s[j] != '=' && s[j] != '+' && s[j] != '*'){
                cond = 0;
                break;
            }
        }
        if(!cond) continue;
        if(s[0] == ' ' || s[sz(s)-1] == ' '){
            cond = 0;
            continue;
        }
        for1(j,n-1){
            if(s[j] == ' ' && s[j-1] == ' '){
                cond = 0;
                break;
            }
        }
        if(!cond) continue;
        for0(j,sz(s)){
            int m1 = j-1, p1 = j+1;;
            if(isNum(s[j]) && ((j && !isNum(s[m1]) && !isLetter(s[m1]) && s[m1] != ' ' && s[m1] != '_' && s[m1] != '{' && s[m1] != '}' && s[m1] != '^') || (j < n-1 && !isNum(s[p1]) && !isLetter(s[p1]) && s[p1] != ' ' && s[p1] != '_' && s[p1] != '{' && s[p1] != '}' && s[p1] != '^'))){
                cond = 0;
                break;
            }
        }
        if(!cond) continue;

        for0(j,n){
            if(s[j] == '_' || s[j] == '^'){
                if(!j || j == n-1 || s[j+1] != '{'){
                    cond = 0;
                    break;
                }
                int k = j-1;
                if(!isLetter(s[k]) && !isNum(s[k])){
                    cond = 0;
                    break;
                }
                while(k >= 0 && (isNum(s[k]) || isLetter(s[k]))) k--;
                if(k >= 0 && s[k] != ' '){
                    cond = 0;
                    break;
                }
            }
            if(s[j] == '{'){
                if(!j || (s[j-1] != '_' && s[j-1] != '^') || j == n-1 || !isNum(s[j+1])){
                    cond = 0;
                    break;
                }
                int k = j+1;
                while(k < n && isNum(s[k])) k++;
                if(k == n || s[k] != '}'){
                    cond = 0;
                    break;
                }
            }
            if(s[j] == '}'){
                if(!j || !isNum(s[j-1])){
                    cond = 0;
                    break;
                }
                int k = j-1;
                while(k >= 0 && isNum(s[k])) k--;
                if(k < 0 || s[k] != '{'){
                    cond = 0;
                    break;
                }
            }
        }
        if(!cond) continue;

        for0(j,n){
            if(s[j] != '0' || (j && s[j-1] != ' ' && s[j-1] != '{') || (j == n-1 || s[j+1] == ' ' || s[j+1] == '}' || s[j+1] == '_' || s[j+1] == '^')) continue;
            int k = j;
            bool cond1 = 1;
            while(k < sz(s)){
                if(s[k] == ' ' || s[k] == '}' || s[k] == '_' || s[k] == '^') break;
                if(!isNum(s[k])){
                    cond1 = 0;
                    break;
                }

                k++;
            }
            if(cond1){
                cond = 0;
                break;
            }
        }
    }

    cout<<(cond ? "Ok" : "Validation failed")<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
