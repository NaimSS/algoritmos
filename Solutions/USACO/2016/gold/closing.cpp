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

int n,m;
const int N = 200100;
int pai[N];
pii v[N];
int t[N];
int f(int x){
  return pai[x] = (pai[x] == x ? x : f(pai[x]));
}
int comp=0;
void join(int a,int b){
  a=f(a),b=f(b);
  if(a==b)return;
  comp--;
  pai[f(a)]=f(b);
}
vi g[N];
int rev[N],res[N];
int32_t main(){
  fastio;

  ifstream cin("closing.in");
  ofstream cout("closing.out");
  
  cin >>n >> m;
  for(int i=1;i<=m;i++){
    cin >> v[i].ff >> v[i].ss;
  }
  vi order;
  for(int i=1;i<=n;i++){
    order.pb(i);
    pai[i] = i;
    cin >> t[i];
    rev[t[i]] = i;
  }
  sort(all(order),[&](int a,int b){
    return rev[a] > rev[b];
  });
  for(int i=1;i<=m;i++){
    int a = v[i].ff ,b = v[i].ss;
    if(rev[a] > rev[b])swap(a,b);
    g[a].pb(b);
  }

  for(int i : order){
    comp ++ ;
    for(int x : g[i])join(x,i);
      res[rev[i]] = comp;
  }

  for(int i=1;i<=n;i++){
    if(res[i] == 1)cout <<"YES"<<endl;
    else cout<<"NO"<<endl;
  }


  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
