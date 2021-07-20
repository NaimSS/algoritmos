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


const int N = 100100;
typedef pair<ll,ll> pll;
vector<pll> g[N];
ll d1[N],d2[N];
bool mark[N];
ll val[N];
const ll inf = 1e18;

int32_t main(){
  fastio;
  
  ifstream cin("dining.in");
  ofstream cout("dining.out");
  
  int n,m,k;
  cin >> n >> m >> k;
  for(int i=0;i<m;i++){
    int a,b,c;
    cin >> a >> b >> c;
    g[a].pb(pii(b,c));
    g[b].pb(pii(a,c));
  }
  for(int i=1;i<=k;i++){
    ll j,v;
    cin >> j >> v;
    val[j] = max(val[j],v);
  }
  for(int i=1;i<=n;i++){
    d1[i] = inf;
  }
  d1[n] = 0;
  priority_queue<pll,vector<pll>,greater<pll> >pq;
  pq.push(pll(d1[n],n));
  while(!pq.empty()){
    int cur = pq.top().ss;
    if(d1[cur]!=pq.top().ff){
      pq.pop();
      continue;
    }
    pq.pop();
    for(auto to : g[cur]){
      if(d1[to.ff] > to.ss + d1[cur]){
        d1[to.ff] = to.ss + d1[cur];
        pq.push(pll(d1[to.ff],to.ff));
      }
    }
  }

  for(int i=1;i<=n;i++){
    d2[i] = d1[i] + 1;
    if(val[i]!=0){
      d2[i] = d1[i] - val[i];
      pq.push(pll(d2[i],i));
    }

  }
  while(!pq.empty()){
    int cur = pq.top().ss;
    mark[cur]=1;
    if(d2[cur]!=pq.top().ff){
      pq.pop();
      continue;
    }
    pq.pop();
    for(auto to : g[cur]){
      if(d2[to.ff] > to.ss + d2[cur]){
        pq.push(pll(d2[to.ff] = to.ss + d2[cur],to.ff));
      }
    }
  }
  
  for(int i=1;i<n;i++)cout << mark[i] << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
