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

const int N = 200100;

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
   return query(r) - query(l-1);
 }
 
 void update(int x,ll val){
   while(x<MAX){
     bit[x]+=val;
     x+=(x&-x);
   }
 }
 

   
};


int a[N];

int32_t main(){
  fastio;
    ifstream cin("sleepy.in");
  ofstream cout("sleepy.out");
  int n;
  cin>>n;
  for(int i=1;i<=n;i++){
    cin >> a[i];
  }  
  BIT T(n);
  int tot=0;
  int i;
  for(i=n;i>=1;i--){
    tot += T.query(a[i]);
    if(tot > 0)break;
    T.update(a[i],1);
  }
  

  cout << i << endl;
  for(int j=1;j<=i;j++){
    int bloco = i - j;
    int add = T.query(a[j]);
    T.update(a[j],1);
    cout << bloco + add << " \n"[j==i];
  }
  return 0;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
