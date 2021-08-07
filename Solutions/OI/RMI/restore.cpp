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
//#define int long long  
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left oooooopss
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b,ll e,ll m){
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
      if (e & 1) ans = ans * b % m;
  return ans;
}
const int N = 5050;
vector<pii> g[N];
int dist[N];
int inQ[N];
int visi[N];
int n,m;
const int inf = 1e9;
void NO(){
  cout << -1 << endl;
  exit(0);
}
void SPFA(int S){
  for(int i=0;i<N;i++)dist[i]=inf,inQ[i]=visi[i]=0;
  queue<int> q;
  q.push(S);
  inQ[S]=1;
  dist[S]=0;
  while(!q.empty()){
    int cur = q.front();
    q.pop();
    inQ[cur]=0;
    for(auto to : g[cur]){
      if(dist[to.ff] > dist[cur] + to.ss){
        if(visi[to.ff] > 2*m)
          NO();
        visi[to.ff]++;
        dist[to.ff] = dist[cur] + to.ss;
        if(dist[to.ff] < 0){
          NO();
        }
        if(!inQ[to.ff]){
          q.push(to.ff);
          inQ[to.ff]=1;
        }
      }
    }
  }
  for(int i=0;i<N;i++)if(dist[i]<0)NO();
}

int32_t main(){
  fastio;
  cin >> n >> m;
  for(int i=0;i<m;i++){
    int l,r,k,v;
    cin >> l >> r >> k >> v;
    l++;
    r++;
    if(v == 0){ // xl-1 - xr <= -k
      g[r].pb(pii(l-1,-k));
    }else{ 
      // xr - xl-1 < k 0's
      // xr - xl-1 <= k-1
      g[l-1].pb(pii(r,k-1));
    }
  }
  for(int i=1;i<=n;i++){
    g[i-1].pb(pii(i,1));
    g[i].pb(pii(i-1,0));
  }
  SPFA(0);
  for(int i=1;i<=n;i++){
    cout << ((dist[i] - dist[i-1])^1) << " ";
  }
  cout << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
