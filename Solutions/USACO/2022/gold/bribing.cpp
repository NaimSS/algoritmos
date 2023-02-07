#include <bits/stdc++.h>
// #define int long long
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

struct naim_data{
	int p,c,x;
};
const int N = 2020;
map<int,int> dp[N];
int32_t main(){
    fastio;
	int n,a,b;
	cin >> n >> a >> b;
	vector<naim_data> v(n);
	rep(i,0,n)cin>>v[i].p>>v[i].c>>v[i].x;
	sort(all(v),[&](naim_data a,naim_data b){
		return a.x < b.x;
	});
	dp[a][b]=0;
	for(int i=0;i<n;i++){
		
		for(int j=0;j<=a;j++){
			for(map<int,int>::iterator it = dp[j].begin();it!=dp[j].end();){
				if(j!=a && it->ff!=0)it = dp[j].erase(it);
				else it++;
			}
			for(auto it : dp[j]){
				int b = it.ff;
				int p = it.ss;
				int use = min(b/v[i].x,v[i].c);
				int cost = v[i].c - use;
				if(j-cost<0)continue;
				int nb = b - use*v[i].x;
				if(use!=v[i].c){
					nb=0;
				}
				assert(nb>=0);
				dbg(i,j,b,p,j-cost);
				dp[j-cost][nb] = max(dp[j-cost][nb],p + v[i].p);
			}
		}
		
	}
	int res = 0;
	rep(j,0,a+1)for(auto it : dp[j])res=max(res,it.ss);
	cout<<res<<endl;
    // math -> gcd it all
    // Did u check N=1? Did you switch N,M?
}
