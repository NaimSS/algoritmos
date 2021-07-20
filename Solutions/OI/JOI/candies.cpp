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
#define int long long  
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
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b,ll e,ll m){
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
      if (e & 1) ans = ans * b % m;
  return ans;
}

const int N = 200100;
ll A[N];
int pai[N];
int L[N],R[N];
int f(int x){
  return pai[x]=(pai[x]==x?x:f(pai[x]));
}
void join(int a,int b){
  a=f(a),b=f(b);
  L[b]=min(L[b],L[a]);
  R[b]=max(R[b],R[a]);
  pai[a]=b;
}
int32_t main(){
  fastio;
  set<pll> pq;
  int n;
  cin >> n;
  rep(i,1,n+1){
    cin >> A[i];
    A[i]=-A[i];
    pq.insert(pll(A[i],i));
    pai[i]= i;
    L[i] = R[i] = i;
  }
  const ll inf = 1e18;
  A[0] = A[n+1] = inf;
  pq.insert(pll(inf,0));
  pq.insert(pll(inf,n+1));
  pai[0] = 0;
  pai[n+1] = n+1;
  
  ll res=0;
  rep(iter,0,(n+1)/2){
    pll x = *pq.begin();
    pq.erase(x);
    assert(x.ff == A[x.ss]);
    res+=x.ff;
    x.ff = -x.ff;
    int l = f(L[x.ss]-1);
    int r = f(R[x.ss]+1);
    
      pq.erase(pll(A[l],l)),x.ff+=A[l],join(l,x.ss);
      pq.erase(pll(A[r],r)),x.ff+=A[r],join(r,x.ss);
    
    x.ss = f(x.ss);
    A[x.ss] = x.ff;
    pq.insert(pll(A[x.ss],x.ss));
    cout << -res << endl;
  }
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
