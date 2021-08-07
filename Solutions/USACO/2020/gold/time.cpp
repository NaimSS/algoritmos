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

const int N = 1010;
const int MT = 510;

ll dp[N][MT];

vi g[N];
int m[N];
bool vis[N][MT];
ll C;
const int inf = 1e9;
ll solve(int v,int t){
  if(t == MT-1)return -inf;
  ll &x = dp[v][t];
  if(vis[v][t])return x;
  vis[v][t] = 1;
  x = - inf;
  if( v == 1)x = max(x, - C*t*t);
  for(int to : g[v]){
    x = max(x,m[v] + solve(to,t+1)); // continua    
  }

  return x;
}



int32_t main(){
  fastio;
  
  ifstream cin("time.in");
  ofstream cout("time.out");
  
  int n,M;
  cin>>n>>M >> C;
  for(int i=1;i<=n;i++)cin >> m[i];
  for(int i=0;i<M;i++){
    int a,b;
    cin>>a>>b;
    g[a].pb(b);
  }

  cout << max(0ll,solve(1,0)) << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
