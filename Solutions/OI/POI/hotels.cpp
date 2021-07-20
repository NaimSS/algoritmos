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

const int N = 5050;

int H[N];
int n;
vi g[N];
int tin[N],tout[N];
int t=0;
int rev[N];

void dfs(int v,int p = -1){
  tin[v] = ++t;
  rev[t] = v;
  
  assert(t<=n);

  for(int to : g[v])if(to!=p){
    H[to] = H[v] + 1;
    dfs(to,v);
  }
  tout[v] = t;
}

ll ans=0;

ll dp[N][5];
int sla[N];
bool used[N];
bool sub[N];

bool is_ans(int to,int x){
  return tin[to]<=tin[x] and tout[to]>=tout[x];
}

void calc(int v,int p = -1){
   
  for(int i=0;i<=n;i++){
    dp[i][0] = 1;
    dp[i][1] = dp[i][2] = dp[i][3] = 0;
    sub[i]=0;
    sla[i]=used[i]=0;
  }
  
  for(int to : g[v])if(to!=p){
    int l = tin[to],r = tout[to];
    
    for(int ii=l;ii<=r;ii++){
      int i = rev[ii];
      sla[H[i]]++;
      used[H[i]] = 0;
      sub[i] = 1;
    }
    for(int ii=l;ii<=r;ii++){
      int i = rev[ii];
      if(!used[H[i]]){
        used[H[i]]=1;
        for(int j=2;j>=0;j--){
          dp[H[i]][j+1]+=sla[H[i]]*dp[H[i]][j];
        }
        
        sla[H[i]]=0;
      }
    }
  }
  for(int i=1;i<=n;i++){
    if(!sub[i]){
      sla[H[i]]++;
      used[H[i]]=0;
    }
  }
  for(int i=1;i<=n;i++){
    if(!sub[i] and !used[H[i]]){
      used[H[i]]=1;
      
      for(int j=2;j>=0;j--){
        dp[H[i]][j+1]+=sla[H[i]]*dp[H[i]][j];
      }
      sla[H[i]]=0;
    }
  }
  for(int i=1;i<=n;i++){
    ans+=dp[i][3];
    dp[i][0] = dp[i][1] = dp[i][2] = dp[i][3] = 0;
    sla[H[i]] = sub[i] = used[i] = 0;
  }

  for(int to : g[v])if(to!=p){
    // reroot:
    for(int x=1;x<=n;x++){
       
      if(is_ans(to,x)){
        H[x]--;
      }else{
        H[x]++;
      }
    
    }
    calc(to,v);
    // roolback:
    for(int x=1;x<=n;x++){
      
      if(is_ans(to,x)){
        H[x]++;
      }else{
        H[x]--;
      }
      
    }
  }

}

int32_t main(){
  fastio;
  cin >> n;
  for(int i=0;i<n-1;i++){
    int a,b;
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
  }
  dfs(1);
  calc(1);

  cout << ans << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
