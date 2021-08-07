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
#define int long long
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

const int N = 100100;
int bit[N];
int pos[N];
void upd(int x,int v){
  while(x<N){
    bit[x]+=v;
    x+=(x&-x);
  }
}
int query(int x){
  int r=0;
  while(x>0){
    r+=bit[x];
    x-=(x&-x);
  }
  return r;
}
int query(int l,int r){return query(r) - query(l-1);}
int a[2*N];
int ar[N],br[N];
int32_t main(){
  fastio;
  
  ifstream cin("mincross.in");
  ofstream cout("mincross.out");
  
  int n;
  cin>>n;
  for(int i=1;i<=n;i++){
    cin >> ar[i];
  }

  for(int i=1;i<=n;i++){
    cin >> br[i];
  } 
  ll res = 1e18;

  rep(iter,0,2){
  
  rep(i,0,N)bit[i]=0;
    for(int i=1;i<=n;i++){
      pos[ar[i]] = i;
    }
   
    for(int i=1;i<=n;i++){
      a[i] = pos[br[i]];
      a[i+n] = a[i];
    }
    for(int i=1;i<=n;i++)swap(ar[i],br[i]);
    ll cur=0;

    for(int i=1;i<=2*n;i++){
      if(i>n){
        // tira i-n:
        upd(a[i],-1);
        cur-=query(a[i]-1);

      }
      upd(a[i],1);
      cur+=query(a[i]+1,n);
      if(i>=n)res = min(res,cur);
  //    if(i>=n)cout <<i <<" "<<cur << endl;
    }
  }
  cout << res << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
