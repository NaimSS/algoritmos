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
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x=0, T y=0) : x(x), y(y) {}
  bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
  bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
  P operator+(P p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  P operator*(T d) const { return P(x*d, y*d); }
  P operator/(T d) const { return P(x/d, y/d); }
  T dot(P p) const { return x*p.x + y*p.y; }
  T cross(P p) const { return x*p.y - y*p.x; }
  T cross(P a, P b) const { return (a-*this).cross(b-*this); }
  T dist2() const { return x*x + y*y; }
  double dist() const { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this/dist(); } // makes dist()=1
  P perp() const { return P(-y, x); } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")"; }
};
typedef Point<ll> P;


void reorder_polygon(vector<P> & p){
    size_t pos = 0;
    for(size_t i = 1; i < p.size(); i++){
        if(p[i].y < p[pos].y || (p[i].y == p[pos].y && p[i].x < p[pos].x))
            pos = i;
    }
    rotate(p.begin(), p.begin() + pos, p.end());
}

vector<P> minkowski( vector<P> &A , vector<P> &B){
  reorder_polygon(A);
  reorder_polygon(B);
    A.push_back(A[0]);
    A.push_back(A[1]);
    B.push_back(B[0]);
    B.push_back(B[1]);
    // main part
    vector<P> result;
    size_t i = 0, j = 0;
    while(i < A.size() - 2 || j < B.size() - 2){
        result.push_back(A[i] + B[j]);
        auto cross = (A[i + 1] - A[i]).cross(B[j + 1] - B[j]);
        if(cross >= 0)
            ++i;
        if(cross <= 0)
            ++j;
    }
    return result;
}

vector<P> solve(int l,int r,vector<P>& p){
  if(l==r){
    return {P(0,0),p[l]};
  }
  int m=(l+r)>>1;
  auto a = solve(l,m,p);
  auto b = solve(m+1,r,p);
  auto c = minkowski(a,b);
  //db2(l,r);
  //for(auto it : c)cout<<it<<endl;
  return c;
}

int32_t main(){
  fastio;
  int n;
  cin >> n;
  vector<P> p;
  rep(i,0,n){
    int x,y;
    cin >> x >> y;
    if(x!=0 || y!=0)p.pb(P(x,y));
    else i--,n--;
  }
  if(n==0){
    cout<<0<<endl;
    return 0;
  }
  auto h = solve(0,n-1,p);
  ll res=0;
  for(auto it : h)res=max(res,it.dist2());
  cout << res << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
