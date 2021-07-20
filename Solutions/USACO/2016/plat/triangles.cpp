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

const int N = 301;

typedef pair<ll,ll> pii;
pii p[N];
pii operator-(const pii& a,const pii& b){
  return pii(a.ff - b.ff,a.ss - b.ss);
}
bool cross(int i,int j,int k){
  pii p1 = p[j]-p[i];
  pii p2 = p[k]-p[i];
  return (p1.ff*p2.ss - p1.ss * p2.ff) > 0;
}

bitset<N> g[N][N];
int res[N];

int32_t main(){
  fastio;

  ifstream cin("triangles.in");
  ofstream cout("triangles.out");

  int n;
  cin >> n;
  rep(i,0,n){
    cin >> p[i].ff >> p[i].ss;
  }
  rep(i,0,n)rep(j,0,n)if(j!=i){
    rep(k,0,n)g[i][j][k] = (cross(i,j,k));
  }

  rep(i,0,n)rep(j,i+1,n)rep(k,j+1,n){
    if(cross(i,j,k))
    res[(g[i][j]&g[j][k]&g[k][i]).count()]++;
    else res[(g[i][k]&g[k][j]&g[j][i]).count()]++;
  }
  rep(i,0,n-2)cout << res[i] << endl;



  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
