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
#define int long long
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


struct BIT{
 int n;
 int MAX;
 vector<ll> bit;
 BIT(){}
 BIT(int _n){
   n = _n;
   MAX = n +2;
   bit.resize(n+10,0);
 }
 
 ll query(int x){
   ll r=0;
   while(x>0){
     r+=bit[x];
     x-=(x&-x);
   }
   return r;
 }
 
 ll query(int l,int r){
  if(l > r){
    return 0;
  }
  assert(l<=r);

   return query(r) - query(l-1);
 }
 
 void update(int x,ll val){
   while(x<MAX){
     bit[x]+=val;
     x+=(x&-x);
   }
 }
 
 ll find_kth(ll k){
   ll sum=0;
   ll pos=0;
   // 20 == log -> trocar conforme necessario
   for(int i=20;i>=0;i--){
     if(pos+(1LL<<i)>n)continue;
     int atual = bit[pos+(1LL<<i)];
     if(sum+atual<k){
       sum+=atual;
       pos+=(1LL<<i);
     }
     
   }
   
   //acha a maior pos com <k;
   return pos+1;
 }
   
};

  vi comp;
struct mediana{
  int n;
  int tot;
  BIT freq,sum;
  mediana(){}
  mediana(int n,int tot):n(n),tot(tot){
    freq = sum = BIT(n+n);
  }
  void insert(int x){
    int pos = lower_bound(all(comp),x) - comp.begin() + 1;
    tot++;
    freq.update(pos,1);sum.update(pos,x);
  }
  ll f(){
    int pos = freq.find_kth(tot/2);
    ll val = comp[pos-1];

    ll r = freq.query(pos) * val - sum.query(pos);
    r+= sum.query(pos + 1,n + n) - freq.query(pos+1,n+n) * val;
    return r; 
  }
  void clear(){
    tot=0;
    freq = sum = BIT(n+n);
  }
};

const int N = 100100;
int S[N],T[N];
char P[N],Q[N];

int pre[N],suf[N];

int32_t main(){
  fastio;
  int k,n;
  cin >> k >> n;
  vector<pii> vec;
  ll bef=0;
  for(int i=1;i<=n;i++){
    cin >> P[i] >> S[i] >> Q[i] >> T[i];
    if(S[i] > T[i])swap(S[i],T[i]);
    if(P[i] == Q[i]){

      bef+=T[i] - S[i];
    }else{
      bef++;
      vec.pb(pii(S[i],T[i]));
      comp.pb(S[i]);comp.pb(T[i]);
    }
  }
  sort(all(comp));
  comp.erase(unique(all(comp)),comp.end());
  sort(all(vec),[&](pii a,pii b){
    return a.ff + a.ss < b.ff + b.ss;
  });
  int tam = sz(vec);
  if(tam == 0){
    cout << bef << endl;
    return 0;
  }
  mediana Med(n,0);


  for(int i=0;i<tam;i++){
    Med.insert(vec[i].ff);Med.insert(vec[i].ss);
    pre[i] = Med.f();
  }
  Med.clear();
  for(int i = tam-1;i>=0;i--){
    Med.insert(vec[i].ff);Med.insert(vec[i].ss);
    suf[i] = Med.f();
  }

  ll ans = pre[tam-1];
  if(k == 2){
  for(int i=0;i<tam-1;i++){
    ans = min(ans,pre[i] + suf[i+1]);
  }
  }
  cout << ans + bef << endl;



  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
