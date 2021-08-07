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

const int N = 1e5 + 100;
ll d[N];
typedef pair<ll,ll> pll;
vector<pll> g[N];
int vis[N];
int SLA=0;
map<pii,int> mp;
int n;

ll dist[N][4];

struct coisa{
  int v,j;
  ll d;
  coisa(){}
  coisa(ll d,int v,int j):d(d),v(v),j(j){}
  bool operator<(const coisa& o )const{
    return d > o.d;
  }
};

bool mark[N][4];
struct edge{
  int v,w,j;
  edge(){}
  edge(int v,int w,int j):v(v),w(w),j(j){}
};

vector<edge> adj[N];

void DJ2(int U,int V){
    rep(i,0,N)rep(j,0,4){
      dist[i][j] = 1e18;
      mark[i][j] = 0;
    }
    dist[U][0] = 0;
    priority_queue<coisa> pq;
    pq.push(coisa(0,U,0));
    while(!pq.empty()){
      int cur = pq.top().v,j = pq.top().j;
      pq.pop();
      if(mark[cur][j])continue;
      mark[cur][j]=1;

      for(auto e : adj[cur]){
        int to = e.v;
        ll w = e.w;
        int t = e.j;

        if(t == 3){
          // ababa
          if(j==0 and dist[to][0] > dist[cur][j] + w){
            pq.push(coisa(dist[to][0] = dist[cur][j] + w,to,0));
          }
          if(dist[to][3] > dist[cur][j] + w){
            pq.push(coisa(dist[to][3] = dist[cur][j] + w,to,3));
          }
        }else if(t==1){
          // only j == 0 or j == 1 can pick
          if(j ==0 || j == 1){
            if(dist[to][1] > dist[cur][j] + w){
                pq.push(coisa(dist[to][1] = dist[cur][j] + w,to,1));
            }
          }
        }else if(t==2){
           // only j == 0 or j == 2 can pick
          if(j == 0 || j == 2){
            if(dist[to][2] > dist[cur][j] + w){
                pq.push(coisa(dist[to][2] = dist[cur][j] + w,to,2));
            }
          }
        }

      }

    }
    cout << min({dist[V][0],dist[V][1],
      dist[V][2],dist[V][3]}) << endl;
}


void DJ(int S,int T){
  for(int i=0;i<N;i++)d[i] = 1e18,vis[i]=0;
  d[S] = 0;
  mp.clear();
  priority_queue<pll,vector<pll>,greater<pll> > pq;
  pq.push(pll(d[S],S));
  while(!pq.empty()){
    int cur = pq.top().ss;
    if(d[cur]!=pq.top().ff){
      pq.pop();continue;
    }
    pq.pop();
    for(auto to : g[cur]){
      if(d[to.ff] > d[cur] + to.ss){
        d[to.ff] = d[cur] + to.ss;
        pq.push(pll(d[to.ff],to.ff));
      }
    }
  }
 
  queue<int> q;
  q.push(T);
  while(!q.empty()){
    int cur = q.front();q.pop();
    vis[cur] = 1;
    for(auto to : g[cur]){
      if(d[to.ff] + to.ss == d[cur]){
          mp[pii(to.ff,cur)] = 1;
        if(!vis[to.ff]){
          vis[to.ff] = 1;
          q.push(to.ff);
        }
      }
    }
  }
  rep(i,0,N){
    int cur = i;
    for(auto to : g[i]){
      if(mp[pii(to.ff,cur)]){
        adj[i].pb(edge(to.ff,0,1));
      }else if(mp[pii(cur,to.ff)]){
        adj[i].pb(edge(to.ff,0,2));
      }
      adj[i].pb(edge(to.ff,to.ss,3));
    }
  }

}

int32_t main(){
  fastio;
  int m;
  cin >> n >> m;
  int S,T;
  cin >> S >> T;
  int U,V;
  cin >> U >> V;
  for(int i=0;i<m;i++){
    int a,b,c;
    cin >> a >> b >> c;
    g[a].pb(pii(b,c));
    g[b].pb(pii(a,c));
  }
  DJ(S,T);

  DJ2(U,V);

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
