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
     
    const int N = 500100;
    vi g[N];
    int S[N];
    int p[N];
    int cnt[N];
    int f(int x){return p[x] = (p[x]==x?x:f(p[x]));}
    void join(int a,int b){
    	p[f(a)]=f(b);
    }
     
    pii e[N];
     
    void dfs(int v,int p,map<int,int>&mp){
    	if(cnt[S[v]]!=1)
    		mp[S[v]] = 1;
    	for(auto to : g[v])if(to!=p){
    		map<int,int> nv;
    		dfs(to,v,nv);
    		if(sz(nv) > sz(mp))mp.swap(nv);
     
    		for(auto it : nv){
    			mp[it.ff]+=it.ss;
    			if(mp[it.ff] == cnt[it.ff]){
    				// todo mundo na subarvore. Cor n importa mais
    				mp.erase(it.ff);
    			}
    		}
    	}
    	if(mp.size()!=0 && p!=-1){
    		// alguem não ta dentro.
    		// pode juntar com o pai
    		join(v,p);
    	}
    }
    int deg[N];
    int32_t main(){
        fastio;
    	int n,k;
    	cin >> n >> k;
    	rep(i,0,n-1){
    		int a,b;
    		cin >> a >> b;
    		g[a].pb(b);
    		g[b].pb(a);
    		e[i] = pii(a,b);
    	}
    	rep(i,1,n+1)p[i]=i;
    	rep(i,1,n+1)cin >> S[i],cnt[S[i]]++;
    	map<int,int> mp;
    	dfs(1,0,mp);
    	rep(i,0,n-1){
    		if(f(e[i].ff)!=f(e[i].ss)){
    			deg[f(e[i].ff)]++;
    			deg[f(e[i].ss)]++;
    		}
    	}
    	int res=0;
    	set<int> used;
    	rep(i,1,n+1)used.insert(f(i));
     
    	for(int i : used)
    		if(deg[i]<=1)res++;
    	
    	if(res<=1)res=0;
    	cout << (res + 1)/2 << endl;
     
     
        // math -> gcd it all
        // Did u check N=1? Did you switch N,M?
    }
