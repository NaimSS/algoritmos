#include <bits/stdc++.h>
#define ld long double
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
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
#define sz(v) ((int)v.size())
//#define int long long  
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left oooooopss
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b,ll e,ll m){
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
      if (e & 1) ans = ans * b % m;
  return ans;
}

struct node{
  int pos,frm,dist;
  bool operator<(const node& a)const{
    return make_tuple(dist,-frm) < make_tuple(a.dist,-a.frm);
  }
};
const int N = 300100;
int vis[N];
vi g[N];
int ans[N][2];
int F[N];
int A[N];
int32_t main(){
  fastio;
  int n;
  ll k;
  cin >> n >> k;
  priority_queue<node> pq;
  for(int i=1;i<=n;i++){
    int x;
    cin>>x;
    pq.push({i,i,x});
  }
  for(int i=1;i<n;i++){
    int a,b;
    cin>>a>>b;
    g[a].pb(b);
    g[b].pb(a);
  }
  while(!pq.empty()){
    auto cur = pq.top();
    pq.pop();
    int pos = cur.pos;
    int ini = cur.frm;
    int d = cur.dist;
    if(ans[pos][0] == ini || ans[pos][1]==ini || vis[pos]==2)continue;

    ans[pos][vis[pos]++] = ini;
    for(int to : g[pos]){
      pq.push({to,ini,d-1});
    }
  }

  for(int i=1;i<=n;i++){
    if(ans[i][0]==i)F[i] = ans[i][1];
    else F[i]=ans[i][0];
  }

  int cur = 1;

  int A = F[cur],B = F[F[cur]];
  ll tail,period;

  while(A!=B){
    A = F[A];
    B = F[F[B]];
  }
  tail=0;
  A = cur;
  while(A!=B){
    A = F[A];
    B = F[B];
    tail++;
  }
  period = 1;
  A = F[A];
  while(A!=B){
    A = F[A];
    period++;
  }


  cur = 1;

  rep(I,0,tail){
    k--;
    cur = F[cur];
    if(k == 0){
      cout << cur << endl;
      return 0;
    }
  }
  k%=period;
  while(k--){
    cur = F[cur];
  }
  cout << cur << endl;
  
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
