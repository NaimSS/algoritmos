#include <bits/stdc++.h>
#define int long long
#define ld long double
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb(x) push_back(x)
#define mp(a,b) make_pair(a,b)
#define ms(v,x) memset(v,x,sizeof(v))
#define ff first
#define ss second
#define rep(i,l,r) for(int i = (int)l;i<(int)r;i++)
#define td(v) v.begin(),v.end()
#define M   1000000007 // 1e9 + 7
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
inline int mod(int n, int m){ int ret = n%m; if(ret < 0) ret += m; return ret; }
int gcd(int a, int b){return (b == 0 ? a : gcd(b, a%b));}
int exp(int a,int b,int m){
    if(b==0) return 1;
    if(b==1) return mod(a,m);
    int k = mod(exp(a,b/2,m),m);
    if(b&1){
        return mod(a*mod(k*k,m),m);
    }
    else return mod(k*k,m);
}
const int MAXN = 200100;
int fat[MAXN];
int inv[MAXN];

int C(int n,int k){
	if(k>n)return 0;
	return mod(fat[n]*mod(inv[n-k]*inv[k],M),M);
}

int dp[MAXN];
int cmp(pii a,pii b){
	return a.ff + a.ss < b.ff + b.ss;
}


int32_t main(){
	fastio;
    fat[0] = inv[0] = 1;
    for(int i=1;i<MAXN;i++){
		fat[i] = (i*fat[i-1])%M;
		inv[i]  = exp(fat[i],M-2,M);
	}
	int h,w,n;
	cin>>h>>w>>n;
	vector<pii> v;
	for(int i=0;i<n;i++){
		int r,c;
		cin>>r>>c;
		v.pb(pii(r,c));
	}
	v.pb(pii(h,w));
	sort(v.begin(),v.end(),cmp);
	for(int i=0;i<(int)v.size();i++){
		
		dp[i] = C(v[i].ff + v[i].ss - 2, v[i].ff - 1);
		int r = v[i].ff,c = v[i].ss;
		for(int j=0;j<i;j++){
			int r1 = v[j].ff,c1 = v[j].ss;
			if(r1<=r && c1<=c){
				dp[i] = mod(dp[i]  - dp[j]*C(r-r1 + c - c1,r-r1),M);
			}
		}
	}
	cout << dp[(int)v.size() - 1] <<endl;
	
	
}
