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
#define MAXN 100100
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

int dp[MAXN];
int pai[MAXN];
vector<int> adj[MAXN];
int M ;
int solve(int v,int p=-1){
	if(dp[v]!=-1)return dp[v];
	
	if(adj[v].size()==1 && p!=-1)return dp[v] = 2;
	
	int op1 = 1;
	int op2 = 1;
	for(int i=0;i<adj[v].size();i++){
		int to = adj[v][i];
		if(to==p)continue;
		pai[to] = v; 
		op2 = (op2*solve(to,v))%M;
	}
	return dp[v] = (op1 + op2)%M;
}

int ans[MAXN];
int phi;
int passou[MAXN];
int pre[MAXN],suf[MAXN];

void dfs(int v,int p=-1){
	if(v==1){
		ans[v] = mod(dp[v] - 1,M);
			pre[0] = 1;
		suf[adj[v].size()] = 1;
		for(int i=0;i<adj[v].size();i++){
			int to = adj[v][i];
			if(to==p)continue;
			pre[i+1] = (pre[i]*dp[to])%M;  	
		}
		for(int i=(int)adj[v].size() - 1;i>=0;i--){
			int to = adj[v][i];
			if(to==p)continue;
			suf[i] = (suf[i+1]*dp[to])%M;
		}
		
		for(int i=0;i<adj[v].size();i++){
			int to = adj[v][i];
			if(to==p)continue;
			passou[to] = (pre[i]*suf[i+1])%M;
		}
	}else{
		int r = mod(passou[v]+1,M);
		
		ans[v] = r;
		pre[0] = 1;
		suf[adj[v].size()] = 1;
		for(int i=0;i<adj[v].size();i++){
			int to = adj[v][i];
			pre[i+1] = pre[i]; 
			if(to==p)continue;
			ans[v] = mod(ans[v]*dp[to],M);
			pre[i+1] = (pre[i]*dp[to])%M;  	
		}
		for(int i=(int)adj[v].size() - 1;i>=0;i--){
			int to = adj[v][i];
			suf[i] = suf[i+1];
			if(to==p)continue;
			suf[i] = (suf[i+1]*dp[to])%M;
		}
		
		for(int i=0;i<adj[v].size();i++){
			int to = adj[v][i];
			if(to==p)continue;
			passou[to] = (pre[i]*suf[i+1])%M;
			passou[to] = (passou[to]*r)%M; 	
		}
		
	}
	for(int i=0;i<(int)adj[v].size();i++){
		int to = adj[v][i];
		if(to==p)continue;
		dfs(to,v);
	}
}


int32_t main(){
	fastio;
	int n;
	cin>>n>>M;
	memset(dp,-1,sizeof(dp));
	
	for(int i=0;i<n-1;i++){
		int a,b;
		cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	
	solve(1);
	
	dfs(1);
	
	for(int i=1;i<=n;i++)cout<<mod(ans[i],M)<<endl;
	
	// Math -> gcd it all
	//did you check N=1? Did you mix up N,M?
}
