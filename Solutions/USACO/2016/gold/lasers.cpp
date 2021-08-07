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

const int N = 1e5 + 100;
int x[N],y[N];
int d[N];
map<int,vi> mx,my;

int32_t main(){
  fastio;
  ifstream cin("lasers.in");
  ofstream cout("lasers.out");


  int n;
  cin >> n;
  for(int i=1;i<=n+2;i++){
    cin >> x[i] >> y[i];
    d[i] = -1;
    mx[x[i]].pb(i);
    my[y[i]].pb(i);
  }
  queue<int> q;
  q.push(1);
  d[1] = 0;
  while(!q.empty()){
    int cur = q.front();
    q.pop();
    for(int to : mx[x[cur]]){
      if(d[to] == -1){
        d[to] = d[cur] + 1;
        q.push(to);
      }
    }
    mx[x[cur]].clear();
    for(int to : my[y[cur]]){
      if(d[to]==-1){
        d[to] = d[cur] + 1;
        q.push(to);
              }
    }
    my[y[cur]].clear();
  }
  if(d[2] < 0){
    cout << -1 << endl;
  }
  else cout << d[2] -1 << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
