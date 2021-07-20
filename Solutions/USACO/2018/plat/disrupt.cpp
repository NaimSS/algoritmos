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
#define sz(v) ((int)v.size())
//#define int long long
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

const int N = 100100,MAXL = 20,inf = 1e9 + 7;

int ans[N][MAXL];
int dp[N][MAXL];
vi g[N];
int H[N];
void dfs(int v,int p = -1){
  
  for(int to : g[v])if(to!=p){
    ans[to][0] = v;
    H[to] = H[v] + 1;
    dfs(to,v);
  }
}
int lca(int a,int b,int c){
  if(H[a] < H[b])swap(a,b);
  for(int i=MAXL-1;i>=0;i--){
    if(H[a] - (1<<i) >= H[b]){
      dp[a][i] = min(dp[a][i],c);
      a=ans[a][i];
    }
  }
  if(a==b)return a;
  for(int i=MAXL-1;i>=0;i--)
    if(ans[a][i]!=ans[b][i]){
      dp[a][i] = min(dp[a][i],c);
      dp[b][i] = min(dp[b][i],c);
      a=ans[a][i];

      b=ans[b][i];
    }
    dp[a][0]=min(dp[a][0],c);
    dp[b][0]=min(dp[b][0],c);
  return ans[a][0];
}


pii e[N];
int32_t main(){
  fastio;
  ifstream cin("disrupt.in");
  ofstream cout("disrupt.out");
  int n,q;
  cin >> n >> q;
  for(int i=1;i<n;i++){
    int a,b;cin>>a>>b;
    g[a].pb(b);
    g[b].pb(a);
    e[i] = pii(a,b);
  }
  ans[1][0]=1;
  dfs(1);
  rep(j,0,MAXL)rep(i,0,N)dp[i][j]=inf;
  for(int j=1;j<MAXL;j++){
    for(int i=1;i<=n;i++){
      ans[i][j] = ans[ans[i][j-1]][j-1];
    }
  }
  while(q--){
    int a,b,c;
    cin>>a>>b>>c;
    lca(a,b,c);
  }

  for(int j=MAXL-1;j>0;j--){
    for(int i=1;i<=n;i++){
      dp[ans[i][j-1]][j-1] = min(dp[ans[i][j-1]][j-1],dp[i][j]);
      dp[i][j-1]=min(dp[i][j-1],dp[i][j]);
    }
  }

  for(int i=1;i<n;i++){
    if(ans[e[i].ff][0]!=e[i].ss)swap(e[i].ff,e[i].ss);
    if(dp[e[i].ff][0]==inf)dp[e[i].ff][0]=-1;
    cout << dp[e[i].ff][0]<<endl;
  }
  

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
