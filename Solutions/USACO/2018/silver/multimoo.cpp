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
#define prl cerr<<"called: "<< __LINE__<<endl;
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

const int N = 255;
int mat[N][N];
int n;
int pai[N*N];
int tam[N*N];

int get(int i,int j){
  return n*(i-1) + j - 1;
}

int f(int x){return pai[x]=(pai[x]==x?x:f(pai[x]));}
int getf(int i,int j){
  return f(get(i,j));
}
void join(int a,int b){
  a=f(a),b=f(b);
  if(a==b)return;
  if(tam[a]>tam[b])swap(a,b);
  tam[b]+=tam[a];

  pai[a]=b;
}
int res1=0,res2=0;

int ID=0;
int vis[N*N];

struct grafo{
  map<int,set<int> > go;
};

map<pii,grafo> g;
map<pii,vector<int> >cor;
int sla[4*N*N][3]; // bruh
void addEdge(int a,int b,int c1,int c2){
  ID++;
  if(c1 > c2){
    swap(c1,c2);
    swap(a,b);
  }
  //cout << a<<" -> "<<b<<endl;
  g[pii(c1,c2)].go[a].insert(b);
  g[pii(c1,c2)].go[b].insert(a);
  cor[pii(c1,c2)].pb(ID);
  sla[ID][0] = a,sla[ID][1] = c1,sla[ID][2] = c2; 
}

int c1,c2;
int T=0;
int dfs(int v){
  if(vis[v] == T)return 0;
  vis[v] = T;
  int res = tam[v];
  for(int to : g[pii(c1,c2)].go[v]){
    if(vis[to] == T)continue;
    res+=dfs(to);
  }
  

  return res;
}

int32_t main(){
  fastio;
  
  ifstream cin("multimoo.in");
  ofstream cout("multimoo.out");
  
  cin>>n;
  vi comp;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      cin >> mat[i][j];
      comp.pb(mat[i][j]);
      tam[get(i,j)]=1;
      pai[get(i,j)] = get(i,j);

    }
  }
  Unique(comp);
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      mat[i][j] = lower_bound(all(comp),mat[i][j]) - comp.begin() + 1;
    }
  }

  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      if(i+1<=n and mat[i][j] == mat[i+1][j])join(get(i,j),get(i+1,j));
      
      if(j+1<=n and mat[i][j] == mat[i][j+1]){
        
       join(get(i,j),get(i,j+1));
      }
    }
  }

  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      res1 = max(res1,tam[getf(i,j)]);
      if(i+1<=n and getf(i,j)!=getf(i+1,j)){
        addEdge(getf(i,j),getf(i+1,j),mat[i][j],mat[i+1][j]);
      }
      
      if(j+1<=n and getf(i,j)!=getf(i,j+1)){
        addEdge(getf(i,j),getf(i,j+1),mat[i][j],mat[i][j+1]);
      }
    }
  }
  assert(ID < 4*N*N);
  for(auto vec : cor){
    T++;
    for(int id : vec.ss){
      int ini = sla[id][0];
      c1 = sla[id][1],c2 = sla[id][2];
      int d = dfs(ini);
      res2 = max(res2,d);
    }
  }

  cout << res1 << endl;
  cout << res2 << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
