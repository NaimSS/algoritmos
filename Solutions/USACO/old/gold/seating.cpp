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

struct node{
  int best,pre,suf;
  int tam,tot;
  node(){}
  node(int x){
    pre = suf = best = max(x,0);
    tam = 1;
    tot = x;
  }
  node operator+(const node& o)const{
    node r;
    r.tam = tam + o.tam;
    r.tot = tot + o.tot;
    r.pre = pre;
    r.suf = o.suf;
    if(tot == tam)r.pre = max(r.pre,o.pre + tam);
    if(o.tot == o.tam)r.suf = max(r.suf,o.tam + suf);
    r.best = max({best,o.best,suf + o.pre});
    return r;
  }
};
const int N = 500100;
int lazy[4*N];
node tree[4*N];



void build(int no,int i,int j){
  lazy[no ]= -1;
  if(i == j){
    tree[no] = node(1);
    return ;
  }
  int mid = (i + j)>>1,l=no<<1,r=no<<1|1;
  build(l,i,mid);
  build(r,mid+1,j);
  tree[no] = tree[l] + tree[r];
}
void flush(int no,int i,int j){
  if(lazy[no]==-1)return;
  if(lazy[no] == 1){
    tree[no].best = tree[no].pre = tree[no].suf = (j-i+1);
  }else tree[no].best = tree[no].pre = tree[no].suf = 0;
  tree[no].tot = lazy[no] * (j-i+1);
  if(i!=j)lazy[no<<1]=lazy[no<<1|1]=lazy[no];
  lazy[no] = -1;
}
void upd(int no,int i,int j,int a,int b,int v){
  flush(no,i,j);
  if(i > b || j < a)return;
  if(a<=i and j<=b){
    lazy[no] = v;
    flush(no,i,j);
    return;
  }
  int mid = (i + j)>>1,l=no<<1,r=no<<1|1;
  upd(l,i,mid,a,b,v);
  upd(r,mid+1,j,a,b,v);
  tree[no] = tree[l] + tree[r];
}
void pushdown(int no,int i,int j){
  int mid = (i + j)>>1,l=no<<1,r=no<<1|1;
  flush(no,i,j);
  if(i==j)return;
  flush(l,i,mid);flush(r,mid+1,j);
  tree[no] = tree[l] + tree[r];
}

int walk(int no,int i,int j,int k){
  pushdown(no,i,j);
  
  if(tree[no].best < k)return -1;
  if(i == j)return i;
  int mid = (i + j)>>1,l=no<<1,r=no<<1|1;
  if(tree[l].best >= k)return walk(l,i,mid,k);
  if(tree[l].suf + tree[r].pre >= k){
    return mid - tree[l].suf + 1;
  }
  return walk(r,mid+1,j,k);
}


int32_t main(){
  fastio;
  
  ifstream cin("seating.in");
  ofstream cout("seating.out");
  
  int n,q;
  cin >> n >> q;
  build(1,1,n);
  int res=0;
  while(q--){
    char op;
    cin >> op;
    if(op == 'A'){
      // put 
      int p;
      cin >> p;
      int pos = walk(1,1,n,p);
      if(pos == -1)res++;
      else upd(1,1,n,pos,pos + p - 1,0);
    }else{
      int l,r;
      cin >> l >> r;
      upd(1,1,n,l,r,1);
    }
  } 
  cout << res << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
