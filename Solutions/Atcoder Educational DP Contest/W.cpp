#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb(x) push_back(x)
#define mp(a,b) make_pair(a,b)
#define ms(v,x) memset(v,x,sizeof(v))
#define ff first
#define ss second
#define frr(i,n) for(int i=0;i<n;i++)
#define td(v) v.begin(),v.end()
#define MAXN 200100
typedef long long ll;
using namespace std;
typedef pair<int,int> pii;
typedef pair<pii,int> piii;
inline ll mod(ll n, ll m){ll ret = n%m; if(ret < 0) ret += m; return ret;}
int gcd(int a, int b){return (b == 0 ? a : gcd(b, a%b));}
ll exp(ll a,ll b,ll m){
    if(b==0) return 1;
    if(b==1) return mod(a,m);
    ll k = mod(exp(a,b/2,m),m);
    if(b&1){
        return mod(a*mod(k*k,m),m);
    }    else return mod(k*k,m);
}

struct seg{
 int l,r,v;	
};
seg v[MAXN];

struct LazySeg{
vector<int> tree;
vector<int> lazy;
int n;

void build(int no,int i,int j){
	lazy[no] = 0;
	if(i==j){
		tree[no] = 0;
		if(i==0)tree[no] = 0;
	}else{
		int m = (i+j)/2;
		int l = 2*no,r=2*no+1;
		build(l,i,m);
		build(r,m+1,j);
		tree[no] = max(tree[l],tree[r]);
	}
}

void propagate(int no,int i,int j){
	if(lazy[no]==0)return;
	tree[no]+=lazy[no];
	if(i!=j){
		lazy[2*no]+=lazy[no];
		lazy[2*no+1]+=lazy[no];
	}
	lazy[no] = 0;
}

void update(int no,int i,int j,int a,int b,int v){
	propagate(no,i,j);
	if(i>b || j<a || i>j)return;
	if(a<=i && j<=b){
		tree[no] += v;
		if(i!=j){
			lazy[2*no]+=v;
			lazy[2*no+1]+=v;
		}
		return;
	}
	int m = (i+j)/2;
	int l = 2*no,r=2*no+1;
	update(l,i,m,a,b,v);
	update(r,m+1,j,a,b,v);	
	tree[no] = max(tree[l],tree[r]);
}

int query(int no,int i,int j,int a,int b){
	if(i>b || j<a || i>j)return -1e18;
	
	propagate(no,i,j);
	
	if(a<=i && j<=b)return tree[no];
	
	int m = (i+j)/2;
	int l = 2*no,r=2*no+1;
	
	return max(query(l,i,m,a,b),query(r,m+1,j,a,b));
}

void init(int c){
	n = c;
	tree.resize(4*(n+1));
	lazy.resize(4*(n+1));
	build(1,0,n);
}
	
};

int A[MAXN];


struct event{
 int x,id,type;
 event(){}
 event(int a,int b,int c){
	 x = a;
	 id = b;
	 type = c;
 }	
 bool operator<(const event &o) const{
	return x < o.x;
 }
};
int dp[MAXN];
int32_t main(){
    fastio;
    int n,m;
    cin>>n>>m;
    
    vector<event> ev;
    for(int i=1;i<=m;i++){
		cin>>v[i].l>>v[i].r>>v[i].v;
		v[i].r++;
		// ^confere?
		ev.pb(event(v[i].l,i,0));
		ev.pb(event(v[i].r,i,1));
	}
    sort(td(ev));

    int cur=0;
    dp[0] = 0;
    LazySeg L;
    L.init(n);
    for(int i=1;i<=n;i++){
		while(cur<2*m && i==ev[cur].x){
			
			if(ev[cur].type==0){
				L.update(1,0,n,0, i - 1, v[ev[cur].id].v);
			}else{
				L.update(1,0,n,0,v[ev[cur].id].l - 1, -v[ev[cur].id].v);
			}
			cur++;
		}
		dp[i] = L.query(1,0,n,0,i-1);
		
		L.update(1,0,n,i,i,dp[i]);
	}
	 int r=0;
	 for(int i=1;i<=n;i++){
		 r= max(r,dp[i]);
	 }
	 cout<<r<<endl;
    
    
	// Math -> gcd it all
	//did you check N=1? Did you mix up N,M?
}
