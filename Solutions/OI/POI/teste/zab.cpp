#include <bits/stdc++.h>
#define ld long double
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb(x) push_back(x)
#define mp(a,b) make_pair(a,b)
#define ms(v,x) memset(v,x,sizeof(v))
#define all(v) v.begin(),v.end()
#define ff first
#define ss second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define Unique(v) sort(all(v));v.erase(unique(all(v)),v.end());
#define sz(v) (int)v.size()
//#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left sefude
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl; 
#define prl cerr<<"called: "<< __LINE__ << endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll a,ll b,ll m){
    if(b==0LL) return 1LL;
    if(b==1LL) return mod(a,m);
    ll k = mod(exp(a,b/2,m),m);
    if(b&1LL){
        return mod(a*mod(k*k,m),m);
    }
    else return mod(k*k,m);
}

struct functional_graph{
  int N,MAXL;
  vi mycic,paiC,vis,distcic,indcic;
  vector<vi> rg,ans,ciclos;
  vi F;
  int cur_comp;
  vi cur_cic;
  functional_graph(){}
  functional_graph(int _N,int _MAXL = 20){ // 0 - index
    N = _N;
    MAXL = _MAXL;
    F = mycic = paiC = vis = distcic = indcic = vi(N,0);
    rg.resize(N);
    cur_comp = 0;
    ans = vector<vi>(N,vi(MAXL,0));
  }
  void add_edge(int a,int b){ // 0 - index
    F[a] = b;
    rg[b].pb(a);
  }
  void dfs(int v){
    if(vis[v]){
      cur_cic.pb(v);
      int c = F[v];
      while(c!=v){
        cur_cic.pb(c);
        c = F[c];
      }
      return;
    }
    vis[v] = 1;
    dfs(F[v]);
  }
  void dfs2(int v,int dist,int pai){
    vis[v] = 1;
    distcic[v] = dist;
    paiC[v] = pai;
    mycic[v] = mycic[pai];
    for(int to : rg[v]){
      ans[to][0] = v;
      dfs2(to,dist + 1,pai);
    }
  }
  void decompose(int v){
    dfs(v); 
    for(int i=0;i<sz(cur_cic);i++){
      int x = cur_cic[i];
      vis[x] = 2;//incic
      mycic[x] = cur_comp;
      distcic[x] = 0;
      paiC[x] = x;
      ans[x][0] = x;
      indcic[x] = i;
    }
    
    for(int x : cur_cic){
      for(int to : rg[x])if(vis[to]!=2){
        ans[to][0] = x;
        dfs2(to,1,x);
      }
    }
    ciclos.pb(cur_cic);
    cur_comp++;
    cur_cic.clear();
  }
  void build(){
    for(int i=0;i<N;i++){
      if(!vis[i]){
        decompose(i);
      }
    }

    for(int j=1;j<MAXL;j++){
      for(int i=0;i<N;i++){
        ans[i][j] = ans[ans[i][j-1]][j-1];
      }
    }
    
  }

  int up(int v,ll k){
    for(int i=MAXL-1;i>=0;i--){
      if(k&(1<<i)){
        v = ans[v][i];
      }
    }
    return v;
  }

  int move(int v,ll k){
    // faz v = F[v] k vezes;
    if(distcic[v] >= k){
      return up(v,k);
    }
    k-=distcic[v];
    v = paiC[v];
    int tam = ciclos[mycic[v]].size();
    int id = indcic[v];
    int jump = min(k,(ll)(tam - id));
    if(jump == tam - id){
      k-=(tam - id);
      v = ciclos[mycic[v]][0];
    }else return ciclos[mycic[v]][id + jump];
    return ciclos[mycic[v]][k%tam];
  }

};
const int N = 1e6 + 10;


int32_t main(){
  fastio;
  int n,k;
  ll m;
  cin >> n >> k >> m;
  vector<ll> p(n);
  for(int i=0;i<n;i++){
    cin >> p[i];
  }
  functional_graph grafo(n);
    // montar o grafo:
  pii ptr = pii(0,k);
  int last=0;
  for(int i=0;i<n;i++){
    int res = -1;
    while(ptr.ss + 1 < n and p[i] - p[ptr.ff] > p[ptr.ss + 1] - p[i]){
      ptr.ff++;ptr.ss++;
    }
    if(p[i] - p[ptr.ff] >= p[ptr.ss] - p[i]){
      res = ptr.ff;
    }else res = ptr.ss;
    grafo.add_edge(i,res);
  }
  grafo.build();
  
  
  for(int i=0;i<n;i++){
    cout << grafo.move(i,m) + 1<<" \n"[i==n-1];
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
