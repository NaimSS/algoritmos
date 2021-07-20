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


const int N = 305;
int n,m;

int mx[N][N][N];

int dp[N][N];
bool vis[N][N];

int solve(int l,int r){
  if(l>r)return 0;
  if(vis[l][r])return dp[l][r];
  vis[l][r]=1;
  dp[l][r]=0;
  for(int k=l;k<r;k++){
    dp[l][r]=max(dp[l][r],solve(l,k) + solve(k+1,r));
  }
  for(int i=l;i<=r;i++){
    dp[l][r]=max(dp[l][r],
      solve(l,i-1) + solve(i+1,r) + mx[l][r][i]
      );
  }
  return dp[l][r];
}


int w[N*N],l[N*N],r[N*N];

vi add[N];
vi put[N];
int best[N];
int32_t main(){
  fastio;
  
  freopen("pieaters.in" , "r" , stdin);
  freopen("pieaters.out" , "w" , stdout);
  
  cin >> n >> m;

  for(int i=0;i<m;i++){
    cin >> w[i] >> l[i] >> r[i];
    add[l[i]].pb(i);
    assert(l[i]<=n and r[i]<=n);
  }
  

  for(int L=1;L<=n;L++){
    for(int R=L;R<=n;R++)put[R].clear(),best[R]=0;

    for(int R=L;R<=n;R++){
      for(int id : add[R]){
        assert(l[id] == R);
        put[r[id]].pb(id);
      }

      for(int id : put[R]){
      //  assert(L<=l[id] and r[id]<=R);

        for(int x=l[id];x<=r[id];x++){
          best[x] = max(best[x],w[id]);
        }
      }
      put[R].clear();


      for(int i=L;i<=R;i++){
        mx[L][R][i] = best[i];
      }

    }

  }

  cout << solve(1,n) << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
