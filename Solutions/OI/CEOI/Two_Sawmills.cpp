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

const int N = 20100;
int d[N],w[N];
int L,R;
ll sum;
ll tot;
ll dist;
void redo(){
  L = 1;
  R = 0;
  sum = tot=0;
  dist=0;
}




ll cost(int l,int r){
  if(l>r)return 0;
  while(L<l){
    tot-=d[L]*sum;
    dist-=d[L];
    sum-=w[L];
    L++;
  }
  while(L>l){
    L--;
    sum+=w[L];
    tot+=sum * d[L];
    dist+=d[L];
  }
  while(R<r){
    R++;
    dist+=d[R];
    tot+=dist*w[R];
    sum+=w[R];
  }
  while(R>r){
    tot-=dist*w[R];
    sum-=w[R];
    dist-=d[R];
    R--;
  }
  
  return tot;
}


struct DP{
  int n , inf; 
  vi dp[2];
  DP(int n , int inf) : n(n) , inf(inf) {dp[0] = vi(n+1) , dp[1] = vi(n+1);}
  // compute dp_cur[l], ... dp_cur[r] (inclusive) 
  void compute(int l, int r, int optl, int optr){
      if (l > r) return;
      int mid = l + (r-l)/2;
      pair<int, int> best = {inf, -1}; // se for maximizar muda pra -inf
      rep(k,optl,min(mid,optr)+1){
          best = min(best, { dp[0][k-1] + cost(k,mid-1), k});
      }
      dp[1][mid] = best.first; int opt = best.second;
      compute(l, mid - 1, optl, opt);
      compute(mid + 1, r, opt, optr);
  }
  void solve(int k){
    redo();
    dp[0][0]=0;
    rep(i,1,n+1){
      dp[0][i] = cost(1,i-1);
    }
    rep(i,2,k+1){
      rep(j,0,i)dp[1][j] = dp[0][j];
      rep(j,i,n+1) dp[1][j] = inf;
      redo();
      compute(i,n,i,n) ;
      swap(dp[0] , dp[1]);
    }
  }
};

const int inf = 2e9 + 1000;

int32_t main(){
  fastio;
  int n;
  cin >> n;
  for(int i=n;i>=1;i--){
    cin >> w[i] >> d[i];
  }

  DP dp(n,inf);
  dp.solve(2);

  redo();
  ll res = 1e18;
  for(int i=1;i<=n;i++){
    res=min(res,dp.dp[0][i] + cost(i+1,n));
  }
  cout << res << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
