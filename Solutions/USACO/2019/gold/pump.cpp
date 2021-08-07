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
typedef pair<ll,ll> pll;
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

const int N = 1010;
int a[N],b[N];
int c[N],f[N];
const int inf = 2e9;
int d[N];
int n,m;
int vis[N];
vector<pii> g[N];
vi V[N];
int solve(int FF){
  for(int i=1;i<=n;i++)d[i] = inf,vis[i]=0;
  d[1]=0;
  priority_queue<pii,vector<pii>,greater<pii> >pq;
  pq.push(pii(d[1],1));
  while(!pq.empty()){
    int cur = pq.top().ss;
    pq.pop();
    if(vis[cur])continue;
    vis[cur]=1;
    for(auto to : g[cur]){
      if(d[to.ff] > d[cur] + to.ss){
        pq.push(pii(d[to.ff] = d[cur] + to.ss,to.ff));
      }
    }
  }
  if(d[n] == inf)return 0;
  return ((1000000 * FF) / d[n]);
}

int32_t main(){
  fastio;
  
  ifstream cin("pump.in");
  ofstream cout("pump.out");
  
  cin >> n >> m;
  for(int i=0;i<m;i++){
    cin >> a[i] >> b[i] >> c[i] >> f[i];
    V[f[i]].pb(i);
  }

  int ans = 0;
  for(int ff = 1000;ff>=1;ff--){
    if(sz(V[ff])){
      for(int id : V[ff]){
        g[a[id]].pb(pii(b[id],c[id]));
        g[b[id]].pb(pii(a[id],c[id]));
      }
      ans = max(ans,solve(ff));
    }
  }

  cout << ans << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
