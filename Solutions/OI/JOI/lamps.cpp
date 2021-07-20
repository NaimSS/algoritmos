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

const int N = 1e6 + 10;
int dp[N][8];
int A[N],B[N];
inline int get(int id,int msk){
  int a = A[id];
  if(msk&(1<<0))a=0;
  if(msk&(1<<1))a=1;
  if(msk&(1<<2))a^=1;
  return a;
}
int n;
int solve(int id,int m){
  if(id == n + 1)return 0;
  if(dp[id][m]!=-1)return dp[id][m];
  int&x = dp[id][m];
  x = n - id + 1;
  rep(nv,0,8)if(get(id,nv) == B[id]){
    x = min(x,__builtin_popcount(~m&nv) + solve(id+1,nv));
  }
  return x;
}

int32_t main(){
  fastio;
  ms(dp,-1);
  cin>>n;
  char c;
  for(int i=1;i<=n;i++){
    cin >> c;
    A[i]=c-'0';
  }
  for(int i=1;i<=n;i++){
    cin >> c;
    B[i] = c-'0';
  }
  cout << solve(1,0) << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
