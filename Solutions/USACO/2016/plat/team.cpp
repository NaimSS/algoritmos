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

int n,m,k;
const int M = 1e9 + 9;
const int N = 1002;
int dp[N][N][10];
int a[N],b[N];
int solve(int i,int j,int c){
  if(c == k)return 1;
  if(i == n + 1 or j == m + 1)return 0;
  int &x = dp[i][j][c];
  if(x!=-1)return x;
  ll t = 0;
  if(a[i] > b[j])t+=solve(i+1,j+1,c+1);
  t+=solve(i+1,j,c);
  t+=solve(i,j+1,c);
  t-=solve(i+1,j+1,c);
  x = (t%M);
  if(x<0)x+=M;
  return x;
}

int32_t main(){
  fastio;
  
  ifstream cin("team.in");
  ofstream cout("team.out");
  
  cin >> n >> m >> k;
  for(int i=1;i<=n;i++)cin >> a[i];
  for(int i=1;i<=m;i++)cin >> b[i];
  sort(a+1,a+1+n);
  sort(b+1,b+1+m);
  ms(dp,-1);
  cout << solve(1,1,0) << endl;  
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
