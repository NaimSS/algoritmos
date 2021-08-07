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
const int N = 500100;
struct node{
  int pre,suf,tot;
  int ans;
  node(){}
  node(int x){
    pre = suf = tot = ans = x;
  }
  node operator+(const node &o)const{
    node r;
    r.pre = max(pre,tot + o.pre);
    r.suf = max(o.suf,o.tot + suf);
    r.tot = tot + o.tot;
    r.ans = max({ans + o.tot,o.ans + tot,pre + o.suf});
    return r;
  }
}tree[4*N];

int v[N];
void build(int no,int i,int j){
  if(i == j){
    tree[no].pre = max(v[i],0);
    tree[no].suf = max(v[i],0);
    tree[no].tot = v[i];
    tree[no].ans = (v[i] < 0 ? 0 : 1);
    return;
  }
  int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
  build(l,i,mid);build(r,mid+1,j);
  tree[no] = tree[l] + tree[r];
}

node query(int no,int i,int j,int a,int b){
  if(i > j || i > b || j < a)return node(-1);
  if(a<=i and j<=b)return tree[no];
  int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
  node op1 = query(l,i,mid,a,b),op2 = query(r,mid+1,j,a,b);
  if(op1.ans == -1)return op2;
  if(op2.ans == -1)return op1;
  return op1 + op2;
}

int32_t main(){
  fastio;
  int n;
  cin >> n;
  for(int i=1;i<=n;i++){
    char c;
    cin>>c;
    v[i] = (c == 'C' ? -1 : 1);
  }
  build(1,1,n);
  int q;
  cin >> q;
  while(q--){
    int l,r;
    cin>>l>>r;
    cout << query(1,1,n,l,r).ans<<endl;
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
