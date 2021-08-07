// submitted on Codeforces - EDU seg part 2
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

const ll inf = 2e9;
int n;
struct node{
  node *l,*r;
  ll pre,tot;
  int L,R;
  ll lazy;
  int borda;
  node(int LL,int RR){
    l = r = NULL;
    pre = tot = 0;
    L = LL,R = RR;
    lazy = -inf;
    borda = 0;
  }
  void flush(){
    if(lazy == - inf)return;
    tot = (R - L + 1)*lazy;
    pre = max(0LL,lazy*(R-L+1));
    borda = lazy;
    int mid = (L+R)/2;
    if(L!=R){
      if(l == NULL) l = new node(L,mid);
      if(r == NULL) r = new node(mid+1,R);
      l->lazy = lazy;
      r->lazy = lazy;
    }
    lazy = -inf;
  }
  ll Tot(node* no){
    return !no ? 0 : no->tot;
  }
  ll Pre(node* no){
    return !no ? 0 : no->pre;
  }
  int Borda(node* no){
    return !no ? 0 : no->borda;
  }
  void upd(int a,int b,int d){
    flush();
    
    if(L > b || R < a)return;
    if(a<=L and R<=b){
      lazy = d;
      flush();
      return;
    }
    int mid = (L+R)/2;
    if(a<=mid){
      if(l == NULL)l = new node(L,mid);
      l->upd(a,b,d);
    }
    if(b > mid){
      if(r == NULL)r = new node(mid+1,R);
      r->upd(a,b,d);
    }
    if(l)l->flush();
    if(r)r->flush();
    pre = max(Pre(l),Tot(l) + Pre(r));
    tot = Tot(l) + Tot(r);
    borda = Borda(l);
  }
  ll query(int h){

    flush();
   
    if(L == R){
      if(tot > h)return L-1;
      return L;
    }
    int mid = (L+R)/2;
    if(l == NULL) l = new node(L,mid);
    if(r == NULL) r = new node(mid+1,R);
    l->flush();
    r->flush();
    if(l->pre>h)return l->query(h);
    return r->query(h - Tot(l));
  }
};
node* tree;


int32_t main(){
  fastio;
  cin >> n;
  char op;
  tree = new node(0,n);
  while(cin >> op and op!='E'){
    if(op == 'Q'){
      int h;
      cin >> h;
      ll res = (tree->pre<=h ? n  : tree->query(h));
      cout << res  << endl;
    }else if(op == 'I'){
      int l,r,d;
      cin >> l >> r >> d;
      tree->upd(l,r,d);
    }
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
