// upsolving

#include <bits/stdc++.h>
//#define int long long
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
std::mt19937_64 rng64((int) std::chrono::steady_clock::now().time_since_epoch().count());

ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down
//inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
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
vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
	vector<C> in(n), out(n);
	copy(all(a), begin(in));
	rep(i,0,sz(b)) in[i].imag(b[i]);
	fft(in);
	trav(x, in) x *= x;
	rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}

vector<ll> conv(vi a,vi b){
  vd A(sz(a)),B(sz(b));
  rep(i,0,sz(a))A[i]=a[i];
  rep(i,0,sz(b))B[i]=b[i];
  vd res = conv(A,B);
  vl Res(sz(res));
  rep(i,0,sz(res))Res[i] = round(res[i]);
  return Res;
}

int32_t main(){
  fastio;
  int n1,m1;
  cin >> n1 >> m1;
  vector<vi> a(n1,vi(m1));
  rep(i,0,n1)rep(j,0,m1)cin >> a[i][j];



  // ai * (ai - bj)^2
  // ai * (ai^2 - 2aibj + bj^2)
  // ai^3 - 2 (ai^2)bj + ai (bj^2)

  ll sumA3 = 0;
  rep(i,0,n1)rep(j,0,m1)sumA3 += (ll)a[i][j] *a[i][j] *a[i][j]; 

  int n2,m2;
  cin >> n2 >> m2;
  vector<vi> b(n2,vi(m2));
  rep(i,0,n2)rep(j,0,m2)cin >> b[i][j];
  const int MAX = max(m1,m2) * 2 + 1;
  const int MX = n1*MAX - 1;
  vi polyA1(n1*MAX);
  vi polyA2 = polyA1;
  rep(i,0,n1)rep(j,0,m1){
    polyA1[MX - (i*MAX + j)] = a[i][j] * a[i][j];
    polyA2[MX - (i*MAX + j)] = a[i][j];
  }
  vi polyB1(MAX*n2),polyB2(MAX*n2);
  rep(i,0,n2)rep(j,0,m2){
    polyB1[i*MAX + j] = b[i][j];
    polyB2[i*MAX + j] = b[i][j] * b[i][j];
  }

  vl v1 = conv(polyA1,polyB1);
  vl v2 = conv(polyA2,polyB2);

  vector<pii> res;

  for(int i=0;i + n1-1 < n2;i++){
    for(int j=0;j + m1 -1 < m2;j++){
      ll val = sumA3 - 2*v1[i*MAX + j + MX] + v2[i*MAX + j + MX];
      if(!val)
        res.pb(pii(i,j));
    }
  }
  cout << sz(res) << endl;
  for(auto it : res)cout << it.ff + 1 <<" "<< it.ss + 1<<endl;


  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
