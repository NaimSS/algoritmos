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
//#define sz(v) (int)v.size()
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

// source: https://codeforces.com/blog/entry/44351

const int N =100100;
ll BIT[N];
int sz[N],cor[N];
vi g[N];
int bigchild[N],big[N];
int res[N];

void update(int x,int v){
  while(x<N){
    BIT[x]+=v;
    x+=(x&-x);
  }
}
ll query(int x){
  ll r=0;
  while(x>0){
    r+=BIT[x];
    x-=(x&-x);
  }
  return r;
}


void add(int v,int p,int x){
  update(cor[v],x);
  for(auto to : g[v]){
    if(to!=p and !big[to])add(to,v,x);
  }
}

int n;

void dfs(int v,int p,bool keep){
  int mx=-1,bigchild=-1;
  for(auto to : g[v]){
    if(to!=p and mx < sz[to])
      mx=sz[to],bigchild=to;
  }

  for(auto to : g[v]){
    if(to!=p and to!=bigchild){
      dfs(to,v,0);
    }
  }
  if(bigchild!=-1){
    dfs(bigchild,v,1);big[bigchild]=1;
  }
  add(v,p,1);
  // answer queries;
  res[v] = sz[v] - query(cor[v]-1) - 1;
  if(bigchild!=-1)big[bigchild]=0;
  if(!keep)add(v,p,-1);

}
void pre(int v,int p = -1){
  sz[v] = 1;
  for(int to : g[v])if(to!=p){
    pre(to,v);sz[v]+=sz[to];
  }
}

int32_t main(){
  fastio;
    ifstream cin("promote.in");
  ofstream cout("promote.out");
  int n;
  cin>>n;
  vi comp;
  for(int i=1;i<=n;i++){
    cin >> cor[i];
    comp.pb(cor[i]);
  }
  Unique(comp);
  for(int i=1;i<=n;i++){
    cor[i] = lower_bound(all(comp),cor[i]) - comp.begin() + 1;
  }
  for(int i=2;i<=n;i++){
    int x;
    cin>>x;
    g[i].pb(x);
    g[x].pb(i);
  }
  pre(1);
  dfs(1,-1,0);
  for(int i=1;i<=n;i++)cout << res[i]<<endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
