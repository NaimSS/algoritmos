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

const int N = 100100;
int a[N];
int b[N];

vector<vi> stk;

bool ok(int n){
  stk.clear();
  vi c;
  for(int i=1;i<=n;i++)c.pb(a[i]);
  sort(all(c));
  c.erase(unique(all(c)),c.end());
  for(int i=1;i<=n;i++)b[i] = lower_bound(all(c),a[i]) - c.begin() + 1;

  int small = 1;
  int cur = 0;
  for(int i=1;i<=n;i++){
    while(true){
      if(cur >= stk.size())break;
      if(sz(stk[cur])==0){
        cur++;
        continue;
      }
      if(stk[cur].back() == small){
        small ++ ;
        stk[cur].pop_back();
      }else break;
    }
    if(b[i] == small){
      small++;
      continue;
    }
    if(cur == sz(stk)){
      stk.pb(vi(0));
      stk[cur].pb(b[i]);
      continue;
    }
    if(stk[sz(stk)-1][0] < b[i]){
      stk.pb(vi(0));
      stk[sz(stk)-1].pb(b[i]);
      continue;
    }
    int l = cur,r = sz(stk) - 1;
    int ans = -1;
    while(l<=r){
      int mid = (l+r)/2;
      if(stk[mid].back() > b[i]){
        ans = mid;
        r = mid - 1;
      }else l = mid + 1;
    }
    if(ans == -1 or (ans - 1 >= cur and stk[ans-1][0] > b[i])){
      return 0;
    }

    stk[ans].pb(b[i]);
  }  
  return 1;
}

int32_t main(){
  fastio;
  
  ifstream cin("dishes.in");
  ofstream cout("dishes.out");
  
  int n;
  cin >> n;
  for(int i=1;i<=n;i++)cin >> a[i]; // permutacao
  int l = 1,r = n;
  int ans = 1;

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
