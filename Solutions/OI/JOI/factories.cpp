#include "factories.h"
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

//#define int long long

template<class T> struct RMQ { // floor(log_2(x))
  int level(int x) { return 31-__builtin_clz(x); } 
  vector<T> v; vector<vi> jmp;
  int comb(int a, int b) { // index of min
    return v[a]==v[b]?min(a,b):(v[a]<v[b]?a:b); } 
  void init(const vector<T>& _v) {
    v = _v; jmp = {vi(sz(v))}; iota(all(jmp[0]),0);
    for (int j = 1; 1<<j <= sz(v); ++j) {
      jmp.pb(vi(sz(v)-(1<<j)+1));
      rep(i,0,sz(jmp[j])) jmp[j][i] = comb(jmp[j-1][i],
                  jmp[j-1][i+(1<<(j-1))]);
    }
  }
  int index(int l, int r) { // get index of min element
    int d = level(r-l+1);
    return comb(jmp[d][l],jmp[d][r-(1<<d)+1]); }
  T query(int l, int r) { return v[index(l,r)]; }
};
const int MAXL = 21;
const ll inf = 1e18;

struct Tree{
  int n;
  vector<vector<pii> > g;
  vi pos,tin,tout,vis,tam,del,pai,hi;
  vector<ll> H,best;
  vector<pii> temp;
  Tree(){}
  int T;
  vi ans[MAXL];
  void init(int _n){
    T=0;
    n = _n;
    g.resize(n+1);
    best = H = vector<ll>(n+1);
    hi = pai = del = vis = tam = pos = tin = tout = vi(n+1);
    rep(i,0,MAXL)ans[i].resize(n+1);
  }
  RMQ<pii> rmq;
  void addEdge(int a,int b,int c){
    g[a].pb(pii(b,c));
    g[b].pb(pii(a,c));
  }
  void dfs(int v,int p = -1){
    pos[v] = sz(temp);
    tin[v] = ++T;
    temp.pb(pii(hi[v],v));
    trav(to,g[v])if(to.ff!=p){
      
      H[to.ff] = H[v] + to.ss;
      hi[to.ff] = hi[v] + 1;
      ans[0][to.ff] = v;
      dfs(to.ff,v);
      temp.pb(pii(hi[v],v));
    }
    tout[v] = T;
  }
  void gen(int Root){
    ans[0][Root] = Root;
    temp.clear();
    dfs(Root);
    rmq.init(temp);
    
    rep(j,1,MAXL){
      rep(i,0,n+1){
        ans[j][i] = ans[j-1][ans[j-1][i]];
      }
    }

    decompose(Root);
  }
  int lca(int a,int b){
    a = pos[a],b = pos[b];
    if(a > b)swap(a,b);
    return rmq.query(a,b).ss;
  }
  ll dist(int a,int b){
    return H[a] + H[b] - 2*H[lca(a,b)];
  }
  int calc_sz(int v,int p = -1){
  	tam[v] = 1;
  	for(auto to : g[v])if(to.ff!=p and !del[to.ff]){
  		tam[v]+=calc_sz(to.ff,v);
  	}
  	return tam[v];
  }
  int find_centroid(int v,int p,int Sz){
  	for(auto to : g[v])if(to.ff!=p and !del[to.ff]){
  		if(tam[to.ff]*2 > Sz)return find_centroid(to.ff,v,Sz);
  	}
  	return v;
  }
  void decompose(int v,int p = -1){
  	int Sz = calc_sz(v,-1);
  	int cent = find_centroid(v,-1,Sz);
  	pai[cent] = p;
  	del[cent] = 1;
  	for(auto to : g[cent]){
  		if(del[to.ff])continue;
  		decompose(to.ff,cent);
  	}
  }
  int CT = 0;
  void add(int x){
  	int c = x;
  	while(c!=-1){
  		if(vis[c] != CT){
  			vis[c] = CT;
  			best[c] = inf;
  		}
  		best[c] = min(best[c],dist(x,c));
  		c = pai[c];
  	}
  }
  ll query(int x){
  	ll res = inf;
  	int c = x;
  	while(c!=-1){
  		if(vis[c] == CT){
  			res = min(res,best[c] + dist(x,c));
  		}
  		c = pai[c];
  	}
  	return res;
  }
}tree;

void Init(int32_t N, int32_t A[], int32_t B[], int32_t D[]) {
	tree.init(N);
	for(int i=0;i<N-1;i++){
		tree.addEdge(A[i],B[i],D[i]);
	}
	tree.gen(0);
}

long long Query(int32_t S, int32_t X[], int32_t T, int32_t Y[]) {
  tree.CT++;
  for(int i=0;i<S;i++)tree.add(X[i]);
  ll res = inf;
  for(int i=0;i<T;i++)res = min(res,tree.query(Y[i]));	
  assert(res!=inf);
  return res;
}
