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

const int N = 200100;
vi g[N];
int pai[N];
queue<int>  q;
int Sz[N];
int f(int x){
  return pai[x] = (pai[x]==x?x:f(pai[x]));
}

void join(int a,int b){
  a=f(a),b=f(b);
  if(a==b)return;
  if(Sz[a] > Sz[b])swap(a,b);
  Sz[b]+=Sz[a];
  pai[a]=b;
  g[b].insert(end(g[b]),begin(g[a]),end(g[a]));
  g[a].clear();
  if(sz(g[b]) > 1)q.push(b);
}

int foi[N];

int32_t main(){
  fastio;
  
  ifstream cin("fcolor.in");
  ofstream cout("fcolor.out");
  
  int n,m;
  cin >> n >> m;
  for(int i=0;i<m;i++){
    int a,b;
    cin >> a >> b;
    g[a].pb(b);
  }

  for(int i=1;i<=n;i++){
    pai[i] = i;
    Sz[i] = 1;
    if(sz(g[i]) > 1)q.push(i);
  }

  while(!q.empty()){
    int x = q.front();
    if(sz(g[x])<=1){
      q.pop();
      continue;
    }
    int a = g[x].back();
    g[x].pop_back();
    if(a == g[x].back())continue;
    join(a,g[x].back());
  }

  int cur = 0;
  for(int i=1;i<=n;i++){
    if(!foi[f(i)])foi[f(i)] = ++cur;
    cout << foi[f(i)] << endl;
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
