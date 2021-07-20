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

const int N = 50100;
const int L = 17;
vector<pii> vai[N][L];

vector<pii> g[N];

int k,n,m,q;

void preprocess(){
  for(int i=0;i<n;i++){
    for(auto it : g[i]){
      vai[i][0].pb(it);
    }
  }
  for(int j=1;j<L;j++){
    for(int i=0;i<n;i++){
      map<int,int> dist;
      for(auto it : vai[i][j-1]){

        for(auto ind : vai[it.ff][j-1]){
          if(dist.count(ind.ff)){
            dist[ind.ff] = min(dist[ind.ff],ind.ss + it.ss);
          }else{
            dist[ind.ff] = ind.ss + it.ss;
          }
        }

      }
      for(auto it : dist){
        vai[i][j].pb(it);

      }
    }
  }
}

const int inf = 1e9;

int32_t main(){
  fastio;
  cin >> k >> n >> m >> q;

  for(int i=0;i<m;i++){
    int a,b,t;
    cin>>a>>b>>t;
    g[a].pb(pii(b,t));
  }

  preprocess();
  while(q--){
    int a,b;
    cin>>a>>b;
    vector<pii> act;
    act.pb(pii(a,0));
    int l = a/k;
    int need = b/k;
    int dif = need - l;
    for(int j=L-1;j>=0;j--){
      if(dif&(1<<j)){
        map<int,int>dist;
        
        for(auto it : act){

          for(auto go : vai[it.ff][j]){
            if(dist.count(go.ff)){
              dist[go.ff] = min(dist[go.ff],it.ss + go.ss);
            }else dist[go.ff] = go.ss + it.ss;

          }
        }

        act.clear();
        for(auto it : dist){
          act.pb(it);
        }

      }
    }
    int mn = inf;
    for(auto it : act){
      if(it.ff == b)mn = min(mn,it.ss);
    }
    if(mn != inf)cout << mn << endl;
    else cout << -1 << endl;
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
