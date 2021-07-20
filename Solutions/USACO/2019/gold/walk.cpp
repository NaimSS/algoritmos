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



const ll h1 = 2019201913;
const ll h2 = 2019201949;
const ll h3 = 2019201997;
int n,k;
const int N = 7501;
ll d[N];
bool vis[N];

ll dist(int i,int j){
  if(i>j)swap(i,j);
  return (i*h1 + j*h2)%h3;
}

void prim(){
  for(int i=1;i<=n;i++)d[i] = h3;

  for(int iteraa=1;iteraa<=n;iteraa++){
    ll best = h3+1;
    int id = 0;
    
    for(int j=1;j<=n;j++){
      if(d[j]<best and !vis[j]){
        best = d[j];
        id = j;
      }
    }

    vis[id] = 1;

    for(int j=1;j<=n;j++){
      if(vis[j])continue;
      assert(dist(id,j) >=0 );
      if(d[j] > dist(id,j)){
        d[j] =  dist(id,j);
      }
    }

  }

}

int32_t main(){
  fastio;
  
  ifstream cin("walk.in");
  ofstream cout("walk.out");
  
  cin >> n >> k;
  
  prim();
  sort(d+1,d+1+n);


  
  cout << d[n+1-k] << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
