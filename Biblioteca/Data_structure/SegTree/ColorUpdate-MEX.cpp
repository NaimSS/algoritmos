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
//#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left sefude
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

struct segtree{
  struct node{
    bool t[2];
    node(){}
    node(bool a,bool b){
      t[0]=a;
      t[1]=b;
    }
  };
  vector<node> tree;
  vector<int> lazy;
  int n;
  segtree(){}
  segtree(int _n){
    n = _n +10;
    tree.resize(4*n,node(1,0));
    lazy.resize(4*n,0);
  }
  void flush(int no,int i,int j){
    if(lazy[no]){
      if(lazy[no]==1){
        tree[no].t[0]=0;tree[no].t[1]=1;
      }else if(lazy[no]==2){
        tree[no].t[0]=1;tree[no].t[1]=0;
      }else{
        swap(tree[no].t[0],tree[no].t[1]);
      }
       if(i!=j){
        int l = no<<1,r=no<<1|1;
        if(lazy[no] == 3){
           if(lazy[l] == 1)lazy[l] = 2;
           else if(lazy[l]==2)lazy[l]=1;
           else if(lazy[l]==0)lazy[l]=3;
           else lazy[l]=0;
           if(lazy[r] == 1)lazy[r] = 2;
           else if(lazy[r]==2)lazy[r]=1;
           else if(lazy[r]==0)lazy[r]=3;
           else lazy[r]=0;
        }else{
          lazy[l] = lazy[r] = lazy[no];
        }

      }
    }
    lazy[no]=0;
  }
  void update(int no,int i,int j,int a,int b,int t){
    flush(no , i , j);
    if(i > j or i > b or j < a)return;
    if(a<=i and j<=b){
      lazy[no] = t;
      flush(no,i,j);
      return;
    }
    int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
    update(l,i,mid,a,b,t);update(r,mid+1,j,a,b,t);
    rep(k,0,2)tree[no].t[k]=tree[l].t[k]|tree[r].t[k];
  }

  void pushdown(int no,int i,int j){
    flush(no,i,j);
    if(i==j)return;
    int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
    flush(l,i,mid);flush(r,mid+1,j);
    rep(k,0,2)tree[no].t[k]=tree[l].t[k]|tree[r].t[k];
  }

  int get(int no,int i,int j){
    pushdown(no,i,j);
    if(i==j)return i;
    int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
    if(tree[l].t[0])return get(l,i,mid);
    else return get(r,mid+1,j);
  }

};
const int N = 100100;
ll t[N],l[N],r[N];
const ll MX = (ll)1e18+1;
int32_t main(){
  fastio;
  int q;
  cin>>q;
  vector<ll> c;
  c.pb(1);
  c.pb(MX);
  for(int i=0;i<q;i++){
    cin >> t[i]>>l[i]>>r[i];
    c.pb(l[i]);
    if(l[i]-1>0)c.pb(l[i]-1);
    if(l[i]+1<=MX)c.pb(l[i]+1);
    c.pb(r[i]);
    if(r[i]-1>0)c.pb(r[i]-1);
    if(r[i]+1<=MX)c.pb(r[i]+1);
  }
  sort(all(c));
  c.erase(unique(all(c)),c.end()); 
  int n = sz(c);
  segtree T(n);
  for(int i=0;i<q;i++){
    l[i] = lower_bound(all(c),l[i]) - c.begin() + 1;
    r[i] = lower_bound(all(c),r[i]) - c.begin() + 1;
    T.update(1,1,n,l[i],r[i],t[i]);
    cout << c[T.get(1,1,n) - 1] << endl;
  }

  // Math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
