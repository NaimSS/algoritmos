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
#define MAXN 300100
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

struct cx{
    int w,r,v;
    void read(){
        cin >> w >> r >> v;
    }
    bool operator<(const cx& b)const{
        return (w + r < b.w + b.r);
    }
};

int32_t main(){
    int n;
    fastio;
    cin >> n;
    vector<cx> v(n);
    for(int i=0;i<n;i++){
        v[i].read();        
    }
    sort(td(v));
    int maxr = 1e4 * 3;
    vector<int> dp(maxr);
    for(int i=0;i<n;i++){
        for(int j=min(v[i].r,maxr - v[i].w);j>=0;j--){
            dp[j+v[i].w] = max(dp[j+v[i].w],dp[j] + v[i].v);
        }
    }
    cout << *max_element(td(dp)) << endl;
    

	// Math -> gcd it all
	//did you check N=1? Did you mix up N,M?
}
