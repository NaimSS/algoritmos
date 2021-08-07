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


map<int,int> vis,id;
int ID=0;
vi can[123100];
void go(int n){
  if(vis[n])return;
  vis[n]=1;
  id[n] = ID++;
  int cur = id[n];
  if(n == 1){
    can[cur].pb(0);
    return;
  }
  for(int i=1;i*i<=n;i++){
      if(n%i==0){
        if(i!=1){
          go(n/i);
          int Id = id[n/i];
          for(int val : can[Id]){
            can[cur].pb(val+i-1);
          }
        }
        if(n/i!=i){
          go(n/(n/i));
          int Id = id[n/(n/i)];
          for(int val : can[Id]){
            can[cur].pb(val + (n/i) - 1);
          }
        }
      }
  }
  Unique(can[cur]);
  return;
}


int32_t main(){
  fastio;
  int n;
  cin >> n;
  go(n);
  cout << sz(can[id[n]]) << endl;
  for(int x : can[id[n]]){
    cout << x<<" ";
  }
  cout << endl;
  return 0;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
