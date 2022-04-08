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

int n;

const double PI = acos(-1);
 
typedef complex<double> C;
typedef vector<double> vd;
 
void fft(vector<C>& a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  static vector<complex<long double>> R(2, 1);
  static vector<C> rt(2, 1);  // (^ 10% faster if double)
  for (static int k = 2; k < n; k *= 2) {
    R.resize(n); rt.resize(n);
    auto x = polar(1.0L, acos(-1.0L) / k);
    rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
  }
  vi rev(n);
  rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
      // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
      auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
      C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
      a[i + j + k] = a[i + j] - z;
      a[i + j] += z;
    }
}
const double EPS = 1e-9;
vl conv(const vl& a, const vl& b) {
  if (a.empty() || b.empty()) return {};
  vl res(sz(a) + sz(b) - 1);
  int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
  vector<C> in(n), out(n);
  copy(all(a), begin(in));
  rep(i,0,sz(b)) in[i].imag(b[i]);
  fft(in);
  for (C& x : in) x *= x;
  rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
  fft(out);
  rep(i,0,sz(res)) res[i] = (ll)round(imag(out[i]) / (4 * n));
  
  while(res.back()<EPS and sz(res)>1)res.pop_back();
  return res;
}

vl solve(vl F,vl C){
  sort(all(F));
  sort(all(C));

  ll cur=0;
  int i=0,j=sz(F)-1;
  vl res(sz(F));
  int k=0;
  while(i<=j){
    ll op1 = C[i] * F[i],op2 = C[j] * F[j];
    if(op1 <=0 && op2 <=0)break;
    if(op1 > op2){
      cur+=op1;
      i++;
    }else cur+=op2,j--;
    res[k++] = cur;
  }
  vl F2,C2;
  while(i<=j){
    F2.pb(F[i]);C2.pb(C[i]);
    i++;
  }
  if(sz(F2)==0)
    return res;

  sort(all(F2),[&](ll a,ll b){
    return abs(a) < abs(b);
  });
  sort(all(C2),[&](ll a,ll b){
    return abs(a) < abs(b);
  });

  auto p = conv(F2,C2);
  rep(i,k,sz(F)){
    res[i] = cur + p[i-k];
  }
  return res;
}

int32_t main(){
    fastio;
    cin >> n;
    vector<ll> F(n),C(n),F2(n);
    rep(i,0,n)cin>>F[i],F2[i] = - F[i];
    rep(i,0,n)cin>>C[i];

    auto r1 = solve(F,C);
    auto r2 = solve(F2,C);
    rep(i,0,n){
      cout << -r2[i]<<" "<<r1[i] << endl;
    }   

    // math -> gcd it all
    // Did u check N=1? Did you switch N,M?
}
