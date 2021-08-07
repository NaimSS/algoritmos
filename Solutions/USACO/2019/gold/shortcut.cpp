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


const int N = 1e4 + 100;
const ll inf = 1e18;
ll d[N];
vector<pii> g[N];
typedef pair<ll,ll> pll;
void DJ(int S){
  for(int i=0;i<N;i++)d[i] = inf;
  priority_queue<pll,vector<pll>,greater<pll> > pq;
  d[S] =0;pq.push(pll(d[S],S));
  while(!pq.empty()){
    int cur = pq.top().ss;
    if(d[cur]!=pq.top().ff){
      pq.pop();continue;
    }
    pq.pop();
    for(auto to : g[cur])if(d[to.ff] > d[cur] + to.ss){
      d[to.ff] = d[cur] + to.ss;
      pq.push(pll(d[to.ff],to.ff));
    }
  }
}
int c[N];
int here[N];

int32_t main(){
  fastio;
    ifstream cin("shortcut.in");
  ofstream cout("shortcut.out");
  int n,m,t;
  cin >> n >> m >> t;
  for(int i=1;i<=n;i++)cin >> c[i];  
  for(int i=0;i<m;i++){
    int a,b,c;
    cin >> a >> b >> c;
    g[a].pb(pii(b,c));
    g[b].pb(pii(a,c));
  }
  DJ(1);
  vi ids;
  for(int i=2;i<=n;i++)ids.pb(i),here[i] = c[i];
  sort(all(ids),[&](int a,int b){
    return d[a] > d[b];
  });  
  
  for(int i : ids){
    sort(all(g[i]),[&](pii a,pii b){
      if(d[a.ff]+a.ss!=d[b.ff]+b.ss)return d[a.ff]+a.ss < d[b.ff]+b.ss;
      return a.ff < b.ff;
    });
    //cout << i<<" "<<d[i] << " "<<g[i][0].ff<<endl;

    here[g[i][0].ff]+=here[i];
  }
  ll best = 0;
  for(int i=1;i<=n;i++){
    if(d[i]>t)best = max(best,here[i] * ( d[i] - t));
  }
  cout<<best<<endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
