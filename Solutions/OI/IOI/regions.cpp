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

const int N = 200100;
const int R = 25100;
const int sq = 700;
int ans[R/sq][R];
int cnt[N];

vi g[N];
vi here[R];
vi tempo[R];
int tin[N],tout[N],t;
int H[N];
int ar[N];
int A[2*N],T=0;
void dfs(int v){
  A[++T]=v;
  tin[v] = ++t;ar[t] = H[v];
  tempo[H[v]].pb(t);  
  for(int to : g[v])dfs(to);
  tout[v] = t;
  A[++T]=v;
}
int id[N],rev[N];

int cur=0;

bool vis[N];
int32_t main(){
  fastio;
  int n,r,q;
  cin>>n>>r>>q;
  for(int i=1;i<=n;i++){
    if(i == 1){
      cin >> H[i];
    }else{
      int p;
      cin >> p >> H[i];
      g[p].pb(i);
    }
    here[H[i]].pb(i);
    cnt[H[i]]++;
  }
  dfs(1);
  rep(i,0,R)sort(all(tempo[i]));
  int ck = 0;
  for(int i=1;i<=r;i++){
    if(cnt[i]>=sq){
      id[++ck] = i;
      rev[i] = ck;
      for(int t=1;t<=T;t++){
        if(vis[A[t]]){
          vis[A[t]]=0;
          if(H[A[t]] == i)cur--;
        }else{
          vis[A[t]]=1;
          if(H[A[t]]==i)cur++;
          else ans[ck][H[A[t]]]+=cur;
        }
      }

      assert(cur == 0);
    }
  }

  while(q--){
    int r1,r2;
    cin >> r1 >> r2;
    if(rev[r1] > 0){
      cout << ans[rev[r1]][r2]<< endl;
    }else{
      int res=0;
      for(int k : here[r1]){
        res+=upper_bound(all(tempo[r2]),tout[k]) - lower_bound(all(tempo[r2]),tin[k]);
      }
      cout << res << endl;
    }
    cout.flush();
  }
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
