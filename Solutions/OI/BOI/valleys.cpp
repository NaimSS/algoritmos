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

template<class T = long long>
struct Tree{ // peso é INT!!!
  int N,MAXL,Root;
  vector<vector<pair<int,int>> > g;
  vector<vi> ans;
  vi tin,tout;
  vi H,tam;
  vector<T> D;
  vector<vector<T>> dp;
  vi isshop;
  Tree(){}
  Tree(int n,int _MAXL = 20){
    N = n;
    MAXL = _MAXL;
    isshop = tam = H = tin = tout = vi(n+1,0);
    g.resize(n + 1);
    ans = vector<vi>(n+1,vi(MAXL,0));
    dp = vector<vector<T>>(n+1,vector<T>(MAXL,0));
    t=0;

    D = vector<T>(n+1,0);
  }
  int t;
  
  const ll inf = 1e18;
  T dfs(int v,int p = -1){
    tin[v] = ++t;
    tam[v]=1;
    T val = inf;
    if(isshop[v])val = - D[v];

    for(auto to : g[v])if(to.ff!=p){
      H[to.ff] = H[v] + 1;
      D[to.ff] = D[v] + to.ss;
      ans[to.ff][0] = v;
      val = min(val,dfs(to.ff,v) - 2 * D[v]);

      tam[v]+=tam[to.ff];
    }
    tout[v] = ++t;
    dp[v][0] = val;
    return val + 2 * D[v];
  }
  
  void init(int _Root){
    t=0;Root = _Root;
    // assuming conected!!!
    ans[Root][0] = Root;
    H[Root] = D[Root] = 0;
    for(int i=1;i<=N;i++){
      for(int j=0;j<MAXL;j++)dp[i][j] = inf;
    }
    dfs(Root);

    for(int j=1;j<MAXL;j++){
      for(int i=1;i<=N;i++){
        ans[i][j] = ans[ans[i][j-1]][j-1];
        dp[i][j] = min(dp[i][j-1],dp[ans[i][j-1]][j-1]);
      }
    }
  }
  void addEdge(int a,int b,int c){
    g[a].pb(pii(b,c));
    g[b].pb(pii(a,c));
  }

  bool is_ans(int a,int b){
    return tin[a]<=tin[b] and tout[a]>=tout[b]; 
  }
  int lca(int a,int b){

    if(H[a] < H[b])swap(a,b);
    for(int j=MAXL-1;j>=0;j--){
      if(H[a] - (1<<j) >= H[b]){
        a=ans[a][j];
      }
    }
    if(a==b)return a;
    for(int j=MAXL-1;j>=0;j--){
      if(ans[a][j]!=ans[b][j]){
        a=ans[a][j],b=ans[b][j];
      }
    }
    return ans[a][0];
  }
  int dist(int a,int b){
    return H[a] + H[b] - 2*H[lca(a,b)]; 
  }
  int up(int v,int k){
    for(int j=MAXL-1;j>=0;j--){
      if(k&(1<<j))v = ans[v][j];
    } 
    return v;
  }
  // for Valleys:
  
  bool inpath(int a,int b,int c){
    int L = lca(a,b);
   
    if(c == L)return 1;
    if(!is_ans(c,a) and !is_ans(c,b))return 0;
    if(is_ans(c,L) and c!=L)return 0;
    return 1;
  }
  T get(int a,int d){
    T val = inf;
    int ini = a;
    for(int j=MAXL-1;j>=0;j--){
      if(d&(1<<j)){
        val = min(val,dp[a][j] + D[ini]);
        a = ans[a][j];
      }
    }
    return val;
  }
  T solve(int v,int A,int B){
    if(ans[A][0] != B)swap(A,B);
    if(!inpath(v,Root,A) || !inpath(v,Root,B))return -1;
    return get(v,dist(v,B));
  }


};

const int N = 100100;
pii ar[N];

int32_t main(){
  fastio;
  int n,s,q,e;
  cin >> n >> s >> q >> e;
  Tree<ll> tree(n);
  for(int i=1;i<=n-1;i++){
    int a,b,c;
    cin>>a>>b>>c;
    tree.addEdge(a,b,c);
    ar[i] = pii(a,b);
  }
  for(int i=0;i<s;i++){
    int x;
    cin>>x;
    tree.isshop[x] = 1;
  }
  tree.init(e);
  while(q--){
    int I,R;
    cin >> I >> R;
    int a = ar[I].ff,b = ar[I].ss;
    ll res = tree.solve(R,a,b);
    if(res == -1)cout<<"escaped"<<endl;
    else if(res == tree.inf)cout <<"oo"<<endl;
    else cout << res << endl;
  }


  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
