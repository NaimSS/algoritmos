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

const int N = 20;
int dp[(1<<N)];
int sum[(1<<N)];
vi vec[N];
int D[N],C[N];
int n,L;

int next(int to,int curt){
  auto it = lower_bound(all(vec[to]),curt + 1);
  if(it == vec[to].begin())return curt;
  it--;
  return max(curt,*it + D[to]);
}

int32_t main(){
  fastio;
  
  ifstream cin("movie.in");
  ofstream cout("movie.out");
  
  cin >> n >> L;
  rep(i,0,n){
    cin >> D[i] >> C[i];
    vec[i].resize(C[i]);
    for(auto& x : vec[i])cin >> x;
  }
  dp[0] = 0;
  int res = -1;
  rep(ms,0,(1<<n)){
    rep(to,0,n)if(!(ms&(1<<to))){
      dp[ms|(1<<to)]=max(dp[ms|(1<<to)],next(to,dp[ms]));
    }
  
    if(dp[ms] >= L){
      if(res == -1)res = __builtin_popcount(ms);
      else res = min(res,__builtin_popcount(ms));
    }

  }

  cout << res << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
