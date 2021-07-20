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
//#define sz(v) (int)v.size()
//#define int long long
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

const int N = 2e5 + 100;

void rotate(int &a,int &b){
  int c = a,d = b;
  a = c + d;
  b = d - c;
}
int x[N],y[N];

int32_t main(){
  fastio;

  ifstream cin("mountains.in");
  ofstream cout("mountains.out");
  
  int n;
  cin >> n;
  vi id;
  for(int i=1;i<=n;i++){
    cin >> x[i] >> y[i];
    for(int j=0;j<1;j++)rotate(x[i],y[i]);
    id.pb(i); 
  }


  sort(all(id),[&](int a,int b){
    if(x[a] == x[b])return y[a] > y[b];
    return x[a] > x[b];
  });
  int res = 0;
  set<int> S;
  for(int i : id){
    auto it = S.lower_bound(y[i]);
    if(it!=S.end()){

    }else{
      res++;
      S.insert(y[i]);
    }
  }
  
  cout << res << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
