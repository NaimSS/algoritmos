//https://oj.uz/problem/view/JOI14_fortune_telling2

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
#define dbg(...) 42
#endif
//

const int N = 400100;
int A[N],B[N],T[N];
int mx[N],mn[N];
int n,k;

struct node1{
  int mx;
  node1(int id=N){
    mx = id;
  }
  node1 operator+(const node1& o) const{
    node1 r;
    r.mx = max(mx,o.mx);
    return r;
  }
};
struct node2{
  int cnt;
  node2(int v=0){
    cnt=v;
  }
  node2 operator+(const node2& o) const{
    node2 r;
    r.cnt = cnt + o.cnt;
    return r;
  }
};
template <class T>
struct ST{
	vector<T> st; int n; 
	ST(int n) : st(2*n) , n(n){}
	void upd(int pos, T val){ // pos 0index
		for(st[pos += n] = val ; pos /= 2;)
			st[pos] = st[2*pos] + st[2*pos + 1];
	}
	T query(int x , int y){ // [x,y] , x, y -0index
		T ra , rb = T();
		bool okl = false, okr = false;
		for(x += n, y += n+1 ; x < y ; x/=2 , y/=2){
			if(x&1) ra = (okl ? ra + st[x] : st[x]) , x++ , okl = true;
			if(y&1) --y , rb = (okr ? st[y] + rb : st[y]) , okr = true;
		}
		return (okl ? (okr ? ra + rb : ra): rb);
	}
};
int jmx[N];

struct query{
  int l,r,mx,id;
  query(int l,int r,int mx,int id):l(l),r(r),mx(mx),id(id){}
};



int32_t main(){
  fastio;
  cin >> n >> k;
  vi comp;
  rep(i,1,n+1){
    cin >> A[i]>>B[i];
    mn[i] = min(A[i],B[i]);
    mx[i] = A[i] + B[i] - mn[i];
  }
  rep(i,1,k+1){
    cin >> T[i];
    comp.pb(T[i]);
  }
  Unique(comp);
  int tam = sz(comp);
  ST<node1> tree(tam);
  rep(i,1,k+1){
    int p = lower_bound(all(comp),T[i]) - comp.begin();
    tree.upd(p,node1(i));
  }
  auto get = [&](int x) -> int{
    return int(lower_bound(all(comp),x) - comp.begin());
  };
  vector<query> Q;
  rep(i,1,n+1){
    int L = get(mn[i]);
    int R = get(mx[i])-1;
    int ok=0;
    if(L<=R){
      jmx[i] = tree.query(L,R).mx;
      if(jmx[i] <= k){
        Q.pb(query(jmx[i]+1,k,mx[i],i));
        ok=1;
      }
    }else jmx[i] = k+1;
    if(!ok){
      Q.pb(query(1,k,mx[i],i));
    }
  }
  sort(all(Q),[&](query a,query b){
    return a.mx > b.mx;
  });
  vi ids;
  rep(i,1,k+1)ids.pb(i);
  sort(all(ids),[&](int a,int b){
    return T[a] > T[b];
  });
  int pt=0;
  ST<node2> seg(k);
  ll res=0;
  for(auto it : Q){
    while(pt < sz(ids) && T[ids[pt]] >= it.mx){
      seg.upd(ids[pt]-1,node2(1));
      pt++;
    }
    int cnt = seg.query(it.l-1,it.r-1).cnt;
    cnt%=2;
    int i = it.id;
    if(jmx[i]<=k){
      res+=(cnt == 0 ? mx[i] : mn[i]);
    }else{
      res+=(cnt==1 ? B[i] : A[i]);
    }
  }
  cout << res << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
