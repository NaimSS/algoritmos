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
struct node{
  ll best[2][2];
  node operator+(const node &o) const{  // exemplo de operador de merge
    node r;
    for(int i=0;i<2;i++){
      for(int j=0;j<2;j++){
        r.best[i][j] = -inf;
      }
    }
    rep(i,0,2){
      rep(j,0,2){
        int l1 = i,c2 = j;
        rep(l2,0,2){
          r.best[i][j] = max(r.best[i][j],best[i][l2] + o.best[l2^1][j]);
          
        }
        r.best[i][j] = max(r.best[i][j],best[i][0] + o.best[0][j]);
        
      }
    }
    return r;
  }
};

node make(ll v){
  node r;
  r.best[0][0]=0;
  r.best[1][1]=v;
  r.best[0][1] = r.best[1][0] = -inf;
  return r;
}

const int N = 40100;
int v[N];
void print(node r);
node tree[4*N];
void build(int no,int i,int j){
  if(i==j){
    tree[no] = make(v[i]);
    return;}
  int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
  build(l,i,mid);build(r,mid+1,j);
  
  tree[no] = tree[l] + tree[r];
  return;
}
void upd(int no,int i,int j,int p,int v){
  if(i==j){
    tree[no] = make(v);
    return ;
  }
  int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
  if(p<=mid)upd(l,i,mid,p,v);
  else upd(r,mid+1,j,p,v);
  tree[no] = tree[l] + tree[r];
}


void print(node r){
  rep(i,0,2){
    rep(j,0,2)cout << r.best[i][j]<<" ";
    cout << endl;
  }
  cout <<endl;
}

int32_t main(){
  fastio;
    ifstream cin("optmilk.in");
  ofstream cout("optmilk.out");
  int n,q;
  cin >> n >> q;

  for(int i=1;i<=n;i++){
    cin >> v[i];
  }
  build(1,1,n);

  //print(make(1) + make(2));
  ll res=0;
  while(q--){
    int i,m;
    cin >> i >> m;
  
    upd(1,1,n,i,m);
    node r = tree[1];
    ll mx = 0;
    rep(i,0,2)rep(j,0,2)mx=max(mx,r.best[i][j]);
    res+=mx;
  }
  cout << res << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
