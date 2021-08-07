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

const int N = 100100;

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

/**
 * Author: Tiago Domingos
 * Date: 14/02/2020
 * Description:
  Return points in CCW order, using graham scan, if you want collinears, change <= to < in the pop_back part and 
  remove (hull[back] == hull[0]) part
 * Status: tested with Kattis problems convexhull 
 * Time: O(n \log n)
*/
typedef Point<ll> P;

vector<P> convexHull(vector<P> pts) {
  if (sz(pts) <= 1) return pts;
  P pivot = pts[0];
  rep(i,0,sz(pts)) pivot = min(pivot , pts[i]);
  sort(all(pts) , [&](P a , P b){
    a = a - pivot , b = b - pivot;
    int hp1 = a < P(0,0) , hp2 = b < P(0,0);
    if(hp1 != hp2) return hp1 < hp2;
    if(a.cross(b) != 0){
      return a.cross(b)  > 0;
    }
    return a.dist2() < b.dist2();
  });
  vector<P> hull;
  rep(i,0,sz(pts)){
    while(hull.size() > 1 && ((hull.back() - hull[sz(hull) - 2]).cross(pts[i] - hull.back()) <= 0)) hull.pop_back();
    hull.push_back(pts[i]);
  }
  if(hull.back() == hull[0]) hull.pop_back();
  return hull; 
}

ll f[N];
int l[N],r[N];
const unsigned long long VAL = 100000;
int32_t main(){
  fastio;
  
  ifstream cin("balance.in");
  ofstream cout("balance.out");
  
  int n;
  cin >> n;
  vector<P> pts;
  f[0] = f[n + 1] = 0;
  for(int i=1;i<=n;i++)cin >> f[i];
  for(int i=0;i<=n+1;i++){
    pts.pb(P(i,f[i]));

  }
  vector<P> hull = convexHull(pts);

  sort(all(hull));

  for(int i=0;i<sz(hull) - 1;i++){
    
    l[hull[i].x]=r[hull[i].x] = hull[i].x;
    
    for(int j=hull[i].x+1;j<hull[i+1].x;j++){
      l[j] = hull[i].x;
      r[j] = hull[i+1].x; 
    }

  }

  for(int i=1;i<=n;i++){
    if(l[i] == r[i]){

      cout << VAL * f[i] << endl;

    }else{
      unsigned long long res = (VAL * (1ULL*(r[i] - i)*f[l[i]] + 1ULL*(i - l[i])*f[r[i]]))/(r[i] - l[i]);
      cout << res << endl;
    }
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
