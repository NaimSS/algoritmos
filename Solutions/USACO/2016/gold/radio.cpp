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
#define int long long
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

const int N = 1010;

int dp[N][N];

pii a[2];
pii p[N][2];
char s[N],t[N];
int n,m;
int sq(int x){return x * x;}
int dist(pii a,pii b){
  return sq(a.ff - b.ff) + sq(a.ss - b.ss);
}
int solve(int i,int j){
  if(i>n)i=n;
  if(j>m)j=m;
  if(i == n and j == m)return 0;
  if(dp[i][j]!=-1)return dp[i][j];
  int &x = dp[i][j];
  x = 2e9 + 7;
  rep(ma,1,4){
    int ni = (i + (ma&1)),nj = (j + !!(ma&2));
    if(nj > m)nj=m;
    if(ni>n)ni=n;
    pii A = p[ni][0];
    pii B = p[nj][1];
    x = min(x,dist(A,B) + solve(ni,nj));

  }
  return x;
}

int32_t main(){
  fastio;
  ifstream cin("radio.in");
  ofstream cout("radio.out");
  ms(dp,-1);
  cin >> n >> m;
  cin >> a[0].ff >> a[0].ss;
  cin >> a[1].ff >> a[1].ss;
  for(int i=1;i<=n;i++)cin >> s[i];
  for(int i=1;i<=m;i++)cin >> t[i];

  for(int it=0;it<2;it++){
    p[0][it] = a[it];
    for(int i=1;i<=(it == 0 ? n : m);i++){
      p[i][it] = p[i-1][it];
      char c = (it == 0 ? s[i] : t[i]);
      if(c == 'N')p[i][it].ss++;
      else if(c=='S')p[i][it].ss--;
      else if(c=='E')p[i][it].ff++;
      else p[i][it].ff--;
    }

  }

  cout << solve(0,0) << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
