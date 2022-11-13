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
//std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

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


const int N = 100;

template<class T>
struct Point{
	typedef Point P;
	T x,y;
	Point(T x = 0,T y = 0):x(x),y(y){}
	P operator-(P o)const {return P(x-o.x,y-o.y);}
	P operator+(P o)const {return P(x+o.x,y+o.y);}
	P operator/(double d)const{return P(x/d,y/d);}
	P operator*(double d)const{return P(x*d,y*d);}
	double dist(){
		return sqrt(x*x + y*y);
	}
	P unit(){
		return *this/dist();
	}
	P perp(){
		return P(-y,x);
	}
	T cross(P p)const {return x*p.y - y*p.x;}
	T cross(P a,P b)const{return (a-*this).cross(b - *this);}
	friend ostream& operator <<(ostream& os,P p){
		return os <<"("<<p.x<<","<<p.y<<")";
	} 
};

typedef Point<double> P;

struct ilha{
	vector<P> v;
	void read(){
		int n;
		cin >> n;
		rep(i,0,n){
			int x,y;
			cin >> x >> y;
			v.pb(P(x,y));
		}
	}
};

struct aviao{
	int x[2],y[2],z[2];
	void read(){
		rep(i,0,2)cin >> x[i] >> y[i] >> z[i];
	}


	P vetor(){
		return P(x[1],y[1]) - P(x[0],y[0]);
	}
	P perp1(){
		return vetor().perp();
	}
	P perp2(){
		return vetor().perp().perp().perp();
	}
	P p0(){
		return P(x[0],y[0]);
	}
	P p1(){
		return P(x[1],y[1]);
	}
	
	vector<P> quadri(double theta){
		vector<P> vec;
		// tg(theta) = tam/z -> tam = z * tg
		double tam1 = z[0] * tan(theta);
		vec.pb(p0() + perp1().unit() * tam1);
		vec.pb(p0() + perp2().unit() * tam1);

		double tam2 = z[1] * tan(theta);

		vec.pb(p1() + perp2().unit() * tam2);
		vec.pb(p1() + perp1().unit() * tam2);
		return vec;
	}

	bool inside(const P& qry,double theta){
		vector<P> vec = quadri(theta);
		rep(i,0,4){
			P p = vec[i];
			P q = vec[(i+1)%4];
			if(p.cross(q,qry) < 0)return 0;
		}
		return 1;
	}

}av[N];

const double PI = acos(-1);

bool not_inside(aviao av,P p){
	P v = av.vetor();
	P p1 = av.perp1(),p2 = av.perp2();
	if(av.p0().cross(av.p0() + p1,p) > 0)return 1;
	if(av.p0().cross(av.p0() + p2,p) < 0)return 1;
	if(av.p1().cross(av.p1() + p1,p) < 0)return 1;
	if(av.p1().cross(av.p1() + p2,p) > 0)return 1;
	return 0;
}

int check(const ilha& il,double theta,const vector<aviao> &useful){
	for(auto av : useful){
		int ok = 1;
		for(auto p : il.v){
			if(!av.inside(p,theta)){
				ok = 0;break;
			}
		}
		if(ok)return 1;
	}
	return 0;
}

int32_t main(){
    fastio;
	mt19937 rng(712872);
	int n,m;
	cin >> n >> m;
	vector<ilha> vec;
	rep(i,0,n){
		ilha il;
		il.read();
		vec.pb(il);
	}
//	shuffle(all(vec),rng);
	rep(i,0,m){
		av[i].read();
	}
	double res = 0;
	
	for(auto &it : vec){

		vector<aviao> useful;

		rep(i,0,m){
			int ok = 1;
			for(auto p : it.v){
				if(not_inside(av[i],p)){
					ok = 0;
					break;
				}
			}
			if(ok)useful.pb(av[i]);
		}
		if(sz(useful) == 0){
			cout << "impossible\n";
			return 0;
		}
		if(check(it,res,useful))continue;
		double L = res,R = PI/2;
		rep(iter,0,45){
			double m = (L+R)/2.0;
			if(check(it,m,useful)){
				R = m;
				res = m;
			}else L = m;
		}

	}	
	cout << setprecision(10) << fixed;
	res = res * 180/PI;
	cout << res << endl;


    // math -> gcd it all
    // Did u check N=1? Did you switch N,M?
}
