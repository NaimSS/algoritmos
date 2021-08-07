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
ll tot[(1<<N)];
int h[N],w[N],s[N];
int32_t main(){
  fastio;
    ifstream cin("guard.in");
  ofstream cout("guard.out");
  int n,H;
  cin >> n >> H;
  ms(dp,-1);
  for(int i=0;i<n;i++){
    cin >> h[i] >> w[i] >> s[i];
    dp[(1<<i)] = s[i];
  }
  for(int m=0;m<(1<<n);m++){
    if(dp[m]==-1)continue;
    rep(i,0,n)if((1<<i)&m)tot[m]+=h[i];
    rep(i,0,n){
      if(m&(1<<i))continue;
      dp[m|(1<<i)] = max(dp[m|(1<<i)],min(dp[m] - w[i],s[i]));
    }

  }
  int best = -1;
  rep(i,0,(1<<n))if(dp[i]>=0 and tot[i] >= H){
    best = max(best,dp[i]);
  }
  if(best == -1)cout<<"Mark is too tall"<<endl;
  else cout << best << endl;


  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
