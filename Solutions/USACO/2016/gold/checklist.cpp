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
#define sz(v) (int)v.size()
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
int n,m;
const int N = 1010;
int x[N],y[N],a[N],b[N];
ll dp[N][N][2];
ll sq(ll x){return x * x;}
ll solve(int i,int j,int f){
  if(i == n+1)return 0;
  if(i == n and j == m and f == 0)return 0;
  ll &v = dp[i][j][f];
  if(v!=-1)return v;
  v = 1e18;
  int X = (f == 0 ? x[i] : a[j]);
  int Y = (f == 0 ? y[i] : b[j]);
  // move j:
  if(j!=m){
    v = min(v,sq(X - a[j+1]) + sq(Y - b[j+1]) + solve(i,j+1,1));
  }
  // move i:
  if(i!=n || (i == n and j == m and f == 1)){
    v = min(v,sq(X - x[i + 1]) + sq(Y - y[i+1]) + solve(i+1,j,0));
  }
  return v;
}
int32_t main(){
    ifstream cin("checklist.in");
  ofstream cout("checklist.out");
  ms(dp,-1);
  fastio;
  cin >> n >> m;
  for(int i=1;i<=n;i++){
    cin >> x[i] >> y[i];
  }
  x[n+1] = x[n];
  y[n+1] = y[n];
  for(int i=1;i<=m;i++){
    cin >> a[i] >> b[i];
  }
  cout << solve(1,0,0) << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
