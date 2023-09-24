#include <bits/stdc++.h>
#include <iostream>
// #define int long long
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
#define Unique(v) sort(all(v)),v.erase(unique(all(v)),v.end());
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
// std::mt19937_64 rng64((int) std::chrono::steady_clock::now().time_since_epoch().count());
std::mt19937 rng(
  
//  (int) std::chrono::steady_clock::now().time_since_epoch().count()
   1239010
);
ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down
//inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b,ll e,ll m){
    b%=m;
    ll ans = 1;
    for (; e; b = b * b % m, e /= 2)
        if (e & 1) ans = ans * b % m;
    return ans;
}
// debug:
template<class T>void print_vector(vector<T> &v){
    rep(i,0,sz(v))cout<<v[i]<<" \n"[i==sz(v)-1];
}
void dbg_out() {cerr << endl; }
template<typename Head, typename ... Tail> void dbg_out(Head H,Tail... T){
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__), cerr << endl
#else
#define dbg(...) 42
#endif
//
typedef __int128_t u128;

u128 exp(u128 x,int n){
    if(n == 0)return 1;
    if(n==1)return x;
    u128 r = exp(x,n/2);
    if(n&1)return r*r*x;
    return r*r;
}

int ok(u128 p,u128 sum,u128 m,int n){
    u128 cima = m * p;
    u128 baixo = exp(sum,n) - exp(sum - p,n);
    if(cima%baixo == 0)return 1;
    return 0;
}

int32_t main(){
    fastio;
    ll n,m;
    cin >> n >> m;
    double lim = pow(m,1.0/(n-1)) + 2;
    vector<double> pwr;
    for(int i=0;i <= 1;i++)pwr.pb(pow(i,n));

    for(int sum = 2;sum <= lim;sum++){
        pwr.pb(pow(sum,n));
        for(ll p=1;p<sum;p++){
            // f = p/(p+q)
            ll q = sum - p;
            double val = log(m) + log(p) - n * (log(sum) - log(q));

            if( val >= -1e3){
                if(ok(p,sum,m,n)){
                    cout << p << " " << sum << endl;
                    return 0;
                }
                
            }else continue;
        }
    }
    cout << "impossible\n";
    
    // math -> gcd it all
    // Did you swap N,M? N=1?
}
