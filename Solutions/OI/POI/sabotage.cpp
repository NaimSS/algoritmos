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

const int N = 5e5 + 100;
bool dp[N];
vi g[N];
double x;
int tam[N];
int k;
void pre(int v,int p = -1){
  tam[v] =1;

  for(int to : g[v])if(to!=p){
    pre(to,v);
    tam[v]+=tam[to];
  }

}
const double EPS = 1e-9;
bool dfs(int v,int p = -1){
  bool ok = 1;
  for(int to : g[v])if(to!=p){
    if(dfs(to,v))return 1;
    ok = 0;
    int tot = tam[v] - 1;
    
    if(dp[to] and (1.0*tam[to]>=1.0*tot*x))dp[v]|=1;

  }

  dp[v]|=ok;
  if(dp[v] and tam[v]>=k)return 1;
  return 0;
}

int32_t main(){
  fastio;
  int n;
  cin >> n >> k;
  k++;
  for(int i=2;i<=n;i++){
    int p;
    cin >> p;
    g[p].pb(i);
    dp[i] = 0;
  }

  pre(1);

  double l =0,r = 1;
  double ans = 0;

 

  for(int iter=0;iter<40;iter++){
    double mid = (l+r)/2.0;
    for(int i=1;i<=n;i++)dp[i]=0;
    x = mid;
    if(dfs(1)){
      ans = mid;
      l = mid;
    }else r = mid;
  }


  cout << setprecision(10) << fixed;
  cout << ans << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
