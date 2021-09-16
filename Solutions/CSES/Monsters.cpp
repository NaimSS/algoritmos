#include <bits/stdc++.h>
#define int long long
#define double long double
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb(x) push_back(x)
#define mp(a,b) make_pair(a,b)
#define ms(v,x) memset(v,x,sizeof(v))
#define ff first
#define ss second
#define frr(i,n) for(int i=0;i<n;i++)
#define td(v) v.begin(),v.end()
#define M   1000000007 // 1e9 + 7
#define MAXN 100100
using namespace std;
 
typedef pair<int,int> pii;
typedef pair<int,double> pdd;
inline int mod(int n, int m){int ret = n%m; if(ret < 0) ret += m; return ret;}
int gcd(int a, int b){return (b == 0 ? a : gcd(b, a%b));}
int exp(int a,int b,int m){
    if(b==0) return 1;
    if(b==1) return mod(a,m);
    int k = mod(exp(a,b/2,m),m);
    if(b&1){
        return mod(a*mod(k*k,m),m);
    }    else return mod(k*k,m);
}
 
int n,m;
char g[1010][1010];
pii pai[1010][1010];
int dist[1010][1010];
int d2[1010][1010];
int vis[1010][1010];
int ok(int l,int c){
	return (l>=1 && l<=n && c>=1 && c<=m && g[l][c]!='M' && g[l][c]!='#' && !vis[l][c]);
}
 
 
int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};
 
void BFS(){
	queue<pii> fM;
	queue<pii> fA;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			dist[i][j] = 10000000;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(g[i][j]=='M'){
			fM.push(pii(i,j));
			vis[i][j] = true;
			dist[i][j] = 0;
			}
			if(g[i][j]=='A'){
			fA.push(pii(i,j));
			pai[i][j] = pii(-1,-1);
			}
		}
	}
	
	while(!fM.empty()){
       int l = fM.front().ff;
       int c = fM.front().ss;
       fM.pop();
		for(int i=0;i<4;i++){
			int ll = l+dx[i];
			int cc = c+dy[i];
			if(ok(ll,cc)){
				vis[ll][cc] = true;
				dist[ll][cc] = dist[l][c]+1;
				fM.push(pii(ll,cc));
			}
		}	  		
		
	}
	memset(vis,false,sizeof(vis));
	int rl=-1,rc=-1;
	vis[fA.front().ff][fA.front().ss]=true;
	while(!fA.empty()){
		int l = fA.front().ff;
		int c = fA.front().ss;
		fA.pop();
		if(l==n || l==1 || c==m || c==1){
			rl =l;
			rc =c;
			break;
		}
		for(int i=0;i<4;i++){
			int ll = l+dx[i];
			int cc = c+dy[i];
			if(ok(ll,cc) && d2[l][c]+1<dist[ll][cc]){
			//	cout<<ll<<" "<<cc<<" "<<d2[ll][cc]<<" "<<dist[ll][cc]<<endl;
				vis[ll][cc] = true;
				d2[ll][cc] = d2[l][c]+1;
				pai[ll][cc] = pii(l,c);
				fA.push(pii(ll,cc));
			//	cout<<l<<" "<<c<<" -> "<<ll<<" "<<cc<<endl;
			}
		}
	}
	if(rl!=-1){
		cout<<"YES"<<endl;
		vector<pii> res;
		while(rl!=-1 && rc!=-1){
		//		cout<<rl<<" "<<rc<<" <- "<<pai[rl][rc].ff<<" "<<pai[rl][rc].ss<<endl;
			res.pb(pii(rl,rc));
			pii nex = pai[rl][rc];
			rl = nex.ff;
			rc = nex.ss;
		
		}
		reverse(res.begin(),res.end());
		vector<char> ans;
		for(int i=0;i<(int)res.size() - 1;i++){
			int dl = res[i+1].ff - res[i].ff;
			int dc = res[i+1].ss - res[i].ss;
			if(dl==0){
				if(dc==1){
					ans.pb('R');
				}else ans.pb('L');
			}else{
				if(dl==1){
					ans.pb('D');
				}else ans.pb('U');
			}
		}
		cout<<ans.size()<<endl;
		for(int i=0;i<(int)ans.size();i++){
			cout<<ans[i];
		}
		cout<<endl;
	}else{
		cout<<"NO"<<endl;
	}
	
}
 
 
 
int32_t main(){
	fastio;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>g[i][j];
		}
	}
	BFS();
	
}
