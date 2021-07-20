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

const int N = 2020;
ll cost[N][N];


ll have[N][N];

ll brute(int l,int r){
  ll res=0;
  for(int i=1;i<=l;i++){
    for(int j=r;j<N;j++){
      res+=have[i][j];
    }
  }
  return res;
}

ll Cost(int l,int r){
  assert(l<r);
  return cost[r][r] - cost[l][r];
}

struct DP{
  int n , inf; 
  vi dp[2];
  DP(int n , int inf) : n(n) , inf(inf) {dp[0] = vi(n+1) , dp[1] = vi(n+1);}
  // compute dp_cur[l], ... dp_cur[r] (inclusive) 
  void compute(int l, int r, int optl, int optr){
      if (l > r) return;
      int mid = l + (r-l)/2;
      pair<int, int> best = {-inf, -1}; // se for maximizar muda pra -inf
      rep(k,optl,min(mid,optr)+1){
          best = max(best, { dp[0][k-1] + Cost(k-1,mid), k});
      }
      dp[1][mid] = best.first; int opt = best.second;
      compute(l, mid - 1, optl, opt);
      compute(mid + 1, r, opt, optr);
  }
  void solve(int k){
    dp[0][0]=0;
    rep(i,1,n+1){
      dp[0][i] = cost[i][i];
    }
    int mx=0;
    for(auto it : dp[0])mx=max(mx,it);
    cout << mx << endl;
    rep(i,2,k+1){
      rep(j,0,i)dp[1][j] = dp[0][j];
      rep(j,i,n+1) dp[1][j] = inf;
      compute(i,n,i,n);
      swap(dp[0] , dp[1]);
      for(auto it : dp[0])mx=max(mx,it);
      cout << mx << endl;

    }
  }
};

const int inf = 2e9 + 1000;
char mat[N][N];
int vis[N][N];
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};


vector<pll> add[N];
vi rem[N];

ll val[N];

int n,m;
int ok(int l,int c){
  return l>=1 and l<=n and c>=1 and c<=m and !vis[l][c] and mat[l][c]!='.';  
}

int32_t main(){
  fastio;

  cin >> n >> m;
  DP dp(m,inf);
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      cin >> mat[i][j];
    }
  }

  rep(i,1,n+1)rep(j,1,m+1){
    if(!vis[i][j] and mat[i][j]!='.'){
        int A=0,B=0;
        queue<pii> q;
        q.push(pii(i,j));

        int t=0;
        int l=j,r=j;
        vis[i][j]=1;
        while(!q.empty()){
          pii c = q.front();
          q.pop();
          t+=(int)(mat[c.ff][c.ss]-'0');
          l=min(l,c.ss);
          r=max(r,c.ss);
          vis[c.ff][c.ss]=1;
          rep(k,0,4){
            int L = c.ff + dx[k];
            int C = c.ss + dy[k];
            if(ok(L,C)){
              q.push(pii(L,C));
              vis[L][C]=1;
            }
          }
        }
        have[l][r]+=t;
    }
  }

  swap(n,m);
  for(int i=1;i<=n;i++){
    for(int j=i;j<=n;j++)if(have[i][j]){
      add[i].pb(pii(j,have[i][j]));
      rem[j+1].pb(have[i][j]);
    }
  }

  ll tot=0;
  for(int i=1;i<=n;i++){
    for(auto it : rem[i]){
      tot-=it;
      val[i]+=it;
    }
    for(auto it : add[i]){
      tot+=it.ss;
      val[it.ff+1]-=it.ss;
    }

    ll cur = tot;
    for(int j=i;j<=n;j++){
      cur+=val[j];
      cost[i][j] = cur;
    }

  }


  dp.solve(n);

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
