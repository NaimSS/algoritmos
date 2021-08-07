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
const int N = 1010;
int mat[N][N];
int d[N][N][2][4];

struct coisa{
  int i,j,c,k;
  coisa(){}
  coisa(int i,int j,int c,int k):i(i),j(j),c(c),k(k){}
};

//coisa pai[N][N][2][4];
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

bool ok(int i,int j,int c){
  if(i<=0 or i > n or j<=0 or j > m)return 0;
  if(mat[i][j] == 0)return 0;
  if(mat[i][j] == 3)return c==1;
  return 1;
}

int32_t main(){
  fastio;
  ifstream cin("dream.in");
  ofstream cout("dream.out");
  cin >> n >> m;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      cin >> mat[i][j];
    }
  }
  ms(d,-1);
  queue<coisa> q;
  q.push(coisa(1,1,0,0));
  d[1][1][0][0] = 0;
  while(!q.empty()){
    coisa A = q.front();
    q.pop();
    int i = A.i,j = A.j;
    int c= A.c;
    int KK = A.k;

   if(i == n and j == m){

      /*
      coisa cur = A;
      while(cur.i!=1 or cur.j!=1){
        cout << cur.i<<" "<<cur.j<<" "<<cur.c<<" "<<cur.k<<" == "<<d[cur.i][cur.j][cur.c][cur.k] << endl;
        if(cur.i<=0 or cur.j<=0)break;
        cur = pai[cur.i][cur.j][cur.c][cur.k];
      }
      */
      return cout << d[i][j][c][KK] << endl,0;
    }
    bool done = 1;
    for(int k=0;k<4;k++){
      int ni = i + dx[k];
      int nj = j + dy[k];
      int nc = c;

      if(mat[ni][nj] == 2)nc = 1;
      if(mat[ni][nj] == 4)nc = 0;
      int nK = k;
      if(ok(ni,nj,c) and mat[i][j]==4 and k!=KK){
        continue;
      }
      if(ok(ni,nj,c) and d[ni][nj][nc][nK] == -1){
        d[ni][nj][nc][nK] = d[i][j][c][KK] + 1;
        q.push(coisa(ni,nj,nc,nK));
        
        //pai[ni][nj][nc][nK] = coisa(i,j,c,KK);
      }
      if(ok(ni,nj,c) and mat[i][j] == 4){
        done = 0;
      }
    }
    if(done){
      for(int k=0;k<4;k++){
        int ni = i + dx[k];
        int nj = j + dy[k];
        int nc = c;
        if(mat[ni][nj] == 2)nc = 1;
        if(mat[ni][nj] == 4)nc = 0;
        int nK = k;
        
        if(ok(ni,nj,c) and d[ni][nj][nc][nK] == -1){
          d[ni][nj][nc][nK] = d[i][j][c][KK] + 1;
          q.push(coisa(ni,nj,nc,nK));
          // pai[ni][nj][nc][nK] = coisa(i,j,c,KK);
        }
      }
    }
  }
  cout << -1 << endl;
  return 0;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
