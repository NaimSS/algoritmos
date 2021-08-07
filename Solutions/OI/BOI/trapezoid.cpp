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

const int N = 200100,M = 30013;

pii tree[4*N];

void upd(int no,int i,int j,int p,pii v){
  if(i == j){
    if(tree[no].ff == v.ff)tree[no].ss += v.ss;
    else if(tree[no].ff < v.ff){
      tree[no] = v;
    }
    if(tree[no].ss>=M)tree[no].ss-=M;
    return;
  }
  int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
  if(p<=mid)upd(l,i,mid,p,v);
  else upd(r,mid+1,j,p,v);
  int mx = max(tree[l].ff,tree[r].ff);
  tree[no].ff = mx;
  tree[no].ss = (tree[l].ff==mx?tree[l].ss:0) + (tree[r].ff==mx?tree[r].ss:0);
  if(tree[no].ss>=M)tree[no].ss-=M;
  assert(tree[no].ss>=0 and tree[no].ss<M);
}
pii query(int no,int i,int j,int a,int b){
  if(i > b || j < a)return pii(0,0);
  if(a<=i and j<=b)return tree[no];
  int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
  pii op1 = query(l,i,mid,a,b);
  pii op2 = query(r,mid+1,j,a,b);
  int mx = max(op1.ff,op2.ff);
  int cnt = (op1.ff==mx?op1.ss:0)+(op2.ff==mx?op2.ss:0);
  if(cnt>=M)cnt-=M;
  assert(cnt>=0 and cnt<M);
  return pii(mx,cnt);
}

int a[N],b[N],c[N],d[N];
pii val[N];

int32_t main(){
  fastio;
  /*
  ifstream cin("seating.in");
  ofstream cout("seating.out");
  */
  for(int i=0;i<N;i++)tree[i] = pii(0,0);
  int n;
  cin >> n;
  vi comp;
  vi ids;
  for(int i=1;i<=n;i++){
    cin >> a[i] >> b[i] >> c[i] >> d[i];
    assert(a[i] < b[i] and c[i] < d[i] and a[i]>0);
    
    comp.pb(a[i]);

    comp.pb(b[i]);

    ids.pb(i);
  }
  comp.pb(0);
  Unique(comp);
  int tam = sz(comp);
  for(int i=1;i<sz(comp);i++)assert(comp[i]>comp[i-1]);
  upd(1,1,tam,1,pii(0,1));
  sort(all(ids),[&](int i,int j){
    return c[i] < c[j];
  });
  
  
  priority_queue<pii,vector<pii>,greater<pii> > pq;

  for(int it=0;it<sz(ids);it++){
    int id = ids[it];
    a[id] = lower_bound(all(comp),a[id]) - comp.begin() + 1;
    b[id] = lower_bound(all(comp),b[id]) - comp.begin() + 1;
    assert(1<a[id] and a[id]<b[id] and b[id]<=tam);

    while(!pq.empty() and pq.top().ff < c[id]){
      int cur = pq.top().ss;
      pq.pop();
      upd(1,1,tam,b[cur],val[cur]);
    }

    pii X = query(1,1,tam,1,a[id]-1);
    X.ff++;
    val[id] = X;
    pq.push(pii(d[id],id));
  }
  while(!pq.empty()){
      int cur = pq.top().ss;
      pq.pop();
      upd(1,1,tam,b[cur],val[cur]);
    }
  pii R = query(1,1,tam,1,tam);
  cout << R.ff<<" "<< mod(R.ss,M) << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
