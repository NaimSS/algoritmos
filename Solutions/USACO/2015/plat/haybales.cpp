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
//#define int long long
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


struct LAZY{
vector<ll> mn,sum,lazy;
int n;
LAZY(){}
LAZY(int _n){ // pass a vector/array if needed
  n = _n;
  mn = sum = lazy = vector<ll>(4*n+10,0);
}




void propagate(int no,int i,int j){
  if(lazy[no]==0)return;
  mn[no]+=lazy[no];
  sum[no]+=lazy[no]*(j-i+1);
  if(i!=j){
    lazy[2*no]+=lazy[no];
    lazy[2*no+1]+=lazy[no];
  }
  lazy[no] = 0;
}

void update(int no,int i,int j,int a,int b,ll v){
  propagate(no,i,j);
  if(i>b || j<a || i>j)return;
  if(a<=i && j<=b){
    lazy[no]+=v;
    propagate(no,i,j);
    return;
  }
  int m = (i+j)/2;
  int l = 2*no,r=2*no+1;
  update(l,i,m,a,b,v);
  update(r,m+1,j,a,b,v);  
  mn[no] = min(mn[l],mn[r]);
  sum[no] = sum[l]+sum[r];
}

ll querymn(int no,int i,int j,int a,int b){
  propagate(no,i,j);
  if(i > b || j < a)return 1e15;
  if(a<=i and j<=b)return mn[no];
  int mid =(i+j)>>1,l=no<<1,r=no<<1|1;
  return min(querymn(l,i,mid,a,b),querymn(r,mid+1,j,a,b));
}
ll querysum(int no,int i,int j,int a,int b){
  propagate(no,i,j);
  if(i>b || j <a)return 0;
  if(a<=i and j<=b)return sum[no];
  int mid =(i+j)>>1,l=no<<1,r=no<<1|1;
  return querysum(l,i,mid,a,b) + querysum(r,mid+1,j,a,b); 
}

};



int32_t main(){
  fastio;
    ifstream cin("haybales.in");
  ofstream cout("haybales.out");
  int n,q;
  cin >> n >> q;
  LAZY L(n);
  for(int i=1;i<=n;i++){
    int x;cin>>x;
    L.update(1,1,n,i,i,x);
  }
  while(q--){
    char op;
    cin >> op;
    if(op == 'P'){
      int a,b,c;
      cin >> a >> b >> c;
      L.update(1,1,n,a,b,c);
    }else{
      int a,b;
      cin >> a>>b;
      cout << (op == 'M' ? L.querymn(1,1,n,a,b) : L.querysum(1,1,n,a,b)) << endl;
    }
  }
  
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
