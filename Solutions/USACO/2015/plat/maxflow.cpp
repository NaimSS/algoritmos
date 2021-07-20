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
#define sz(v) ((int)v.size())
#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left sefude
#define db(x) cerr <<#x <<" == "<<x << endl;
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

template <class T> 
struct lazy_seg{
public:
  vector<T>  st , lazy;
  lazy_seg(int n){
    st.resize(4*n + 1 , 0) , lazy.resize(4*n + 1, 0);
  }
  lazy_seg() = default;
  void push(int l , int r , int curr){
    if(lazy[curr] != 0){
      st[curr] += lazy[curr]*(r-l+1);
      if(l!=r) lazy[2*curr] += lazy[curr] , lazy[2*curr+1] += lazy[curr];
      lazy[curr] = 0 ;
    }
  }
  void pull(int l , int r , int curr){
    push(l,r,curr); int mid = l + (r-l)/2;
    if(l!=r) push(l,mid,2*curr) , push(mid+1,r,2*curr+1);
    st[curr] = (st[2*curr] + st[2*curr+1]);
  }
  void upd(int x , int y, T v,  int l, int r , int curr){
    int mid = (l+r)/ 2;  push(l,r,curr);
    if(l == x && r == y){
      lazy[curr] += v;
      push(l,r,curr);
      return ;
    }
    if(y <= mid) upd(x,y,v,l,mid,2*curr);
    else if(x > mid) upd(x,y,v,mid+1,r,2*curr+1);
    else upd(x,mid,v,l,mid,2*curr) , upd(mid+1,y,v,mid+1,r,2*curr+1);
    pull(l,r,curr);
  }
  T qry(int x , int y , int l , int r , int curr){
    int mid = (l+r)/2; push(l,r,curr);
    if(l == x && r == y) return st[curr];
    if(y <= mid) return qry(x,y,l,mid,2*curr);
    else if(x > mid) return qry(x,y,mid+1,r,2*curr+1);
    return (qry(x,mid,l,mid,2*curr) + qry(mid+1,y,mid+1,r,2*curr+1));
  }
  void build(int l , int r,  int curr){
    int mid = (l+r)/2;
    if(l == r){
      st[curr] = 0; 
      return ;
    }
    build(l,mid,2*curr);
    build(mid+1,r,2*curr+1);
    st[curr] = (st[2*curr]  + st[2*curr+1]);
  }
};

template<class T>
class HLD{
public:
  lazy_seg<T> seg;
  HLD(int n): Sz(n+1) , Hd(n+1) , p(n+1, -1) , g(n+1) , out(n+1) , in(n+1) , n(n){
    seg = lazy_seg<T>(n);
    seg.build(0 , n-1 , 1);
  }
  void add_edge(int x , int y){
    g[x].push_back(y);
    g[y].push_back(x);
    edges ++ ;
    assert(edges < n);
  }
  void dfs_sz(int x , int par = -1){
    Sz[x] = 1;
    trav(w, g[x]){
      if(w == par) continue;
      dfs_sz(w,x);
      Sz[x] += Sz[w];
      if(Sz[w] > Sz[g[x][0]] || g[x][0] == par) swap(w, g[x][0]);
    }
  }
  void dfs_dec(int x , int par = -1){ 
    in[x] = tin++;
    allin(w, g[x]){
      if(w == par) continue;
      p[w] = x;
      Hd[w] = ((w == g[x][0]) ? Hd[x] : w);
      dfs_dec(w,x); 
    }
    out[x] = tin;
  }
  void decompose(int root){
    Hd[root] = root;
    dfs_sz(root);
    dfs_dec(root);
  }
  int lca(int x , int y){
    while(Hd[x] != Hd[y]){
      if(in[Hd[x]] > in[Hd[y]]) swap(x,y);
      y = p[Hd[y]];
    }
    return in[x] < in[y] ? x : y ;
  }
  void update_subtree(int x , T v){
    seg.upd(in[x] , out[x]-1 , v, 0 , n-1 , 1);
    return ;
  }
  void update_path(int x , int y , T v , bool c = 1){
    int u = lca(x,y);
    for(; Hd[x] != Hd[y] ; y = p[Hd[y]]){
      if(in[Hd[x]] > in[Hd[y]]) swap(x,y);
      seg.upd(in[Hd[y]] , in[y] ,v, 0 , n-1 , 1);
    }
    if(in[x] > in[y]) swap(x,y);
    if(in[u] + 1 - (c ? 1 : 0) <= in[y]) seg.upd(in[u] + 1 - (c? 1: 0) , in[y] , v, 0, n-1 , 1);
    return ;
  }
  T query_path(int x , int y , bool c = 1){  
    int u = lca(x,y);
    T ans = 0;
    for(; Hd[x] != Hd[y] ; y = p[Hd[y]]){
      if(in[Hd[x]] > in[Hd[y]]) swap(x,y);
      ans = (ans + seg.qry(in[Hd[y]] , in[y] , 0, n-1, 1));
    }
    if(in[x] > in[y]) swap(x,y);
    if(in[u] + 1 - (c ? 1 : 0) <= in[y]) ans = (ans + seg.qry(in[u] + 1 - (c ? 1 : 0) , in[y],  0 , n-1, 1)); 
    return ans;
  }
  T query_subtree(int x){
    return seg.qry(in[x] , out[x]-1 , 0, n-1, 1);
  }

private:
  vector < vi > g; 
  vi Sz , Hd , in , out ,p ; 
  int n , edges =0  , tin = 0;
};

int32_t main(){
  fastio;
    ifstream cin("maxflow.in");
  ofstream cout("maxflow.out");
  int n,q;
  cin>>n>>q;
  HLD<ll> hld(n);
  for(int i=1;i<n;i++){
    int a,b;
    cin>>a>>b;
    hld.add_edge(a,b);
  }
  hld.decompose(1);
  while(q--){
    int a,b;
    cin>>a>>b;
    hld.update_path(a,b,1);
  }
  int res=0;
  for(int i=1;i<=n;i++){
    res=max(res,hld.query_path(i,i));
  }
  cout<<res<<endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
