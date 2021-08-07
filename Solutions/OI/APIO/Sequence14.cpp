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

const int N = 100100;
ll pre[N],a[N];
ll dp[N][2];
int go[N][210];
typedef pair<ll,ll> pll;
#define pii pll
struct coisa{
  pll p;
  int id;
  coisa(){}
  coisa(pll p,int id):p(p),id(id){}
};
struct cht {
    int p = 0;
    vector<coisa> func;
    
    //Cuidado com OVERFLOW
    bool bad(pii A, pii B, pii C){

    return (ll)(B.ss - A.ss)*(A.ff - C.ff) > (ll)(C.ss - A.ss)*(A.ff - B.ff);
    }
    ll f(pll r, ll x){
        return 1ll*r.ff*x + r.ss;
    }
    void addline(pii r,int id) {
      swap(r.ff,r.ss);

        if(!func.empty() and func.back().p.ff == r.ff){
            if(func.back().p.ss <= r.ss) return;
            func.pop_back();
            if(p == sz(func)) p--;
        }
        while(func.size() >= 2 && bad(func[sz(func) - 2].p, func[sz(func) - 1].p, r)){
            func.pop_back();
            if(p == sz(func)) p--;
        }
        func.push_back(coisa(r,id));
    }
    pll queryMin(ll x){
      if(func.empty() || p >= sz(func))return pll(0,0);
        
        while(p < sz(func) - 1 && f(func[p].p, x) > f(func[p + 1].p, x)) p++;
        return pll(f(func[p].p, x),func[p].id);
    }

};
int32_t main(){
  fastio;
  int n,K;
  cin >> n >> K;

  for(int i=1;i<=n;i++){
    cin >> a[i];
    pre[i] = a[i] + pre[i-1];
  }
  for(int k=1;k<=K;k++){
    int cur = k&1,last = cur^1;
    cht CHT;

    //CHT.addline(pll(0,0),0);
    CHT.addline(pll( - (dp[k][last] - 1ll * pre[k]*pre[k]), - pre[k]),k);

    for(int i=k+1;i<=n;i++){
     
        pll best = CHT.queryMin( pre[i]);
        if(best.ss == 0)best.ss = i-1;
        go[i][k] = best.ss;
        dp[i][cur] = - best.ff;  
      
   
      CHT.addline(pll(-  (dp[i][last] - 1ll * pre[i]*pre[i]), - pre[i]),i);
    }
  }
  cout << dp[n][K&1] << endl;
  vi res;
  int cur = n;
  for(int i=K;i>=1;i--){
    res.pb(go[cur][i]);
    cur = go[cur][i];
  }
  for(int x : res)cout << x<<" ";
  cout<<endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
