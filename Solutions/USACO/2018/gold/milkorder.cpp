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

const int N = 100100;
vi g[N];
int grau[N];
int res[N];

vi v[N];

int n,m;

  vi order;
bool ok(int x){
  order.clear();
  for(int i=1;i<=n;i++){
    grau[i]=0;
    g[i].clear();
  }
  for(int i=1;i<=x;i++){

    for(int j=0;j<sz(v[i])-1;j++){
      g[v[i][j]].pb(v[i][j+1]);
      grau[v[i][j+1]]++;
    }

  }
  priority_queue<int,vector<int>,greater<int> > q;
  for(int i=1;i<=n;i++){
    if(grau[i] == 0){
      q.push(i);
    }
  }

  int t=n;
  while(!q.empty()){
    int cur = q.top();

    q.pop();
    res[cur] = t--;
    order.pb(cur);
    for(int to : g[cur]){
      grau[to]--;
      if(grau[to]==0)q.push(to);
    }
  }

  if(sz(order) == n)return 1;
  return 0;
}

int32_t main(){
  fastio;
  
  ifstream cin("milkorder.in");
  ofstream cout("milkorder.out");
  
  cin >> n >> m;
  for(int i=1;i<=m;i++){
    int x;
    cin >> x;
    
    v[i].resize(x);
    for(int j=0;j<x;j++)cin >> v[i][j];
  }
  
  int l = 1,r = m;
  int ans = 1;
  while(l<=r){
    int mid = (l+r)/2;
    if(ok(mid)){
      ans = mid;
      l = mid + 1;
    }else r = mid - 1;
  }
  ok(ans);
  for(int i=0;i<sz(order);i++){
    cout << order[i];
    if(sz(order)-1 == i)cout<<endl;
    else cout <<" ";
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
