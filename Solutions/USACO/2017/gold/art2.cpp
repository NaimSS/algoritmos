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
#define left sefude
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl; 
typedef long long ll;
typedef pair<ll,ll> pll;
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

const int N = 100100;
int a[N];
int L[N],R[N];
int cnt0[N];
int cnt[N];
vi pos[N];

struct node{
  int x;
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
    for(st[pos += n] = val ; pos /= 2;)
      st[pos] = st[2*pos] + st[2*pos + 1];
  }
  T query(int x , int y){ // [x,y] , x, y -0index
    T ra = ini , rb = ini;
    for(x += n, y += n+1 ; x < y ; x/=2 , y/=2){
      if(x&1) ra = ra + st[x] , x++;
      if(y&1) --y , rb = st[y] + rb;
    }
    return ra + rb;
  }
};


int32_t main(){
  fastio;
  
  ifstream cin("art2.in");
  ofstream cout("art2.out");
  
  int n;
  cin >> n;
  for(int i=1;i<=n;i++){
    cin >> a[i];
    pos[a[i]].pb(i);
    if(L[a[i]] == 0)L[a[i]] = i;
    R[a[i]] = i;

    cnt0[i] = cnt0[i-1];
    if(a[i] == 0)cnt0[i]++;
  }
  vector<pii> ev;
  for(int i=1;i<=n;i++){
    int sla = cnt0[R[i]] - cnt0[L[i]-1];
    if(sla > 0){
      cout << -1 << endl;
      return 0;
    }
  }

  ST<node> T(n+1,{0});
  for(int i=1;i<=n;i++){
    T.upd(i,{R[a[i]]});
  }
  for(int i=1;i<=n;i++){
    if(a[i] == 0)continue;
    if(T.query(i,R[a[i]]).x > R[a[i]]){
      cout << -1 << endl;
      return 0;
    }
  }

  int op = 0;
  int res=0;
  for(int i=1;i<=n;i++){
    if(a[i] == 0)continue;
    if(i == L[a[i]]){
      op ++ ;
      cnt[a[i]] ++ ;
    }
    res = max(res,op);
    if(i == R[a[i]])op--;
  }

  cout << res << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
