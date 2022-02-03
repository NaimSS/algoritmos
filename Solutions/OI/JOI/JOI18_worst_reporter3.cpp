/// https://oj.uz/problem/view/JOI18_worst_reporter3

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
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
//#define left oooooopss
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<ll> vl;
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b,ll e,ll m){
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
      if (e & 1) ans = ans * b % m;
  return ans;
}

// debug:
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T){ 
  cerr << ' ' << H; 
  dbg_out(T...); 
}
#ifdef LOCAL
#define dbg(...) cerr<<"(" << #__VA_ARGS__<<"):" , dbg_out(__VA_ARGS__) , cerr << endl
#else
#define dbg(...) 42
#endif
//



int32_t main(){
  fastio;
  int n,q;
  cin >> n >> q;
  vector<ll> d(n+1);
  d[0] = 0;
  rep(i,1,n+1){
    cin >> d[i];
    if(i>1){
      ll k =(d[i] + d[i-1] - 1)/(d[i-1]);
      d[i] = d[i-1] * k;
    }
  }
  sort(all(d));
  auto f = [&](ll t,ll x){
    ll l = 1,r=n;
    for(int i=1;i<=n;i++){
      int m = i;
      ll D = d[m];
      ll pos = (t/D) * D - m;
    }
    ll ans = n+1;
    while(l<=r){
      ll m=(l+r)/2;
      ll D = d[m];
      ll pos = (t/D) * D - m;
      if(pos <= x){
        ans = m;
        r=m-1;
      }else l=m+1;
    }
    return n-ans+1;
  };
  while(q--){
    ll t,l,r;
    cin >> t >> l >> r;
    cout << f(t,r) - f(t,l-1) + (t<=r && t>=l) << endl;
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
