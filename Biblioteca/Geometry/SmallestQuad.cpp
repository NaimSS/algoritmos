// menor area de um quadrilatero usando os pontos

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
#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
//#define left sefude
//#define right sefudermano
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

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
  typedef Point P;
  T x, y;
  T id;
  explicit Point(T x=0, T y=0,T id=0) : x(x), y(y),id(id) {}

  bool operator<(const P &other) const {
        return make_pair(y, x) > make_pair(other.y, other.x);
    }
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

const ll inf = 9e18;


struct coisa{
  P v;
  int id1,id2;
  coisa(P v,int id1,int id2):id1(id1),id2(id2),v(v){}
  bool operator<(const coisa &other)const{
    return v.cross(other.v) > 0;
  }
};

const int N = 2020;
int pos[N];

void solve(){
  int n;
  cin>>n;
  vector<P> p(n);
  for(int i=0;i<n;i++){
    cin >> p[i].x >> p[i].y;
    p[i].id = i;
  }
  ll ans = inf;
  sort(all(p),[&](P a,P b){
    return tie(a.y,a.x) > tie(b.y,b.x);
  });
  vector<coisa> aux;

  for(int i=0;i<n;i++){
    p[i].id = i;
    pos[i] = i;
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<i;j++){
      aux.pb(coisa(p[j] - p[i],i,j));
    }
  }

  sort(all(aux));  
  
  for(auto c : aux){
    int id1 = c.id1,id2 = c.id2;
    int &a = pos[id1];
    int &b = pos[id2];
    assert(b == a-1);

    if(b-1>=0){
    P op1 = p[b-1];
    if(a+1<n){
      P op2 = p[a+1];
      ans = min(ans,abs(p[a].cross(p[b],op1)) + abs(p[a].cross(p[b],op2)));
    }
    }
    swap(p[a],p[b]);
    swap(a,b);
  }
  cout << ans << endl;
}

int32_t main(){
  fastio;
  int T;
  cin>>T;
  for(int cs = 1;cs<=T;cs++){
    cout<<"Case #"<<cs<<": ";
    solve();
  }
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
