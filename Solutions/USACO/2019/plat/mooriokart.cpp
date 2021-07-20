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

const int M = 1e9 + 7;
const int N = 1550;
vector<pii> g[N];

bool vis[N];
int K = 0;
vi res;
void dfs1(int v){
  res.pb(v);
  vis[v] = 1;
  for(auto to : g[v])if(!vis[to.ff]){
    dfs1(to.ff);
  }
}

vi get(int v){
  res.clear();
  dfs1(v);
  return res;
}

const int Y = 2550;
int y;

pii operator+(const pii& a,const pii& b){
  return pii((a.ff + b.ff)%M,(a.ss + b.ss)%M);
}

vector<pii> dp;
void dfs2(int v,int p,int d){
  if(p!=-1)dp[min(y,d)]=dp[min(d,y)]+pii(d,1);
  for(auto to : g[v])if(to.ff!=p){
    dfs2(to.ff,v,to.ss + d);
  }

}
vector<pii> build(vi& v){
  dp = vector<pii>(y + 1,pii(0,0));
  int mx = y;
  for(int x : v){
    dfs2(x,-1,0);
  }

  ll inv2 = (M+1)/2;
  for(int i=0;i<=y;i++){
    dp[i].ff = (dp[i].ff*inv2)%M;
    dp[i].ss = (dp[i].ss*inv2)%M;
  }
  return dp;
}

pii ans[Y];
pii temp[Y];

pii join(pii a,pii b){
  return pii((1ll*a.ff*b.ss + 1ll*a.ss*b.ff)%M,(a.ss * b.ss)%M);
}

int32_t main(){
  fastio;
  
  ifstream cin("mooriokart.in");
  ofstream cout("mooriokart.out");
  
  int n,m,x;
  cin >> n >> m >> x >> y;

  for(int i=0;i<m;i++){
    int a,b,c;
    cin >> a >> b >> c;
    g[a].pb(pii(b,c));
    g[b].pb(pii(a,c));
  }
  int K = n - m;
  
  
  ans[min(K*x,y)] = pii(K*x,1);

  for(int a=1;a<=n;a++){
    if(!vis[a]){

      vi v = get(a);
      vector<pii> dp = build(v);

      map<int,pii> mp;
      for(int i=0;i<=y;i++){
        if(dp[i].ss)mp[i]=dp[i];
      } 
      

      for(int i=0;i<=y;i++){
          temp[i] = ans[i];
          ans[i] = pii(0,0);
      }
      for(auto it : mp){
        for(int i=0;i<=y;i++){
          ans[min(i + it.ff,y)] = (ans[min(i+it.ff,y)] + join(temp[i],it.ss));
        }

      }

    }
  }

  ll res = ans[y].ff;

  for(int i=1;i<K;i++)res = res * i %M;
  for(int i=1;i<K;i++)res = res * 2ll%M;
  
  cout << res << endl;  

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
