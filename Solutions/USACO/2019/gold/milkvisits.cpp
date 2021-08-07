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
vi g[N];
int tin[N],tout[N];
int t=0;
int ans[N][20];

int H[N];
void dfs(int v,int p=-1){
  tin[v] = ++t;

  for(int to : g[v])if(to!=p){
    ans[to][0] = v;
    H[to] = H[v]+1;
    dfs(to,v);
  }
  tout[v]=  t;
}

int LCA(int a,int b){
  if(H[a] < H[b])swap(a,b);
  for(int i=19;i>=0;i--){
    if(H[a] - (1<<i) >= H[b]){
      a = ans[a][i];
    }
  }
  if(a==b)return a;
  for(int i=19;i>=0;i--){
    if(ans[a][i]!=ans[b][i]){
      a=ans[a][i],b=ans[b][i];
    }
  }
  return ans[a][0];
}

unordered_map<int,int> BIT[N];
int T[N];

void upd(int x,int c,int v){
  while(x<N){
    BIT[x][c]+=v;
    x+=(x&-x);
  }
  return ;
}
int query(int x,int c){
  int r=0;
  while(x>0){
    if(BIT[x].count(c))r+=BIT[x][c];
    x-=(x&-x);
  }
  return r;
}

int32_t main(){
  fastio;
    ifstream cin("milkvisits.in");
  ofstream cout("milkvisits.out");
  int n,q;
  cin>>n>>q;
  for(int i=1;i<=n;i++)cin >> T[i];
  for(int i=0;i<n-1;i++){
    int a,b;
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
  }
  ans[1][0]=1;
  dfs(1);
  for(int j=1;j<20;j++){
    for(int i=1;i<=n;i++){
      ans[i][j] = ans[ans[i][j-1]][j-1];
    }
  }
  for(int i=1;i<=n;i++){
    upd(tin[i],T[i],1);
    upd(tout[i]+1,T[i],-1);
  }
  string s="";
  while(q--){
    int a,b,c;
    cin>>a>>b>>c;
    int r = query(tin[a],c) + query(tin[b],c);
    int lca = LCA(a,b);
    r-=2*query(tin[lca],c);
    if(T[lca] == c)r++;
    if(r)s+='1';
    else s+='0';
  }
  cout <<s << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
