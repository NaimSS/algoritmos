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
#define prl cerr<<"called: "<< __LINE__<<endl;
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

const int N = 1e6 + 1;
vi rg[N];
int F[N];
int pai[N];
bool vis[N];
pii ans;
vi cic;
bool incic[N];
void dfs(int v){
  if(incic[v])return;
  if(vis[v] == 1){
    int cur = pai[v];
    cic.pb(v);
    while(cur!=v){
      if(pai[cur] == 0){
        break;
      }
      cic.pb(cur);
      cur = pai[cur];
    }
    return;
  }
  vis[v] = 1;
  pai[F[v]] = v;
  dfs(F[v]);
}

int bad(int v,int p){
  vis[v] = 1;
  bool leaf = 1;
  int res=0;
  for(int to : rg[v]){
    if(to!=p){
      leaf=0;
      res+=bad(to,v);
    }
  }
  res+=leaf;
  return res;
}

bool done[N];
//dp[v][eu atiro ou nao] = menor qtd de mortos na subarvore
int curans=0;
void dfs_dp(int v,int p){
  for(int to : rg[v])if(to!=p){
    dfs_dp(to,v);
    if(!done[v] and !done[to]){
      done[v] = done[to] = 1;
      curans++;
    }
  }

}

void solve(int v,int p){
  // for maximum:
  curans=0;
  ans.ss -= bad(v,p);
  dfs_dp(v,-1);
  ans.ff+=curans;
}

bool die[N];

void go(int v){
  cic.clear();
  dfs(v);

  for(int c : cic){
    incic[c] = 1;
  }
  bool flag = 1;
  for(int iter=0;iter<sz(cic);iter++){
   

    int c = cic[iter];
    for(int o : rg[c]){
      if(!incic[o]){
        flag = 0;
        // here is a tree:
        solve(o,c);
        if(!done[o] and !done[c]){
          done[o] = done[c] = 1;
          ans.ff++;
        }
    }
    }
    
  }

  if(sz(cic) == 1)flag = 0;
  ans.ss-=flag;

  int st = -1;
  for(int i=0;i<sz(cic);i++){
    if(done[cic[i]]){
      st = i;
      break;
    }
  }
  if(st == -1){
    ans.ff+=(sz(cic) + 1)/2;
    return;
  }
  rotate(cic.begin(),cic.begin() + st,cic.end());
  assert(done[cic[0]]);
  int tam=0;
  for(int j = 0;j<sz(cic);j++){
    if(done[cic[j]]){
      ans.ff+=(tam/2);
      tam=0;
    }else tam++;
  }
  ans.ff+=(tam/2);
}

int32_t main(){
  fastio;
  int n;
  cin>>n;
  ans.ss = n;
  for(int i=1;i<=n;i++){
    int x;
    cin>>x;
    F[i] = x;
    rg[F[i]].pb(i);
  }
  for(int i=1;i<=n;i++){
    if(!vis[i]){
      go(i);
    }
  }
  assert(ans.ff<=ans.ss);
  cout << ans.ff<<" "<<ans.ss << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
