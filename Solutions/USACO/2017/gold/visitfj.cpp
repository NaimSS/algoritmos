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

const int N = 110;
ll d[N][N][4];
int mat[N][N];
bool vis[N][N][4];
struct cord{
  int d,i,j,k;
  cord(){}
  cord(int d,int i,int j,int k):d(d),i(i),j(j),k(k){}
  bool operator<(const cord& o)const{
    return d > o.d;
  }
};
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
int32_t main(){
  fastio;

  ifstream cin("visitfj.in");
  ofstream cout("visitfj.out");
  int n,T;
  cin >> n >> T;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      cin >> mat[i][j];
      for(int k=0;k<3;k++)d[i][j][k] = 1e16;
    }
  }
  priority_queue<cord> pq;
  d[1][1][0] = 0;
  pq.push(cord(0,1,1,0));
  while(!pq.empty()){
    int i = pq.top().i,j=pq.top().j,k=pq.top().k;
    pq.pop();
    if(vis[i][j][k])continue;
    vis[i][j][k]=1;

    for(int D = 0; D<4; D++ ){
      int l = dx[D] + i;
      int c = dy[D] + j;
      if(l<=0 || l > n || c<=0 || c>n)continue;
      int nk = k + 1;
      int cost = T;
      if(nk == 3){
        nk = 0,cost+=mat[l][c];
      }
      if(d[l][c][nk] > d[i][j][k] + cost){
        d[l][c][nk] = d[i][j][k] + cost;
        pq.push(cord(d[l][c][nk],l,c,nk));
      }
    }

  }

  ll res = 1e18;
  for(int k=0;k<3;k++)res = min(res,d[n][n][k]);

  cout << res << endl;


  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
