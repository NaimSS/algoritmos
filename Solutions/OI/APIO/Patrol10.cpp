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

struct Tree{
  vector<vi> g;
  int N;
  vi dist;
  vi mx;
  vi up;
  int dp[100100][2];
  Tree(){}
  Tree(int n){
    N = n;
    g.resize(N+1,vi());
    dist.resize(N+1,0);
    mx.resize(N+1,0);
    up.resize(N+1,0);
    for(int i=0;i<=N;i++){
      dist[i] = mx[i] = up[i] = 0;
    }
  }
  void addEdge(int a,int b){
    g[a].pb(b);
    g[b].pb(a);
  }

  void dfs(int v,int p,vi& d){
    if(p==-1)d[v]=0;
    for(int to : g[v])if(to!=p){
      d[to] = d[v] + 1;
      dfs(to,v,d);
    }
  }
  int ans=0;
  int SLA(int v,int p,bool print = 0){
    if(print)cout << v<<" ";
    if(v == -1)return -1;
    int res = 0;
    for(int to : g[v])if(to!=p){
      res = max(res,1 + SLA(to,v));
    }
    for(int to : g[v])if(print and to!=p and res == SLA(to,v) + 1){
      SLA(to,v,1);
      break;
    }
    return res;
  }
  void my_assert(bool x,int v,int p){
    if(!x){
      assert(false);
      cout <<"ops "<<v<<" "<<up[v]<<" "<<SLA(p,v)<<endl;
      cout << p << endl;
      SLA(p,v,1);
      exit(0);
    }
  }

  void solve(int v,int p = -1){
    int cur=0;
    
    ans = max(ans,max(dp[v][0],dp[v][1]));


    vi Best1;
    vector<pii> best1;
    for(int i=0;i<sz(g[v]);i++){
      if(g[v][i]!=p)dp[g[v][i]][1] = mx[g[v][i]] - dist[v];
      int to1 = g[v][i];
      Best1.pb(max(dp[to1][0],dp[to1][1]));
      best1.pb(pii(dp[to1][1],to1));
    }
    
    sort(all(Best1),greater<int>());
    sort(all(best1),greater<pii>());

    if(sz(Best1))cur = max(cur,Best1[0]);
    if(sz(Best1) > 1){
      cur = max(cur,Best1[0] + Best1[1]);
    }
    
    for(int k=0;k<sz(g[v]);k++){
      int to3 = g[v][k];
      int pegou = 0;
      int tem = max(dp[to3][1],dp[to3][0]);
//      if(v == 5)cout<< to3<<" "<<dp[to3][0]<<" "<<dp[to3][1]<<endl;
      for(int i=0;i<4;i++){
        if(pegou == 2 || i == sz(best1))break;
        if(best1[i].ss == to3)continue;
        pegou++;
        tem+=best1[i].ff;
      }
      cur = max(cur,tem);
    }
    
    if(sz(best1) >= 4){
      int tem=0;
      rep(i,0,4)tem+=best1[i].ff;
      cur = max(cur,tem);

    } 

    
    ans = max(ans,cur);
    vector<pii> sla;
    for(int i=0;i < sz(g[v]);i++){
      if(g[v][i]!=p)sla.pb(pii(mx[g[v][i]] - dist[v],g[v][i]));
    }
    sort(all(sla),greater<pii>());

    best1.clear();
    Best1.clear();

    vector<pii> best0;
    for(int to : g[v]){
      if(to == p)best1.pb(pii(up[v],p));
      else best1.pb(pii(mx[to] - dist[v],to));
      best0.pb(pii(dp[to][0],to));
    }

    sort(all(best0),greater<pii>());
    sort(all(best1),greater<pii>());
    for(int i=0;i<sz(g[v]);i++){
      int to = g[v][i];
      if(to == p)continue;
      up[to] = up[v] + 1;
      if(sz(sla) > 0 and to != sla[0].ss)up[to] = max(up[to],sla[0].ff + 1);
      else if(sz(sla) > 1 and to!=sla[1].ss)up[to] = max(up[to],sla[1].ff+1);
      else if(sz(sla) > 2 and to!=sla[2].ss)up[to] = max(up[to],sla[2].ff+1);

      dp[v][1] = up[to];
      dp[v][0] = 0;
      vi best;
      for(int j=0;j<3;j++){
        if(j == sz(best0))break;
        if(best0[j].ss == to)continue;
        dp[v][0] = max(dp[v][0],best0[j].ff);
        
        break;
      }
      
      int tem=0;
      int pegou=0;
      for(int j=0;j<4;j++){
        if(j == sz(best1))break;
        if(pegou == 2)break;
        if(to!=best1[j].ss){
          tem+=best1[j].ff;
          pegou++;
        }
      }
      dp[v][0] = max(dp[v][0],tem);
     
      
      pii antes = pii(dp[to][0],dp[to][1]);
      solve(to,v);
      dp[to][0] = antes.ff;
      dp[to][1] = antes.ss;
    }

  }

  void pre(int v,int p = -1){
    dp[v][0] = 0;
    dp[v][1] = 0;
    mx[v] = dist[v];
    assert(dist[v] < N);
    vi best;
    for(int to : g[v])if(to!=p){
      dist[to] = dist[v] + 1;
      pre(to,v);
      mx[v] = max(mx[v],mx[to]);
      best.pb(mx[to] - dist[v]);
      dp[v][0] = max(dp[v][0],dp[to][0]);
    }
    
    sort(all(best),greater<int>());
    if(sz(best) == 0)dp[v][0] = max(dp[v][0],0);
    else if(sz(best) == 1)dp[v][0] = max(dp[v][0],best[0]);
    else dp[v][0] = max(dp[v][0],best[0] + best[1]);
    
    dp[v][1] = mx[v];
  }


  int gogo(){
    dist[1] = 0;
    pre(1,-1);
    up[1] = 0;
   
    solve(1,-1);
    return 2*(N-1) - ans + 2;
  }

  int diametro(){
    vi d[2];
    int root = 1;
    int ponta[2]={0,0};// pontas do diametro
    rep(it,0,2){
      d[it].resize(N+1,0);
      dfs(root,-1,d[it]);
      int best=-1,id=0;
      for(int i=1;i<=N;i++)if(d[it][i] > best){
        best = d[it][i];
        id = i;
      }
      root = id;
      ponta[it] = id;
    }
    dfs(ponta[0],-1,d[0]);dfs(ponta[1],-1,d[1]);
    // max(d[0][i],d[1][i]) == maior distancia pra alguma folha
    int diam=0;
    for(int i=1;i<=N;i++){
      diam = max(diam,max(d[0][i],d[1][i]));
    }
    return diam;
  }

};
int32_t main(){
  fastio;
  int n,k;
  cin >> n >> k;
  Tree tree(n);
  for(int i=0;i<n-1;i++){
    int a,b;
    cin >> a >> b;
    
    tree.addEdge(a,b);
  }
  int res = 0;
  if(k == 1)res = 2*(n-1) - tree.diametro() + 1;
  else res = tree.gogo();
  cout << res << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
