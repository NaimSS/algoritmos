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

const int N = 410;
int dp[2][N][N];
int rev[N],v[N],a[N];
vi c;
const int inf = 1e9;
int32_t main(){
  fastio;

  ifstream cin("snakes.in");
  ofstream cout("snakes.out");
  
  int n,k;
  cin >> n >> k;
  for(int i=1;i<=n;i++){
    cin >> a[i];
    c.pb(a[i]);
  }
  sort(all(c));
  c.erase(unique(all(c)),c.end());
  for(int i=1;i<=n;i++){
    v[i] = lower_bound(all(c),a[i]) - c.begin();
    rev[v[i]] = a[i];
  }

  for(int j=0;j<sz(c);j++){
    dp[0][0][j] = 0;
  }

  for(int i=1;i<=n;i++){
    int cur = i &1;
    int last = cur^1;
    rep(j,0,k+1)rep(y,0,sz(c))dp[cur][j][y]=inf;
    // to em i,fiz j alteracoes, meu tamanho é rev[y]:

    for(int j=0;j<=k;j++){
      int best=inf;
      for(int y=0;y<sz(c);y++)best = min(best,dp[last][j][y]);

      for(int y=v[i];y<sz(c);y++){
        dp[cur][j][y] = min(dp[cur][j][y],dp[last][j][y] + rev[y] - a[i]);
        if(j+1<=k){
          dp[cur][j+1][y] = min(dp[cur][j+1][y],best + rev[y] - a[i]);
        }
      }
    }

  }
  int res = inf;
  for(int j=0;j<=k;j++){
    for(int y=0;y<sz(c);y++){
      res = min(res,dp[n&1][j][y]);
    }
  }

  cout << res << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
