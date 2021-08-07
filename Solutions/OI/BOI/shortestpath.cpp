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

const int M = 1e5 + 100,N = 2500;
struct edge{
  int a,b,c;
  edge(){}
  edge(int a,int b,int c):a(a),b(b),c(c){}
}e[M];

vi g[N];
int pai[N],idpai[N];
int n;
int W[N];
void DJ(int S,vi& d){
  vi vis(n+1,false);
  d.resize(n + 1);rep(i,1,n+1)d[i] = 1e9,pai[i] = -1;
  d[S]=0;
  priority_queue<pii,vector<pii>,greater<pii> > pq;
  pq.push(pii(d[S],S));
  while(!pq.empty()){
    int cur = pq.top().ss;
    pq.pop();if(vis[cur])continue;
    vis[cur]=1;
    for(int id : g[cur]){
      int to = e[id].a^e[id].b^cur;
      int w = e[id].c;
      if(d[to] > d[cur] + w){
        pai[to] = cur;idpai[to] = id;
        W[to] = w;
        pq.push(pii(d[to] = d[cur] + w,to));
      }
    }
  }
 // cout <<"Here "<< S << endl;
 // for(int i=1;i<=n;i++)cout << d[i] << endl;
}
vector<pii> adj[N];

int rep[N];
int pos[N];

void representante(vi path){
  priority_queue<pii,vector<pii>,greater<pii> > pq;
  vi d(n + 1),vis(n+1);
  for(int i=1;i<=n;i++)d[i] = 1e9,vis[i] = 0;
  for(int i=0;i<sz(path);i++){
    int x = path[i];
    d[x] = 0;
    pos[x] = i;
    pq.push(pii(0,x));
    rep[x] = x;
  }
  while(!pq.empty()){
    int cur = pq.top().ss;pq.pop();
    if(vis[cur])continue;
    vis[cur]=1;
    for(auto to : adj[cur]){
      if(d[to.ff] > d[cur] + to.ss){
        rep[to.ff] = rep[cur];
        pq.push(pii(d[to.ff] = d[cur] + to.ss,to.ff));
      }
    }
  }

}
bool used[M];


int ans[N];
int32_t main(){
  fastio;
  int m,S,T;
  cin >> n >> m >> S >> T;
  for(int i=0;i<m;i++){
    cin >> e[i].a >> e[i].b >> e[i].c;
    g[e[i].a].pb(i);
    g[e[i].b].pb(i);
  }
  vi d1,d2;
  DJ(T,d2);
  DJ(S,d1);

  int k;
  cin >> k;
  vi path(k);
  for(int i=0;i<k;i++){
    cin >> path[i];
    ans[path[i]] = 1e9 + 18273;
    if(i){
      pai[path[i]] = path[i-1];
      for(int id : g[path[i-1]]){
        if(e[id].a+e[id].b-path[i-1] == path[i]){
          W[path[i]] = e[id].c;
          idpai[path[i]] = id;
        }
      }
    }
  }

  // build DJ tree:
  for(int i=1;i<=n;i++){
    if(pai[i]!=-1){
      adj[i].pb(pii(pai[i],W[i]));
      adj[pai[i]].pb(pii(i,W[i]));
      used[idpai[i]] = 1;
    }
  }
  // acha o representante de cada cara:
  representante(path);
  
  for(int i=0;i<m;i++){
    if(!used[i]){
      int a = e[i].a;
      int b = e[i].b;
      int w = e[i].c;
      if(pos[rep[a]] > pos[rep[b]])swap(a,b);
      // update de [rep[a],rep[b]):
      for(int j=pos[rep[a]];j<pos[rep[b]];j++){
    
        ans[path[j]] = min(ans[path[j]],d1[a] + w + d2[b]);
      }
    }
  }

  for(int i=0;i<k-1;i++){
    if(ans[path[i]] > 1e9)cout << -1 << endl;
    else cout << ans[path[i]] << endl;
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
