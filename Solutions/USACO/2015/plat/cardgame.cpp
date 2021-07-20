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
bool mark[N];
struct node{
  int l1,l2,res;
  node(){
    l1 = l2 = res = 0;
  }
  node operator+(const node & o)const{
    node r;
    int put = min(l1,o.l2);
    r.res = put + res + o.res;
    r.l1 = l1 + o.l1 - put;
    r.l2 = l2 + o.l2 - put;
    return r;
  }
}tree[4*N];
void clear(){
  rep(i,0,4*N)tree[i] = node();
}
void upd(int no,int i,int j,int p,int v){
  if(i == j){
    tree[no].res = tree[no].l1 = tree[no].l2 = 0;
    if(v == 1)tree[no].l2 = 1;
    else tree[no].l1 = 1;
    return;
  }
  int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
  if(p<=mid)upd(l,i,mid,p,v);
  else upd(r,mid+1,j,p,v);
  tree[no] = tree[l] + tree[r];
}
void upd(int p,int v){
  upd(1,1,N-1,p,v);
}

void calc(int res[],vi v1,vi v2){
  clear();
  res[0] = 0;
  for(int i=0;i<sz(v1);i++){
    upd(v1[i],1);
    upd(v2[i],-1);
    res[i+1] = tree[1].res;
  }
}

int res[2][N];

int32_t main(){
  fastio;
  
  ifstream cin("cardgame.in");
  ofstream cout("cardgame.out");
  
  int n;
  cin >> n;
  vi v2(n);
  for(int i=1;i<=n;i++){
    cin >> v2[i-1];
    mark[v2[i-1]] = 1;
  }
  vi v1;
  for(int i=1;i<=n*2;i++)if(!mark[i])v1.pb(i);
  sort(all(v1),greater<int>());
  calc(res[0],v1,v2);  
  rep(i,0,n){
    v1[i] = 2*n - v1[i] + 1;
    v2[i] = 2*n - v2[i] + 1;
  }
  reverse(all(v1));
  reverse(all(v2));
  calc(res[1],v1,v2);
  int ans=0;
  for(int i=0;i<=n;i++){
    ans = max(ans,res[0][i] + res[1][n-i]);
  }
  cout << ans << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
