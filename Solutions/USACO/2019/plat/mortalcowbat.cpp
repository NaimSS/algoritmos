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
//#define int long long
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

const int N = 1e5 + 10;
int pre[N][30];
int a[30][30];

struct node{
  ll x;
  node operator+(const node &rhs) const{  // exemplo de operador de merge
    node r;
    r.x = min(x,rhs.x);
    return r;
  }
};
template <class T>
struct ST{
  vector<T> st; int n; 
  T ini; 
  ST(){}
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
const ll inf = 1e9;

ST<node> T[30];
int32_t main(){
  fastio;
  
  ifstream cin("cowmbat.in");
  ofstream cout("cowmbat.out");

  int n,m,k;
  cin >> n >> m >> k;
  string s;
  cin >> s;

  rep(i,0,m){
    rep(j,0,m){
      cin >> a[i][j];
    }
  }

  rep(k,0,m){
    rep(i,0,m){
      rep(j,0,m){
        a[i][j] = min(a[i][j],a[i][k] + a[k][j]);
      }
    }

    T[k] = ST<node>(n+1,{inf});
  }
  rep(i,0,n){
    if(i)rep(j,0,m)pre[i][j]=pre[i-1][j];

   
    rep(j,0,m)pre[i][j]+=a[s[i]-'a'][j];


  }


  rep(j,0,m)T[j].upd(n,{0 + pre[n-1][j]});

  for(int i=n-1;i>=0;i--){
    // dp[i] -> menor custo de comeca aqui
    if(i + k > n)continue;
    ll cur = inf;
    int id = 0;
    rep(j,0,m){
      if(cur > T[j].query(i+k,n).x - (i?pre[i-1][j]:0))
        cur = T[j].query(i+k,n).x - (i?pre[i-1][j]:0),id=j;

    }
    if(i == 0){
      cout << cur << endl;
      break;
    }
  
    rep(j,0,m){
      T[j].upd(i,{cur + pre[i-1][j]});
    }

  }


  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
