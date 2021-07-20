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
#define td(v) v.begin(),v.end()
#define sz(v) (int)v.size()
//#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left sefude
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl; 
typedef long long ll;
typedef pair<int,int> pii;
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
//#define USACO 1

const int N = 100100;
vi g[N];
int tin[N],tout[N];
int tam[N];
int t=0;

void dfs(int v,int p =-1){
  tin[v] = ++ t;
  tam[v]=1;
  for(int to : g[v])if(to!=p){
    dfs(to,v);
    tam[v]+=tam[to];
  }
  tout[v] = t;
}

struct BIT{
 int n;
 int MAX;
 vector<ll> bit;
 BIT(){}
 BIT(int _n){
   n = _n;
   MAX = n +2;
   bit.resize(n+10,0);
 }
 
 ll query(int x){
   ll r=0;
   while(x>0){
     r+=bit[x];
     x-=(x&-x);
   }
   return r;
 }
 
 ll query(int l,int r){
  if(l>r)return 0;
   return query(r) - query(l-1);
 }
 
 void update(int x,ll val){
   while(x<MAX){
     bit[x]+=val;
     x+=(x&-x);
   }
 }

}path(N),sub(N);

map<int,int> cor[N];

void update(int x,int v){
  path.update(tin[x],v);
  path.update(tout[x]+1,-v);
  //
  sub.update(tin[x],v * tam[x]);
}

int32_t main(){
  fastio;
  #ifdef USACO
  freopen("snowcow.in", "r", stdin);
  freopen("snowcow.out","w", stdout);
  #endif

  int n,q;
  cin >> n >> q;
  for(int i=1;i<=n-1;i++){
    int a,b;
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
  }
  dfs(1);
  
  while(q--){
    int op;
    cin >> op;
      int x,c;
    if(op == 1){
      cin >> x >> c;
      auto it = cor[c].upper_bound(tin[x]);
      if(it!=cor[c].begin() and tout[prev(it)->ss]>=tout[x])continue;

      while(it!=cor[c].end() and tout[it->ss]<=tout[x]){
        // inside my subtree
        update(it->ss,-1);
        cor[c].erase(it++);
      }

      cor[c][tin[x]] = x;
      update(x,1);
    }else{
      cin >> x;
      ll cima = tam[x] * path.query(tin[x]);
      ll baixo = sub.query(tin[x]+1,tout[x]);
      cout << cima + baixo << endl;
    }
  }


  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
