#include <bits/stdc++.h>
#define ld long double
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
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
//#define int long long  
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left oooooopss
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b,ll e,ll m){
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
      if (e & 1) ans = ans * b % m;
  return ans;
}

template<class T>
struct BIT{
 int n;
 int MAX;
 vector<T> bit;
 BIT(){}
 BIT(int _n){
   n = _n;
   MAX = n +2;
   bit.resize(n+10,0);
 }
 
 T query(int x){
   T r=0;
   while(x>0){
     r+=bit[x];
     x-=(x&-x);
   }
   return r;
 }
 T query(int l,int r){
   return query(r) - query(l-1);
 }
 void update(int x,T val){
   while(x<MAX){
     bit[x]+=val;
     x+=(x&-x);
   }
 }
   
};


struct BIT_RANGE{
  int n;
  BIT<ll> B[2];
  BIT_RANGE(int nn){
    n = nn;
    B[0] = B[1] = BIT<ll>(n+100);
  }
  ll pa(ll x){
    return x*(x+1)/2;
  }
  void upd(int l,int r,int v){
    B[0].update(l,-v*(l-1));
    B[0].update(r+1,+v*(l-1));
    B[1].update(l,+v);
    B[1].update(r+1,-v);
    B[0].update(r+1,v*pa(r-l+1));
  }
  ll query(int x){
    if(x<=0)return 0;
    return pa(x) * B[1].query(x) + B[0].query(x);
  }
  ll query(int l,int r){
    return query(r) - query(l-1); 
  }
};
const int N = 100100;
int32_t main(){
  fastio;
  int n;
  cin >> n;
  vector<pii> vec(n);
  BIT<ll> bit(N);

  rep(i,0,n)cin >> vec[i].ff >> vec[i].ss;
  int IT=0;
  sort(all(vec));
  for(auto it : vec){
    int H = it.ff;
    int K = it.ss;

    int L = H-K+1;
    int last = L-1;
    int maxi = bit.query(L);
    int fim = L;
    int l = 1,r = L-1;
    while(l<=r){
      int mid = (l+r)/2;
      if(bit.query(mid) <= maxi){
        fim = mid;
        r = mid - 1;
      }else l = mid + 1;
    }
    int inicio = L;
    l = L+1,r = H;
    while(l<=r){
      int mid = (l+r)/2;
      if(bit.query(mid) < maxi){
        r = mid - 1;
      }else{
        inicio = mid;
        l = mid + 1;
      }
    }

    int qtd = inicio-L+1;
    //db2(H,K);
    //cout << L<<" "<<inicio<<" "<<fim<<" "<<qtd<<endl;
    if(qtd!=K){
      bit.update(inicio+1,1);
      bit.update(H+1,-1);
    }
    l = fim,r=fim+qtd-1;
    bit.update(l,1);
    bit.update(r+1,-1);
    //for(int i=1;i<=5;i++)cout << bit.query(i)<<" ";
    //cout << endl;
  //IT++;
  //if(IT > 1)exit(0);
  }

  ll res=0;
  for(int i=1;i<N;i++){
    ll x = bit.query(i);
    //if(x)db2(i,x);
    res+=x*(x-1)/2;
  }
  cout << res << endl;

  
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
