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
#define dbg(...) 
#endif
//
 
const int N = 100100;
int A[N],B[N],C[N];
int pai[N];
int H[N];
ll bit[N];
stack<pii> st[N];
 
 
 
class HLD{
public:
	HLD(int n): Sz(n+1) , Hd(n+1) , p(n+1, -1) , g(n+1) , out(n+1) , in(n+1) , n(n){}
	void add_edge(int x , int y){
		g[x].push_back(y);
		g[y].push_back(x);
		edges ++ ;
		assert(edges < n);
	}
	void dfs_sz(int x , int par = -1){
		Sz[x] = 1;
		trav(w, g[x]){
			if(w == par) continue;
			H[w] = H[x] + 1;
      dfs_sz(w,x);
 
			Sz[x] += Sz[w];
			if(Sz[w] > Sz[g[x][0]] || g[x][0] == par) swap(w, g[x][0]);
		}
	}
	void dfs_dec(int x , int par = -1){ 
		in[x] = tin++;
    p[x] = par;
		allin(w, g[x]){
			if(w == par) continue;
			Hd[w] = ((w == g[x][0]) ? Hd[x] : w);
			dfs_dec(w,x); 
		}
		out[x] = tin;
	}
	void decompose(int root){
    H[root] = 1;
		Hd[root] = root;
		dfs_sz(root);
		dfs_dec(root);
	}
 
 
  ll sum(ll x){
    ll res=0;
    while(x>0){
      res+=bit[x];
      x-=(x&-x);
    }
    return res;
  }
void upd(int x,int v){
  while(x<N){
    bit[x]+=v;
    x+=(x&-x);
  }
}
 
ll cnt(vector<pii> v){
  ll res=0;
  for(auto it : v){
    res+=it.ss * (sum(N-1) - sum(it.ff));
    upd(it.ff,+it.ss);
  }
  for(auto it : v){
    upd(it.ff,-it.ss);
  }
  return res;
}
 
  ll query(int v,int c){
    ll res=0;
    vector<pii> vec;
 
    while(v!=-1){
      int d = H[v];
      v = Hd[v];
      int t = H[v]-1;
 
      stack<pii>&s = st[v];
      vector<pii> cur;
      while(!s.empty() && s.top().ss <= d){
        auto tp = s.top();s.pop();
        cur.pb(pii(tp.ff,tp.ss-t));
        t=tp.ss;
      }
      if(!s.empty() && s.top().ss > d){
        cur.pb(pii(s.top().ff,d-t));
      }
      s.push(pii(c,d));
      v = p[v];
      reverse(all(cur));
      for(auto it : cur)vec.pb(it);
    }
    reverse(all(vec));
    res += cnt(vec);
    return res;
  }
 
private:
	vector < vi > g; 
	vi Sz , Hd , in , out ,p ; 
	int n , edges =0  , tin = 0;
};
 
 
 
 
int32_t main(){
  fastio;
  int n;
  cin >> n;
  vi vec;
  rep(i,1,n+1){
 
    cin >> C[i];
    vec.pb(C[i]);
    pai[i] = i;
  }
  Unique(vec);
  rep(i,1,n+1){
    C[i] = (lower_bound(all(vec),C[i]) - vec.begin()) + 1;
  }
  HLD H(n);
  rep(j,1,n){
    cin >> A[j] >> B[j];
    H.add_edge(A[j],B[j]);
  }
  H.decompose(1);
  rep(j,1,n){
    cout << H.query(B[j],C[B[j]]) << endl;
  }
 
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
