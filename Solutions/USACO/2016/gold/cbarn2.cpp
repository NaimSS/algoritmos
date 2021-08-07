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
#define int long long
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

const int N = 202;
int r[N];

int L;// limite

ll dp[N][N][8];
ll cost[N][N];
int vis[N][N][8];
int T=0;
ll solve(int i,int last,int k){
  if(k < 0)return 1e18;
  if(i == L){
    return cost[last+1][i];
  }
  ll &x = dp[i][last][k];
  if(vis[i][last][k] == T)return x;
  vis[i][last][k] = T;
  x = 1e18;


  // nao coloca
  x = solve(i+1,last,k);
  // coloca um cara aqui
  x = min(x,solve(i+1,i,k - 1) + cost[last+1][i]);
 
  return x;
}

int32_t main(){
  fastio;
  
  ifstream cin("cbarn2.in");
  ofstream cout("cbarn2.out");
  
  int n,k;

  cin >> n >> k;
  for(int i=n;i>=1;i--){
    cin >> r[i];
    r[i+n] = r[i];
  }
  r[0] = r[n];

  for(int i=0;i<=2*n;i++){
    ll acu=0;
    for(int j=i;j<=2*n;j++){
      cost[i][j] = cost[i][j-1] + acu;
      acu+=r[j];
    }
  }

  ll res = 1e18;
  for(int i=1;i<=n;i++){
    // TIRAR ISSO KRL
    
    T++;
    L = i + n;
    res = min(res,solve(i+1,i,k-1)); 
  }

  cout << res << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
