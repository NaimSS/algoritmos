// https://www.hackerrank.com/contests/101hack43/challenges/k-inversion-permutations/problem
// O(Nsqrt)
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
//#define M   1000000007 // 1e9 + 7
//#define int long long
using namespace std;
typedef vector<int> vi;
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
ll fat[N],inv[N];
const int M = 1e9 + 7;
ll C(int n,int k){
  if(k>n)return 0;
  return (fat[n]*((inv[k]*inv[n-k])%M))%M;
}
void init(){
  fat[0] = 1;
  for(int i=1;i<N;i++){
    fat[i] = (fat[i-1]*i)%M;
  }
  inv[N-1] = exp(fat[N-1],M-2,M);
  for(int i=N-2;i>=0;i--){
    inv[i] = (inv[i+1]*(i+1))%M;
  }
}
const int sq = 450;
const int NN = 100100;
ll dp[NN][sq + 10];
int n;
ll g(int i,int j){
  if(j==0){
    if(i==0)return 1;
    return 0;
  }
  if(i<=0)return 0;
  ll &x = dp[i][j];
  if(x!=-1)return x;
  x = 0;
  x = g(i-j,j-1) + g(i-j,j) - g(i - (n +1),j-1);
  x%=M;
  if(x<0)x+=M;
  
  return x;
}

ll f(int s){
  ll tot=0;
  for(int i=0;i<sq;i++){
    ll x = g(s,i);
    if(i%2)x = -x;
    tot = (tot + x)%M;
    if(i>s)break;
  }
  return tot;
}

int32_t main(){
  memset(dp,-1,sizeof(dp));
 fastio;
 init();
 int k;
 cin>>n>>k;
 ll res = 0;
 for(int s=0;s<=k;s++){
    ll cur = C(n -1 + (k-s),n-1);
    
    cur = (cur*f(s))%M;
    res = (res + cur)%M;
 }  
 if(res<0)res+=M;
 cout << res << endl;
  // Math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
