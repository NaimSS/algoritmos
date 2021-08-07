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

const int N = 1e4 + 1000;
bool isp[N];
int k =0;
int prime[N];
void crivo(){
  for(int i=2;i<N;i++)isp[i] = 1;
  for(int i=2;i<N;i++){
    if(isp[i]){
      prime[++k] = i;
      for(int j=i+i;j<N;j+=i){
        isp[j] = 0;
      }
    }
  }
}

int M;
int dp[1400][N];
int solve(int id,int n){
  if(prime[id] > n)return 1;
  int &x = dp[id][n];
  if(x!=-1)return x;
  x=solve(id + 1,n);
  int cur = 1;
  for(int k = 0;;k++){
    cur*=prime[id];
    if(cur > n)break;
    x = (x + 1ll * cur * solve(id + 1,n - cur))%M;
  }
  return x;
}

int n;
int32_t main(){
  fastio;
  ms(dp,-1);
  
  ifstream cin("exercise.in");
  ofstream cout("exercise.out");
  
  cin >> n >> M;
  crivo();

  cout << solve(1,n) << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
