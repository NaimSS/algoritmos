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
    using namespace std;
    typedef vector<int> vi;
    #define y1 abacaba
    //#define left oooooopss
    #define db(x) cerr << #x <<" == "<<x << endl;
    #define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
    #define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl;
    typedef long long ll;
    typedef pair<int,int> pii;
    typedef pair<ll,ll> pll;
    typedef vector<ll> vl;
    std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
    ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
    ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down
    inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
    ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
    ll exp(ll b,ll e,ll m){
      b%=m;
      ll ans = 1;
      for (; e; b = b * b % m, e /= 2)
          if (e & 1) ans = ans * b % m;
      return ans;
    }
      
    // debug:
    void dbg_out() { cerr << endl; }
    template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T){ 
      cerr << ' ' << H; 
      dbg_out(T...); 
    }
    #ifdef LOCAL
    #define dbg(...) cerr<<"(" << #__VA_ARGS__<<"):" , dbg_out(__VA_ARGS__) , cerr << endl
    #else
    #define dbg(...) 42
    #endif
    //
     
    const int N = 200100;
    pll a[N];// (V,C)
    int pos[N];
    struct node{
      node *l,*r;
      ll sum;
      int qtd=0;
      node(ll v = 0,int q=0){
        l = r = NULL;
        sum = v;
    	qtd = q;
      }
    };
    typedef node* pnode;
    pnode version[N];
     
     
    void build(pnode no,int i,int j){
      if(i == j){
        return;
      }
      int mid = (i+j)/2;
      no->l = new node();
      no->r = new node();
      build(no->l,i,mid);
      build(no->r,mid+1,j);
    }
     
    void upd(pnode no,pnode old,int i,int j,int p,ll v){
     
      if(i == j){
        no->sum = old->sum + v;
    	no->qtd = old->qtd + 1;
        return;
      }
      int mid = (i+j)/2;
      if(p<=mid){
        no->r = old->r;
        if(no->l == NULL)no->l = new node();
        upd(no->l,old->l,i,mid,p,v);
      }else{
        no->l = old->l;
        if(no->r == NULL)no->r = new node();
        upd(no->r,old->r,mid+1,j,p,v);
      }
      no->sum = no->l->sum + no->r->sum;
      no->qtd = no->l->qtd + no->r->qtd;
    }
    ll rev[N];
    pll query(pnode no,pnode old,int i,int j,int k){
      if(i>j || k<=0 || no==NULL || old==NULL)return pll(0,0);
      if(i==j){
    	  int put = min(no->qtd-old->qtd,k); 
    	  if(put ==0)return pll(0,0);
    	  return pll(rev[i] * put,put);
      }
      if(no->qtd - old->qtd <= k){
    	  return pll(no->sum - old->sum,no->qtd - old->qtd);
      }
      int m = (i+j)/2;
      auto a = query(no->r,old->r,m+1,j,k);
      k-=a.ss;
      auto b = query(no->l,old->l,i,m,k);
      k-=b.ss;
      return pll(a.ff + b.ff,a.ss + b.ss);
    }
    int T;
    ll res = -1e18;
    	int n,M;
     
    void solve(int l,int r,int optl,int optr){
    	if(l > r)return;
    	int m = (l+r)/2;
    	int optm=-1;
    	ll mx = -1e18;
    	for(int i = optl;i<=optr;i++){
    		if(m-i+1 < M)continue;
    		ll p1=-2ll * (a[m].ss - a[i].ss),p2 = a[m].ff + a[i].ff + query(version[m-1],version[i],1,T,M-2).ff;
    		ll cur = p1+p2;
    		if(cur > mx){
    			mx = cur;
    			optm = i;
    		}
    	}
    	res=max(res,mx);
    	if(optm==-1){
    		solve(m+1,r,optl,optr);
    	}
    	else{
    		solve(l,m-1,optl,optm);
    		solve(m+1,r,optm,optr);
    	}
    }
     
    int32_t main(){
        fastio;
    	cin >> n >> M;
    	vi vals;
    	rep(i,1,n+1){
    		cin >> a[i].ff >> a[i].ss;
    		vals.pb(a[i].ff);
    	}
    	Unique(vals);
    	sort(a+1,a+1+n,[&](pll A,pll B){
    		return A.ss < B.ss;
    	});
     
    	T = sz(vals);
    	rep(i,1,n+1){
    		pos[i] = lower_bound(all(vals),a[i].ff) - vals.begin() + 1;
    		rev[pos[i]] = a[i].ff;
    	}
    	version[0] = new node();
    	build(version[0],1,T);
    	for(int i=1;i<=n;i++){
    		version[i] = new node();
    		upd(version[i],version[i-1],1,T,pos[i],a[i].ff);
    	}
     
    	solve(1,n,1,n);
    	cout << res << endl;
     
     
        // math -> gcd it all
        // Did u check N=1? Did you switch N,M?
    }
