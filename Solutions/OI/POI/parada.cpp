// https://szkopul.edu.pl/problemset/problem/1QaUWE_ePAmitZjgAszOVD1U/site/?key=submissions
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

const int N = 2e5 + 100;
vi g[N];
int dp[N];
int ans = 0;

void dfs(int v,int p = -1){
  dp[v] = sz(g[v]);
  vi vec;
  for(int to : g[v])if(to!=p){
    dfs(to,v);
    int cur = dp[to] - 1 + sz(g[v]) - 1;
    ans = max(ans,cur);
    dp[v] = max(dp[v],cur);
    vec.pb(dp[to] - 1);
  }
  sort(all(vec),greater<int>());
  if(sz(vec) >= 2){
    ans = max(ans,vec[0] + vec[1] + sz(g[v]) - 2);
  }
  return;
}

int32_t main(){
  fastio
  int n;
  cin >> n;
  for(int i=1;i<n;i++){
    int a,b;
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);  
  }
  dfs(1);
  cout << ans << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
