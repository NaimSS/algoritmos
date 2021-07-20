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
#define Unique(v) sort(all(v));v.erase(unique(all(v)),v.end());
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
/*inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll a,ll b,ll m){
    if(b==0LL) return 1LL;
    if(b==1LL) return mod(a,m);
    ll k = mod(exp(a,b/2,m),m);
    if(b&1LL){
        return mod(a*mod(k*k,m),m);
    }
    else return mod(k*k,m);
}*/

const int N = 5e4 + 100;
const int M = 1e9 + 7;
const int K = 21;
int A[N];
int n,k;
const int Q = 200100;
int res[Q],L[Q],R[Q];
inline int mod(int a){
  if(a>=M)a-=M;
  return a;
}
int dp[N];
int ansl[N][K],ansr[N][K];
void calcL(int l,int r){
  for(int i=l;i<=r;i++)for(int j=1;j<=k;j++)ansl[i][j]=0;
  for(int ck=k;ck>=1;ck--){
    
    for(int j=ck;j<=k;j++)dp[j]=0;
    
    for(int i=r;i>=l;i--){

      if(A[i] == ck){
        for(int j = ck;j<=k;j++){
          if(j == ck)dp[j] = mod(dp[j]*2 + 1);
          else dp[j] = mod(dp[j] + mod(dp[j] + ansl[i][j]));
        }
      }

      for(int j=ck;j<=k;j++){
        ansl[i][j] = mod(ansl[i][j] + dp[j]);
      }

    }

  }  
}
void calcR(int l,int r){
  rep(i,l,r+1)rep(j,1,k+1)ansr[i][j]=0;
  for(int ck=1;ck<=k;ck++){
    
    for(int j=1;j<=ck;j++)dp[j]=0;

    for(int i=l;i<=r;i++){

      if(A[i] == ck){

        dp[ck] = mod(dp[ck] * 2 + 1);
        for(int j=ck-1;j>=1;j--){
          dp[j] = mod(dp[j] + mod(dp[j] + ansr[i][j]));
        }
      }

      for(int j=1;j<=ck;j++){
        ansr[i][j] = mod(ansr[i][j] + dp[j]);
      }
    }


  }
  for(int i=l;i<=r;i++){
    for(int j=k-1;j>=1;j--){
      ansr[i][j] = mod(ansr[i][j] + ansr[i][j+1]);
    }
  }
}

void solve(int l,int r,vi& qry){
  if(sz(qry) == 0)return;
  if(l == r){
    for(int x : qry)res[x] = 2;
    qry.clear();
    return;  
  }
  int mid = (l+r)/2;
  vi cur,left,right;
  for(int x : qry){
    if(R[x]<=mid)left.pb(x);
    else if(L[x]>mid)right.pb(x);
    else cur.pb(x);
  }
  qry.clear();
  solve(1,mid,left);
  solve(mid+1,r,right);
  if(sz(cur) == 0)return;

  calcL(l,mid);
  calcR(mid+1,r);

  for(int id : cur){
    for(int j=1;j<=k;j++){
      ll cur = 1ll * ansl[L[id]][j] * ansr[R[id]][j] %M;
      res[id] = mod(res[id] + cur);
      res[id] = mod(res[id] + ansl[L[id]][j]);
    }
    res[id] = mod(res[id] + ansr[R[id]][1]);
    res[id] = mod(res[id] + 1);
  }

}

int32_t main(){
  fastio;
  
  ifstream cin("nondec.in");
  ofstream cout("nondec.out");
  
  cin >> n >> k;

 
  for(int i=1;i<=n;i++)cin >> A[i];
  int q;
  cin >> q;
  vi qry(q);
  for(int i=0;i<q;i++){
    qry[i] = i;
    cin >> L[i] >> R[i];
  }
  solve(1,n,qry);
  for(int i=0;i<q;i++){
    res[i] = mod(res[i]);
    cout << res[i] << endl;
  }  
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
