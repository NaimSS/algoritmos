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

const int N = 100100;
struct edge{
  int a,b,c;
  edge(){}
}e[N];

int res[N];

int pai[N],sz[N];
int f(int x){
  return pai[x] = (pai[x]==x ? x : f(pai[x]));
}
void join(int a,int b){
  a = f(a),b = f(b);
  if(a == b)return;
  if(sz[a] > sz[b])swap(a,b);
  sz[b]+=sz[a];
  pai[a] = b;
}


struct query{
  int k,v,id;
  query(){}
};

int32_t main(){
  fastio;

  ifstream cin("mootube.in");
  ofstream cout("mootube.out");

  int n,q;
  cin >> n >> q;

  for(int i=0;i<n - 1;i++){
    cin >> e[i].a >> e[i].b >> e[i].c;
  }

  for(int i=1;i<=n;i++){
    pai[i] = i,sz[i] = 1;
  }

  sort(e,e+n-1,[&](edge a,edge b){
    return a.c > b.c;
  });
  vector<query> v(q);
  for(int i=0;i<q;i++){
    cin >> v[i].k >> v[i].v;
    v[i].id = i;
  }
  sort(all(v),[&](query a,query b){
    return a.k > b.k;
  });


  int pt = 0;
  for(int i=0;i<q;i++){
    while(pt < n-1 and e[pt].c >= v[i].k){
      join(e[pt].a,e[pt].b);
      pt++;
    }
    res[v[i].id] = sz[f(v[i].v)];
  }

  for(int i=0;i<q;i++){
    cout << res[i] -1 << endl;
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
