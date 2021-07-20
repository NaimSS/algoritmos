#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;
#define int long long
const int N = 1e6 + 10;
ll dp[N];
const int M = 1e9 + 7;
int32_t main(){
    
    ifstream cin("spainting.in");
    ofstream cout("spainting.out");
    
    int n,m,k;
    cin >> n >> m >> k;

    //scanf("%d %d %d",&n,&k,&m);
    dp[0] = 1;
    ll acu=1;
    for(int i=1;i<k;i++){
        dp[i] = 1ll*dp[i-1]*m%M;
        if(i<k-1)acu = (acu + dp[i])%M;
    }
    ll tudo =1;
    for(int i=1;i<=n;i++)tudo = (tudo * m)%M;


    for(int i=k;i<=n;i++){
        acu-=dp[i-k];
        acu+=dp[i-1];
        acu = (acu%M);
        if(acu<0)acu+=M;
        
        dp[i] = acu * (m-1) %M;

    }
    if(k == 1){
        dp[n] = 0;
    }
    ll res = tudo - dp[n];
    res%=M;
    if(res<0)res+=M;

    cout << res << endl;
    //printf("%lld\n",res);

}
