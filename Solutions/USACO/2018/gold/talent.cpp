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

const int N = 251,MAXW=1010;
ll n,w;

pair<ll,ll> v[N];

ll dp[N][MAXW];
const ll inf=1e18;
bool ok(ll x){
  rep(i,0,N)rep(j,0,MAXW)dp[i][j] = -inf;

  dp[0][0] = 0;
  for(int i=1;i<=n;i++){
    for(int j=0;j<=w+1;j++){
      dp[i][min(j + v[i].ff,w+1)] = max(dp[i][min(j + v[i].ff,w+1)],
        dp[i-1][j] + v[i].ss * 1000ll - 1ll * v[i].ff * x
        );
      dp[i][j] = max(dp[i][j],dp[i-1][j]);
      
    }
  }

  if(dp[n][w]>=0 or dp[n][w+1]>=0)return 1;
  return 0;
}

int32_t main(){
  fastio;

  ifstream cin("talent.in");
  ofstream cout("talent.out");

  cin >> n >> w;
  for(int i=1;i<=n;i++){
    cin >> v[i].ff >> v[i].ss;
  }
  sort(v+1,v+1+n);

  ll l = 0,r = (1e12);
  ll ans = 0;
 
  while(l<=r){
    int mid = (l+r)>>1;
    if(ok(mid)){
      ans = mid;
      l = mid + 1;
    }else r = mid - 1;
  }

  cout << ans << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
