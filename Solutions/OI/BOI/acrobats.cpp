//DUM DA DE DO DUM DUM DE DUU DE DAU
#include <bits/stdc++.h>
#define ld long double
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
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
#define sz(v) ((int)v.size())
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
//#define left oooooopss
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<ll> vl;
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b,ll e,ll m){
    b%=m;
    ll ans = 1;
    for (; e; b = b * b % m, e /= 2)
        if (e & 1) ans = ans * b % m;
    return ans;
}
  
// debug:
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T){ 
  cerr << ' ' << H; 
  dbg_out(T...); 
}
#ifdef LOCAL
#define dbg(...) cerr<<"(" << #__VA_ARGS__<<"):" , dbg_out(__VA_ARGS__) , cerr << endl
#else
#define dbg(...) 42
#endif
//

const int N = 300100;
int A[N],B[N];
vector<pii> g[N];
typedef tuple<int,int,int> tup;
vector<tup> ans;
int vis[N];

int dfs(int v){
  vis[v]=1;
  for(auto too : g[v]){
    int to = too.ff;
    if(vis[to])continue;
    if(dfs(to)){
      A[v]^=1;
      B[v]^=1,B[to]^=1;
      int a = v,b = to;
      if(too.ss)swap(a,b);
      ans.pb(make_tuple(1,a,b));
    }
  }
  return A[v];
}



int32_t main(){
    fastio;
    int n,m;
    cin >> n >> m;
    if(n==1){
      cout << -1 << endl;
      return 0;
    }
    rep(i,0,m){
      int a,b;
      cin >> a >> b;
      A[a]^=1;
      B[b]^=1;
      g[a].pb(pii(b,0));
      g[b].pb(pii(a,1));
    }
    vi inicio;
    for(int i=1;i<=n;i++){
      if(!vis[i]){
        inicio.pb(i);
        if(dfs(i)){

          cout << -1 << endl;
          return 0;
        }
      }
    }
    // conserta componentes;
    // agora tem que conectar elas

    if(n>1){
      for(int i=1;i<=n;i++){
        int a = i,b = (i==n?1:i+1);
        B[a]^=1;
        B[b]^=1;
        ans.pb(make_tuple(2,a,b));
      }
    }
    // e depois juntar os B's
    vi imp;
    rep(i,1,n+1)if(B[i])imp.pb(i);
    if(sz(imp)&1){
      cout << -1 << endl;
      return 0;
    }
    for(int i=0;i<sz(imp);i+=2){
      ans.pb(make_tuple(2,imp[i],imp[i+1]));
    }
    cout << sz(ans) << endl;
    for(auto [a,b,c] : ans){
      cout << a<<" "<<b<<" "<<c<<endl;
    }
    
    
    // math -> gcd it all
    // Did u check N=1? Did you switch N,M?
}
