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

const int N = 1e4 + 10;
bool mark[N];
int prime[N];
int k=0;
double Log[N];
void crivo(){
  for(int i=2;i<N;i++){Log[i] = log2(i);
    if(!mark[i]){
      prime[++k] = i;
      for(int j=i;j<N;j+=i)mark[j]=1;
    }
  }
}

const int L = 120;
double dp[N][L];
bool vis[N][L];
const double inf = 1e9;
double solve(int n,int p){
  if(p==L || prime[p]>n)return 0;
  if(vis[n][p])return dp[n][p];
  vis[n][p]=1;
  double& x = dp[n][p];
  x=0;
  x = max(x,solve(n,p+1));
  int c = prime[p];
  for(int it=0;;it++){
    if(c > n)break;
    x = max(x,Log[c] + solve(n - c,p+1));
    
    c *= prime[p];
  }

  return x;
}

void roll(int n,int p,vi& tam){
  if(p == L || prime[p] > n){
    while(n--)tam.pb(1);
    return;
  }
  double best = solve(n,p+1);
  int id = -1;
  int c = prime[p];
  for(int it=0;;it++){
    if(c>n)break;
    if(Log[c] + solve(n-c,p+1) > best){
      best = Log[c] + solve(n-c,p+1);
      id = it;
    }
    c*= prime[p];
  }
  if(id == -1)roll(n,p+1,tam);
  else{
    c = prime[p];
    for(int i=0;i<id;i++){
      c*=prime[p];
    }
    tam.pb(c);
    roll(n-c,p+1,tam);
  }
  return;
}

int32_t main(){
  fastio;
  crivo();
  int t;
  cin >> t;
  while(t--){
    int n;
    cin >> n;
    vi tam;
    roll(n,1,tam);
    sort(all(tam));

    vi v;
    int ini = 1;
    for(int T : tam){
      for(int i=1;i<T;i++){
        v.pb(ini + i);
      }
      v.pb(ini);
      ini+=T;
    }
    
    for(int x : v)cout << x<<" ";
    cout << endl;

  }


  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
