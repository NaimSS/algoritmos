#include <bits/stdc++.h>
#define ld long double
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
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
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
//#define left oooooopss
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<ll> vl;
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b,ll e,ll m){
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
      if (e & 1) ans = ans * b % m;
  return ans;
}
  
// debug:
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T){ 
  cerr << ' ' << H; 
  dbg_out(T...); 
}
#ifdef LOCAL
#define dbg(...) cerr<<"(" << #__VA_ARGS__<<"):" , dbg_out(__VA_ARGS__) , cerr << endl
#else
#define dbg(...) 42
#endif
//
const int N = 200100;
vector<pll> g[N];
ll dp[N][2];
int n;
int vis[N][2];
int pai[N];
multiset<ll> MX[N];
ll solve(int v,int pp,int p){
  ll &x = dp[v][pp];
  if(vis[v][pp])return x;
  vis[v][pp]=1;
  pai[v] = p;
  x=0;
  ll sum=0;

  MX[v].insert(-1e9);
  
  for(auto To : g[v])if(To.ff != p){
    ll to = To.ff;
    ll w = To.ss;
    
    if(pp){
      sum += max(solve(to,0,v),solve(to,1,v) + w);  
      MX[v].insert(w - max(solve(to,0,v),solve(to,1,v) + w) + solve(to,0,v));
    }else{
      sum += max(solve(to,0,v),solve(to,1,v) + w);
    }
  }
  if(pp)x = sum + *MX[v].rbegin();
  else x = sum;
  return x;
}

ll mx=0;
void solve2(int v,int p=-1){
  solve(v,0,p);
  solve(v,1,p);
  assert(vis[v][0] && vis[v][1]);
  mx = max(mx,dp[v][0]);
  for(auto To : g[v])if(To.ff!=p){
    ll to = To.ff,w = To.ss;
    //salvar:
    pll cur1 = pll(dp[v][0],dp[v][1]);
    pll cur2 = pll(dp[to][0],dp[to][1]);

    // conserta pai
    dp[v][0]-=max(dp[to][0],dp[to][1] + w);
    dp[v][1]-=max(dp[to][0],dp[to][1] + w);
    dp[v][1]-=*MX[v].rbegin();
    ll valor = w - max(solve(to,0,v),solve(to,1,v) + w) + solve(to,0,v);

    MX[v].erase(MX[v].find(valor));
    dp[v][1] += *MX[v].rbegin();
    // conserta filho:

    dp[to][0] += max(dp[v][0],dp[v][1] + w);
    assert(MX[to].size()>0);
    dp[to][1] -= *MX[to].rbegin();
    ll valor2 = w - max(dp[v][0],dp[v][1] + w) + dp[v][0];
    MX[to].insert(valor2);
    dp[to][1] += max(dp[v][0],dp[v][1] + w) + *MX[to].rbegin();

    solve2(to,v);

    //rollback:
    dp[v][0] = cur1.ff,dp[v][1]=cur1.ss;
    dp[to][0] = cur2.ff,dp[to][1]=cur2.ss;
    MX[v].insert(valor);

    MX[to].erase(MX[to].find(valor2));
  }

}
  
int32_t main(){
    fastio;
    cin >> n;
    ll tot=0;
    rep(i,1,n){
      int a,b,w;
      cin >> a >> b >> w;
      g[a].pb(pll(b,w));
      g[b].pb(pll(a,w));
      tot+=w;
    }
    dbg(tot);
    ms(dp,-1);
    solve(1,0,-1);
    solve(1,1,-1);
    solve2(1);
    cout << mx << endl;

    // math -> gcd it all
    // Did u check N=1? Did you switch N,M?
}
