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
typedef pair<ll,ll> pii;
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


struct CHT{
  int s, e;
  int pa[1005], pb[1005];
  void clear(){
    s = e = 0;
  }
  void add(int x, int y){
    pa[e] = x;
    pb[e] = y;
    while(e - 2 >= s &&1ll * (pb[e-1] - pb[e-2]) * (pa[e-1] - pa[e]) > 1ll * (pb[e] - pb[e-1]) * (pa[e-2] - pa[e-1])){
      pa[e-1] = pa[e];
      pb[e-1] = pb[e];
      e--;
    }
    e++;
  }
  int query(int x){
    while(s + 1 < e && pa[s] * x + pb[s] >= pa[s+1] * x + pb[s+1]) s++;

   
    return pa[s] * x + pb[s];
  }
};
const int N = 1010;
int d[N][N];

int tem[N][N];
int sq(int x){
  return x*x;
}
int px,py,kx,ky;
bool vis[N][N];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int w,h;
bool good(int l,int c){
  return l>=1 and l<=w and c>=1 and c<=h and !vis[l][c];
}
bool ok(int x){
  queue<pii> q;
  q.push(pii(px,py));
  if(d[px][py] < x)return false;
  rep(i,0,N)rep(j,0,N)vis[i][j]=0;
  while(!q.empty()){
    pii cur = q.front();
    q.pop();
    vis[cur.ff][cur.ss]=1;
    for(int k=0;k<4;k++){
      int l = cur.ff + dx[k];
      int c = cur.ss + dy[k];
      if(good(l,c) and d[l][c]>=x ){
        vis[l][c]=1;
        q.push(pii(l,c));
      } 
    }
  }
  if(vis[kx][ky])return true;
  return false;
}

int up[N][N],dw[N][N];
int get(int a,int b){
  return (a-1) * h + b - 1;
}

struct edge{
 int a,b;
 int d;
 edge(int a,int b,int d):a(a),b(b),d(d){}
};
int pai[N*N];
int f(int x){
  return pai[x] = (pai[x] == x ? x : f(pai[x]));
}
int tam[N*N];
void join(int a,int b){
  a=f(a),b=f(b);
  if(a==b)return;
  if(tam[a] > tam[b])swap(a,b);
  tam[b]+=tam[a];
  pai[a] = b;
}


int32_t main(){
  fastio;
  cin >> w >> h;
  cin >> px>>py>>kx>>ky;
  rep(i,1,w+1)rep(j,1,h+1)d[i][j] = 1e9,pai[get(i,j)] = get(i,j),tam[get(i,j)]=1;


  int frog;
  cin >> frog;
  for(int i=1;i<=frog;i++){
    int x,y;
    cin>>x>>y;
  
    tem[x][y]=1;
    up[x][y] = dw[x][y] = x;
  }

  for(int j=1;j<=h;j++){
    for(int i=1;i<=w;i++){
      if(!up[i][j])up[i][j] = up[i-1][j];
    }
    for(int i=w;i>=1;i--){
      if(!dw[i][j])dw[i][j] = dw[i+1][j];
    }
  }
  CHT cht;
  for(int i=1;i<=w;i++){
    cht.clear();
    for(int j=1;j<=h;j++){
      int dx = 1e9;

      if(up[i][j])dx = min(dx,i-up[i][j]);
      if(dw[i][j])dx = min(dx,dw[i][j]-i);
      
      if(dx<=10000){
        cht.add(-2*j,dx * dx + j * j);
      }
    }
    for(int j=1;j<=h;j++){
      d[i][j] = cht.query(j) + j*j;
    }
  }
  if(px == kx and py == ky){
    cout << d[px][py] << endl;
    return 0;
  }
  vector<edge> vec;
  set<int> S;
  for(int i=1;i<=w;i++){
    for(int j=1;j<=h;j++){
      if(i+1<=w)vec.pb(edge(get(i,j),get(i+1,j),min(d[i][j],d[i+1][j])));
      if(j+1<=h)vec.pb(edge(get(i,j),get(i,j+1),min(d[i][j],d[i][j+1])));
    }
  }


  sort(all(vec),[&](edge a,edge b){
    return a.d > b.d;
  });
  for(auto it : vec){
    join(it.a,it.b);
    if(f(get(px,py)) == f(get(kx,ky))){
      cout << it.d << endl;
      return 0;
    }
  }
  cout << 0 << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
