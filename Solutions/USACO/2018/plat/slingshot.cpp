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


struct node{
  ll mn[2];
  node operator+(const node &o) const{ 
    node r;
    rep(i,0,2){
      r.mn[i]=min(mn[i],o.mn[i]);
    }
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
    st[pos] = (st[pos] + val); 
    for( ; pos /= 2;)
      st[pos] = st[2*pos] + st[2*pos + 1];
  }
  T query(int x , int y){ // [x,y] , x, y -0index
    T ra = ini , rb = ini;
    if(x > y || y<0)return ini;
    for(x += n, y += n+1 ; x < y ; x/=2 , y/=2){
      if(x&1) ra = ra + st[x] , x++;
      if(y&1) --y , rb = st[y] + rb;
    }
    return ra + rb;
  }
};

const int N = 100100;
int x[N],y[N],t[N],a[N],b[N];
ll res[N];
int32_t main(){
  fastio;
  ifstream cin("slingshot.in");
  ofstream cout("slingshot.out");
  int n,q;
  cin >> n >> q;
  
  vi comp;
  vi ids;
  for(int i=1;i<=n;i++){
    cin >> x[i] >> y[i] >> t[i];
    comp.pb(y[i]);
     ids.pb(i);
  }
  Unique(comp);
  sort(all(ids),[&](int a,int b){
    return x[a] < x[b];
  });
  vi qry;
  rep(i,0,q){
    cin >> a[i] >> b[i];
    qry.pb(i);
    res[i] = 2e9;
  }
  sort(all(qry),[&](int i,int j){
    return a[i] < a[j];
  });
  node ini;
  ini.mn[0] = ini.mn[1] = 1e18;
  ST<node> pre(n,ini);

  int id=0;
  for(int i : qry){
    while(id <n and a[i] >= x[ids[id]]){
      int Id = ids[id];
      int pos = lower_bound(all(comp),y[Id]) - comp.begin();
      node no;
      no.mn[0] = t[Id] - x[Id] - y[Id];
      no.mn[1] = t[Id] - x[Id] + y[Id];
      pre.upd(pos,no);
      id++;
    }
    int pos = lower_bound(all(comp),b[i]) - comp.begin();
    node no1 = pre.query(0,pos-1),no2 = pre.query(pos,n-1);
    ll op1 = no1.mn[0] + a[i] + b[i];
    ll op2 = no2.mn[1] + a[i] - b[i];
    res[i] = min({res[i],op1,op2});
  }

  reverse(all(qry));
  reverse(all(ids));
  id = 0;
  pre = ST<node>(n,ini);
  for(int i : qry){
    while(id < n and x[ids[id]]>=a[i]){
      int Id = ids[id];
      int pos = lower_bound(all(comp),y[Id]) - comp.begin();
      node no;
      no.mn[0] = t[Id] + x[Id] - y[Id];
      no.mn[1] = t[Id] + x[Id] + y[Id];
      pre.upd(pos,no);
      id++;
    }
    int pos = lower_bound(all(comp),b[i]) - comp.begin();
    node no1 = pre.query(0,pos-1),no2 = pre.query(pos,n-1);
    ll op1 = no1.mn[0] - a[i] + b[i];
    ll op2 = no2.mn[1] - a[i] - b[i];
    res[i] = min({res[i],op1,op2}); 
  }
  rep(i,0,q){
    res[i] = min(res[i],1ll*abs(a[i] - b[i]));
    cout << res[i] << endl;
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
