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

const int N = 505;
char mat[N][N];
ll dp[2][N][N];
const int M = 1e9 + 7;
int32_t main(){
  fastio;
  
  ifstream cin("palpath.in");
  ofstream cout("palpath.out");
  
  int n;
  cin >> n;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      cin >> mat[i][j];
    }
  } 
  
  ll ans=0;
  for(int x1=1;x1<=n;x1++){
    int cur = x1&1;

    for(int y1=1;y1<=n;y1++){
      for(int x2=n;x2>=1;x2--){
        int y2 = n-x1+1 + n-y1+1 - x2;
        dp[cur][y1][x2] = 0;
        if(x1 == 1 and y1 == 1 and x2 == n){
          assert(y2 == n);
          dp[cur][y1][x2] = (mat[1][1] == mat[n][n]);
          continue;
        }
        if(x1 + y1 == n + 1){
          // metade:
          if(x2!=x1 || y2!=y1)continue;
        }
        if(x1 + y1 > n + 1)continue; // uselless
        if(y2 <=0 || y2 > n)continue;
        if(mat[x1][y1] != mat[x2][y2])continue;

        for(int dx = -1;dx<=0;dx++){
          int dy = (dx == -1 ? 0 : -1);

          for(int dx2 = 0;dx2 <= 1 ;dx2 ++ ){
            int dy2 = (dx2 == 1 ? 0 : 1);
            
            if(x1 + dx <=0 || y1 + dy<=0 || x2+dx2>n || y2+dy2>n)continue;
            
            dp[cur][y1][x2]+=dp[(x1 + dx)&1][(y1 + dy)][(x2+dx2)];
            if(dp[cur][y1][x2]>=M)dp[cur][y1][x2]-=M;
          }
        }

        if(x1 + y1 == n + 1){
          // metade:
          ans += dp[cur][y1][x2];
          if(ans>=M)ans-=M;
        }

      }
    }
  }

  cout << ans << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
