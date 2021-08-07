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
int pai[N],tam[N];
int p[N],a[N],b[N],c[N];
int n,m;

int f(int x){
  return pai[x] = (pai[x]==x?x:f(pai[x]));
}
void join(int a,int b){
  a=f(a),b=f(b);
  if(a==b)return;
  if(tam[a] > tam[b])swap(a,b);
  tam[b]+=tam[a];pai[a]=b;
}

int ok(int x){
  for(int i=1;i<=n;i++){
    pai[i] = i;
    tam[i] = 1;
  }
  for(int i=0;i<m;i++){
    if(c[i]>=x)join(a[i],b[i]);
  }
  for(int i=1;i<=n;i++){
    if(f(i) != f(p[i]))return 0;
  }
  return 1;
}

int32_t main(){
  fastio;
  
  freopen("wormsort.in" , "r" , stdin);
  freopen("wormsort.out" , "w" , stdout);
  
  cin >> n >> m;
  for(int i=1;i<=n;i++){
    cin >> p[i];
  }
  int mx=0;
  for(int i=0;i<m;i++){
    cin >> a[i] >> b[i] >> c[i];
    mx = max(mx,c[i]);
  }
  int l = 0,r = (mx);
  int ans = l;
  if(ok(1e9 + 1)){
    cout << -1 << endl;
    return 0;
  }
  while(l<=r){
    int mid = (l+r)/2;
    if(ok(mid)){
      ans = mid;
      l = mid + 1;
    }else r = mid - 1;
  }
  cout << ans << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
