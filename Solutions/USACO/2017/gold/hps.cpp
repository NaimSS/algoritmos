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
#define sz(v) ((int)v.size())
#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left sefude
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl; 
#define prl cerr<<"called: "<< __LINE__ << endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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


int n,k;
const int N = 100100;
int v[N];
int dp[N][22][3];
int solve(int id,int q,int c){
  if(id == n + 1)return 0;
  if(dp[id][q][c]!=-1)return dp[id][q][c];
  int &x = dp[id][q][c];
  x=0;
  if(q!=k)rep(j,0,3)if(j!=c)x = max(x,solve(id,q+1,j));
  x = max(x,solve(id+1,q,c) + ((c+1)%3 == v[id]));
  return x;
}

int32_t main(){
  fastio;
    ifstream cin("hps.in");
  ofstream cout("hps.out");
  cin >> n >> k;
  ms(dp,-1);
  for(int i=1;i<=n;i++){
    char c;
    cin>>c;
    if(c=='H')v[i]=0;
    else if(c=='S')v[i] =1;
    else v[i]=2;
  }
  cout << max({solve(1,0,0),solve(1,0,1),solve(1,0,2)}) << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
