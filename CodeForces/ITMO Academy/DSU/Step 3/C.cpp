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

/*
- 1-index.
- Complejidad: O(Q*log(Q)*log(n)) tiempo, O(n + Q) memoria 
  (Q = operaciones).
- No maneja aristas repetidas.
- Dynamic connectivity offline: se guardan todas las operaciones
  de agregar arista, borrar arista y las queries.
  process() responde las consultas en orden.
  * add(u, v): agrega la arista u->v (no debe estar ya presente).
  * remove(u, v): borra la arista u->v (debe estar presente).
  * query(): imprime el numero de componentes en ese momento.
    + Si se quiere otro tipo de consulta, se debe cambiar la 
      informacion que se esta imprimiendo en el primer if dentro 
      de la funcion "go".
    + Asi mismo, se podrian hacer varios tipos de queries, 
      agregando las necesarias en "enum" y en el primer if de la 
      funcion "go".
    + Si se quieren queries que pregunten informacion de algun 
      nodo o par de nodos, se cambia "query()" por "query(u)" o 
      "query(u, v)".
- mt[i] es el emparejamiento de la operacion i:
  * ADD: indice de su DEL (operacion en que se elimina) (sz(q) si 
    nunca se elimina)
  * DEL: indice de su ADD (operacion en que se agrega)
  * QUERY: -1.
- go(s, e) al entrar, el DSU ya tiene todas las aristas vivas 
  durante todo el rango [s, e). Para cada mitad [s, m) y [m, e)
  (con m = (s+e)/2) se agregan las aristas que cubren esa mitad 
  completa (y no todo [s, e)), se hacen los llamados recursivos 
  a cada mitad y se hace rollback.
*/

struct DSURollback {
    vi p, len;
    stack<pii> st; stack<int> save;
    int comps;

    DSURollback(int n) : p(n), len(n, 1), comps(n-1) { iota(all(p), 0); }
    int find(int x){
        while(p[x] != x) x = p[x];
        return x;
    }
    bool join(int a, int b){
        a = find(a); b = find(b);
        if(a == b) return 0;
        if(len[a] < len[b]) swap(a, b);
        p[b] = a; len[a] += len[b]; comps--;
        st.push({a, b});
        return 1;
    }
    void checkpoint() { save.push(sz(st)); }
    void rollback(){ // deshace hasta el ultimo checkpoint
        if(save.empty()) save.push(0); // Si no habia checkpoint, borrar todo
        while(sz(st) > save.top()){
            auto [a, b] = st.top(); st.pop();
            len[a] -= len[b]; p[b] = b; comps++;
        }
        save.pop();
    }
};

enum {ADD, DEL, QUERY}; // Agregar mas operaciones de consulta de ser necesario
struct Query { int type, u, v; };

struct DynCon {
    vector<Query> q; DSURollback uf;
    vi mt; map<pii,int> prv;
    DynCon(int n) : uf(n+1) {}
    void add(int u, int v){
        if(u > v) swap(u, v);
        q.pb({ADD, u, v}); mt.pb(-1);
        prv[{u, v}] = sz(q)-1;
    }
    void remove(int u, int v){
        if(u > v) swap(u, v);
        q.pb({DEL, u, v});
        int pr = prv[{u, v}];
        mt[pr] = sz(q)-1; mt.pb(pr);
    }
    void query(){ q.pb({QUERY, -1, -1}); mt.pb(-1); } // Agregar parametros nodos de ser necesario
    void process(){ // responde todas las consultas en orden
        if(!sz(q)) return;
        for0(i,sz(q)) if(q[i].type == ADD && mt[i] < 0) mt[i] = sz(q);
        go(0, sz(q));
    }
    void go(int s, int e){
        if(s+1 == e){
            if(q[s].type == QUERY) cout<<uf.comps<<endl; // Cambiar la operacion de ser necesario
            return;
        }
        int m = (s+e)/2;

        uf.checkpoint();
        forlr(i,m,e-1) if(mt[i] >= 0 && mt[i] < s) uf.join(q[i].u, q[i].v);
        go(s, m);
        uf.rollback();

        uf.checkpoint();
        forlr(i,s,m-1) if(mt[i] >= e) uf.join(q[i].u, q[i].v);
        go(m, e);
        uf.rollback();
    }
};

void solver(){
    // Crear
    int n, q; cin>>n>>q;
    DynCon dc(n);
    for0(i,q){
        char c; cin>>c;
        if(c == '+'){ int u, v; cin>>u>>v; dc.add(u, v); } // Agregar arista
        else if(c == '-'){ int u, v; cin>>u>>v; dc.remove(u, v); } // Eliminar arista
        else dc.query(); // Consultar el numero de componentes
    }
    dc.process(); // Procesar
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