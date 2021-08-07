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
#define db(x) cerr <<#x <<" == "<<x << endl;
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


const int N = 100100;
vi g[N],rg[N],adj[N];
int deg[N];
int d[N];
bool vis[N];
int ok[N];
void dfs(int v,int p = -1){
  if(sz(g[v]))return ;
  ok[v]=1;
  for(int to : adj[v])if(to!=p)dfs(to,v);
}

int32_t main(){
  fastio;
    ifstream cin("gathering.in");
  ofstream cout("gathering.out");
  int n,m;
  cin>>n>>m;
  for(int i=1;i<n;i++){
    int a,b;
    cin>>a>>b;
    adj[a].pb(b);
    adj[b].pb(a);
    d[a]++;d[b]++;
  }
  for(int i=0;i<m;i++){
    int a,b;
    cin>>a>>b;
    deg[b]++;
    g[a].pb(b);
    rg[b].pb(a);
  }
  queue<int> q;
  for(int i=1;i<=n;i++){
    if(d[i] ==  1 and deg[i]==0)q.push(i),vis[i]=1;
  }
  int last=0;
  rep(iter,0,n){
    if(q.empty()){
      rep(i,0,n)cout<<"0\n";
      return 0;
    }
    int cur = q.front();q.pop();
    last=cur;
    for(int to : g[cur]){
      deg[to]--;
      if(d[to]<=1 and deg[to]==0 and !vis[to]){
        vis[to]=1;q.push(to);
      }
    }
    for(int to : adj[cur]){
      d[to]--;
      if(d[to]<=1 and deg[to]==0 and !vis[to]){
        q.push(to);
        vis[to]=1;
      }
    }
  }
  dfs(last);
  for(int i=1;i<=n;i++)cout<<ok[i]<<endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
