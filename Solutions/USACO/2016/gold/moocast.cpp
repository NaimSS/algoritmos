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

const int N = 1010;
int x[N],y[N],pai[N];

int n;

int f(int x){
  return pai[x] = (pai[x]==x?x:f(pai[x]));
}
int comp;
void join(int a,int b){
  a=f(a),b=f(b);
  if(a==b)return;
  comp--;
  pai[a] = b;
}

bool ok(int v){ 
  comp = n;
  for(int i=1;i<=n;i++)pai[i]=i;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      int dx = (x[i]-x[j])*(x[i] - x[j]);
      int dy = (y[i] - y[j])*(y[i] - y[j]);
      if(dx + dy <= v){
        join(i,j);
      }
    }
  }
  return comp == 1;
}

int32_t main(){
  fastio;
    ifstream cin("moocast.in");
  ofstream cout("moocast.out");

  cin >> n;
  for(int i=1;i<=n;i++){
    cin >> x[i] >> y[i];
  }
  int l =0 ,r = 1e9;
  int ans= r;
  while(l<=r){
    int m = (l+r)/2;
    if(ok(m)){
      ans = m;
      r = m - 1;
    }else l = m+1;
  }
  cout << ans << endl;
  
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
