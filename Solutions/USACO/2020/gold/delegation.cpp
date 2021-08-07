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
#define prl cerr<<"called: "<< __LINE__<<endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll a,ll b,ll m){
  a%=m;
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
int sobra[N];
int cnt[N];
int k;
int dfs(int v,int p = -1){
  vi tam;
  for(int to : g[v])if(to!=p){
    int res = dfs(to,v);
    if(res == -1)return -1;
    if(res+1!=k){
      tam.pb(res + 1);
    }
  }
  for(int x : tam){
    if(cnt[k - (x)])cnt[k - x]--;
    else cnt[x]++;
  }
  int tot=0;
  int res=0;
  for(int x : tam){
    tot+=cnt[x];
    if(cnt[x])res = x;
    cnt[x] = 0;
  }
  if(tot > 1)return -1;

  return res;
}

int res[N];
int32_t main(){
  fastio;
  
  ifstream cin("deleg.in");
  ofstream cout("deleg.out");
  
  int n;
  cin >> n;

  for(int i=1;i<n;i++){
    int a,b;
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
  }
  int estrela = 0,big=0;
  for(int i=1;i<=n;i++){
    if(sz(g[i]) > 2){
      estrela++;
      big = i;
    }
  }
  if(estrela!=1){
  for(int i=1;i<=n-1;i++){
    if((n-1)%i == 0){
      k = i;
      if(dfs(1) == 0)res[i] = 1;
    }
    cout << res[i];
  }  
  cout<<endl;
  }else{
    vi tam;
    k = n + 1;
    
    for(int x : g[big]){
      tam.pb(dfs(x,big) + 1);
    }

    for(int i=1;i<=n-1;i++){
      if((n-1)%i == 0){

        int val = -1,foi = 0;
        res[i] = 1;
        for(int x : tam){
          if(x%i == 0)continue;
          cnt[x%i]++;
        }

        for(int j=1;j<=i;j++){
          if(cnt[j] != cnt[i - j]){
            res[i] = 0;
          }
          cnt[j] = cnt[i-j] = 0;
        }

      }

      cout << res[i];
    }
    cout << endl;

  }
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
