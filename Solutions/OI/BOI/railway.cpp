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

const int N = 100100,MAXL = 20,inf = 100100;

int ans[N][MAXL];
vi g[N];
int H[N];
int in[N];
int T=0;
void dfs(int v,int p = -1){
  in[v] = ++T;
  for(int to : g[v])if(to!=p){
    ans[to][0] = v;
    H[to] = H[v] + 1;
    dfs(to,v);
  }
}
int lca(int a,int b){
  if(H[a] < H[b])swap(a,b);
  for(int i=MAXL-1;i>=0;i--){
    if(H[a] - (1<<i) >= H[b])a=ans[a][i];
  }
  if(a==b)return a;
  for(int i=MAXL-1;i>=0;i--)
    if(ans[a][i]!=ans[b][i])a=ans[a][i],b=ans[b][i];
  return ans[a][0];
}


ll pre[N];

void add_path(int l,int r){
  if(l==r)return;
  pre[l]++;pre[r]--;
}

void add(int a,int b){
  int L = lca(a,b);
  add_path(a,L);add_path(b,L);
}

void virtual_tree(vi K){
    auto f = [&](int a , int b){
        return in[a] < in[b];
    };
    //vector<edge> e;
    sort(all(K) , f);
    int m = sz(K);
    rep(i,1,m){
        K.push_back(lca(K[i] , K[i-1]));
    }
    sort(all(K) , f);
    K.erase(unique(all(K)) , K.end());
    
    rep(i,0,sz(K) -1){
        int z = lca(K[i] , K[i+1]);
        add(K[i + 1],z);
        //e.push_back({K[i+1] , z ,dist(z,K[i+1])});
    }
    
    return;
    //return {e ,K[0]};
}


int pai[N];
void go(int v,int p = -1){
  for(int to : g[v])if(to!=p){
    pai[to] = v;
    go(to,v);
    pre[v]+=pre[to];
  }
}

pii e[N];

int32_t main(){
  fastio;
  int n,q,k;
  cin >> n >> q >> k;
  for(int i=1;i<n;i++){
    int a,b;cin>>a>>b;
    g[a].pb(b);
    g[b].pb(a);
    e[i] = pii(a,b);
  }
  ans[1][0]=1;
  dfs(1);
  for(int j=1;j<MAXL;j++){
    for(int i=1;i<=n;i++){
      ans[i][j] = ans[ans[i][j-1]][j-1];
    }
  }
  while(q--){
    int s;
    cin >> s;
    vi v(s);
    rep(i,0,s)cin >> v[i];
    virtual_tree(v);
  }
  go(1);
 
  vi res;
  
  for(int i=1;i<n;i++){

    if(pai[e[i].ff] != e[i].ss)swap(e[i].ff,e[i].ss);
    assert(pai[e[i].ff] == e[i].ss);
    if(pre[e[i].ff] >= k)res.pb(i);
  }
  cout << sz(res)<<endl;
  for(int x : res)cout<<x<<" ";
  cout<<endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
