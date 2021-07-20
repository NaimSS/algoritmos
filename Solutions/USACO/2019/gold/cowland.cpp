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
  ll x;
  node operator+(const node &rhs) const{  // exemplo de operador de merge
    node r;
    r.x = x^rhs.x;
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
    if(x > y)swap(x,y);
    for(x += n, y += n+1 ; x < y ; x/=2 , y/=2){
      if(x&1) ra = ra + st[x] , x++;
      if(y&1) --y , rb = st[y] + rb;
    }
    return ra + rb;
  }
};


const int N = 200100;
int e[N],tin[N],tout[N];
vi g[N];
int t=0;
int ans[N][20];

void dfs(int v,int p = -1){
  tin[v] = t ++ ;

  for(int to : g[v]){
    if(to==p)continue;
    ans[to][0] = v;
    dfs(to,v);
  }

  tout[v] = t ++ ;
}


int is_ans(int a,int b){
  return tin[a]<=tin[b] and tout[a]>=tout[b];
}

int lca(int a,int b){
  if(is_ans(a,b))return a;
  for(int j=19;j>=0;j--){
    if(!is_ans(ans[a][j],b))a = ans[a][j];
  }
  return ans[a][0];
}

int32_t main(){
  fastio;
  
  ifstream cin("cowland.in");
  ofstream cout("cowland.out");

  int n,q;
  cin>>n>>q;
  for(int i=0;i<n;i++){
    cin >> e[i];
  }
  for(int i=0;i<n-1;i++){
    int a,b;
    cin>>a>>b;
    a--;b--;
    g[a].pb(b);
    g[b].pb(a);
  }
  ans[0][0] = 0;
  dfs(0);

  ST<node> T(2*n,{0});
  rep(j,1,20){
    rep(i,0,n){
      ans[i][j] = ans[ans[i][j-1]][j-1];
    }
  }
  for(int i=0;i<n;i++){
    T.upd(tin[i],{e[i]});
    T.upd(tout[i],{e[i]});
  }

  while(q--){
    int op,a,b;
    cin>>op>>a>>b;
    if(op == 1){
      a--;
      e[a] = b;
      T.upd(tin[a],{e[a]});
      T.upd(tout[a],{e[a]});
    }else{
      a--;b--;
      ll r = T.query(tin[0],tin[a]).x ^ T.query(tin[0],tin[b]).x ^ e[lca(a,b)];
    
      cout << r << endl;
    }
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
