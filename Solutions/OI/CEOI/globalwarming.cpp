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
#define int long long
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


const int N = 400100;

int t[N];

struct node{
  ll x;
  
  node operator+(const node &rhs) const{  // exemplo de operador de merge
    node r;
    r.x = max(x,rhs.x);
    return r;
  }
};
template <class T>
struct ST{
  vector<T> st; int n; 
  T ini; 
  ST(int n , T ini) : st(2*n , ini) , n(n) , ini(ini) {}
  void upd(int pos, T val){ // pos 0index
    pos+=n;
    st[pos] = st[pos] + val;
    for(; pos /= 2;)
      st[pos] = st[2*pos] + st[2*pos + 1];
  }
  T query(int x , int y){ // [x,y] , x, y -0index
    if(x>y)return ini;
    T ra = ini , rb = ini;
    for(x += n, y += n+1 ; x < y ; x/=2 , y/=2){
      if(x&1) ra = ra + st[x] , x++;
      if(y&1) --y , rb = st[y] + rb;
    }
    return ra + rb;
  }
};


int suf[N];
int pre[N];
int n,x;

int32_t main(){
  fastio;
  cin >> n >> x;
  vi cmp;
  for(int i=1;i<=n;i++){
    cin >> t[i];
    cmp.pb(t[i]);
    cmp.pb(t[i] + x);
  }  

  Unique(cmp);

  ST<node> T(sz(cmp),{0});
  int res=0;
  for(int i=n;i>=1;i--){
    // find for the Suffix
    int pos = lower_bound(all(cmp),t[i]) - cmp.begin();
    suf[i] = 1 + T.query(pos+1,sz(cmp) - 1).x;
    T.upd(pos,{suf[i]});
    res = max(res,suf[i]);
 //   cout << suf[i]<<" ";
  }
 // cout << endl;
  
  T = ST<node>(sz(cmp),{0});
  for(int i=1;i<=n;i++){
    int pos = lower_bound(all(cmp),t[i]) - cmp.begin();
    pre[i] = 1 + T.query(0,pos-1).x;
    T.upd(pos,{pre[i]});
  //  cout << pre[i]<<" ";
  }
  //cout << endl;
  T = ST<node>(sz(cmp),{0});
  for(int i=1;i<=n;i++){
    int pos2 = lower_bound(all(cmp),t[i] + x) - cmp.begin();
    int val = suf[i] + T.query(0,pos2-1).x;
    res = max(res,val);
    int pos = lower_bound(all(cmp),t[i]) - cmp.begin();
    T.upd(pos,{pre[i]});
  }
  
  cout << res << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
