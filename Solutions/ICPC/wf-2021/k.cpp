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

vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

void reorder_polygon(vector<P> & pts){
    size_t pos = 0;
    for(size_t i = 1; i < pts.size(); i++){
        if(pts[i].y < pts[pos].y || (pts[i].y == pts[pos].y && pts[i].x < pts[pos].x))
            pos = i;
    }
    rotate(pts.begin(), pts.begin() + pos, pts.end());
}

vector<P> minkowski(vector<P> p, vector<P> q){
    if(sz(p)==0)return q;
    if(sz(q)==0)return p;
    // the first vertex must be the lowest
    reorder_polygon(p);
    reorder_polygon(q);
    if(sz(p) < 3 || sz(q) < 3){
      // brute:
      vector<P> v;
      for(auto pp : p)for(auto qq : q){
        v.pb(pp + qq);
      }
      return convexHull(v);
    }

    // we must ensure cyclic indexing
    p.push_back(p[0]);
    p.push_back(p[1]);
    q.push_back(q[0]);
    q.push_back(q[1]);
    // main part
    vector<P> result;
    int i = 0, j = 0;
    while(i < sz(p) - 2 || j < sz(q) - 2){
        result.push_back(p[i] + q[j]);
        assert(i+1 < sz(p) && j+1<sz(q));
        auto cross = (p[i + 1] - p[i]).cross(q[j + 1] - q[j]);
        if(cross >= 0)
            ++i;
        if(cross <= 0)
            ++j;
    }
    return result;
}


const int N = 1e4 + 10;
vector<P> pts[N];
vi g[N];
bool folha[N];
vector<P> neg(vector<P> pts){
  for(auto &it : pts)it = it*-1;
  return convexHull(pts);
}

vector<P> pre[N],suf[N];
void dfs(int v){
  if(folha[v])return;

  for(auto to : g[v]){
    dfs(to);
  }
  rep(i,0,sz(g[v])){  
    int to = g[v][i];
    if(!i)pre[i] = neg(pts[to]);
    else pre[i] = minkowski(pre[i-1],neg(pts[to]));
  }
  for(int i=sz(g[v])-1;i>=0;i--){  
    int to = g[v][i];
    if(i+1 == sz(g[v]))suf[i] = neg(pts[to]);
    else suf[i] = minkowski(suf[i+1],neg(pts[to]));
  }
  
  rep(i,0,sz(g[v])){
    int to = g[v][i];
    vector<P> v1 = pts[to];
    if(i)v1 = minkowski(v1,pre[i-1]);
    if(i+1<sz(g[v]))v1 = minkowski(v1,suf[i+1]);
    for(auto it : v1)pts[v].pb(it);
  }
  pts[v] = convexHull(pts[v]);
}

int32_t main(){
  fastio;
  int n;
  cin >> n;
  for(int i=1;i<=n;i++){
    int k;
    cin >> k;
    if(k==0){
      folha[i] = 1;
      int x,y;
      cin >> x >> y;
      pts[i].pb(P(x,y));
    }else{
      rep(j,0,k){
        int to;
        cin >> to;
        g[i].pb(to);
      }
    }
  }
  dfs(1);
  ll res=0;
  for(auto it : pts[1])res=max(res,it.dist2());
  cout << res << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
