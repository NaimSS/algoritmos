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



const ll inf = 1e17;
int dist(int i,int j);
struct node{
  int L,R;
  int tam;
  ll tot1,tot2;
  node operator+(const node &o) const{  // exemplo de operador de merge
    node r;
    if(tam == 0)return o;
    if(o.tam == 0)return *this;
    r.L = L,r.R = o.R;
    r.tot1 = tot1 + o.tot1 + dist(R,o.L);
    r.tam = tam + o.tam;
    r.tot2 = min({r.tot1,tot2 + o.tot1 + dist(R,o.L),tot1 + o.tot2 + dist(R,o.L)});
    if(tam > 1 || o.tam > 1){
      if(tam > 1)r.tot2 = min(r.tot2,
        tot1 + o.tot1 + dist(R-1,o.L)
         - dist(R,R-1)
        );
       if(o.tam > 1){
        r.tot2 = min(r.tot2,
          tot1 + o.tot1 - dist(o.L,o.L+1)
          + dist(R,o.L+1)
          );
       }
    }
    assert(R + 1 == o.L);
    return r;
    printf("[%d,%d] [%d,%d]\n",L,R,o.L,o.R);
    cout << r.L<<" "<<r.R<<" "<<r.tot1<<" "<<r.tot2<<endl;
    cout.flush();
  }
};
const int N = 100100;
int x[N],y[N];
node tree[4*N];
void upd(int no,int i,int j,int p,node v){
  if(i == j){
    tree[no]=v;
    return;
  }
  int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
  if(p<=mid)upd(l,i,mid,p,v);
  else upd(r,mid+1,j,p,v);
  tree[no] = tree[l] + tree[r];
}

node query(int no,int i,int j,int a,int b){
  if(i > j || i > b || j < a)return {-1,-1,-1,-1,-1};
  if(a<=i and j<=b)return tree[no];
  int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
  node op1 = query(l,i,mid,a,b);
  node op2 = query(r,mid+1,j,a,b);
  if(op1.L == -1)return op2;
  if(op2.L == -1)return op1;
  return op1 + op2;
}
int dist(int i,int j){
  return abs(x[i] - x[j]) + abs(y[i] - y[j]);
}
node make(int id){
  node r;
  r.L = r.R = id;
  r.tam = 1;
  r.tot1 = r.tot2 = 0;
  return r;
}
int32_t main(){
  fastio;
  
  ifstream cin("marathon.in");
  ofstream cout("marathon.out");
  
  int n,q;
  cin >> n >> q;
  for(int i=1;i<=n;i++){
    cin >> x[i] >> y[i];
    upd(1,1,n,i,make(i));
  }
  node r = query(1,1,n,1,n);
  
  while(q--){
    char op;
    cin >> op;
    if(op == 'Q'){
      int a,b;
      cin >> a >> b;

      ll res=0;
      if(a+1>=b){
        res = dist(a,b);
      }else{
        node r = query(1,1,n,a,b);
        res = min(r.tot1,r.tot2);
      }
      cout << res << endl;
    }else{
      int i;
      cin >> i;
      cin >> x[i] >> y[i];
      upd(1,1,n,i,make(i));
    }
  }
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
