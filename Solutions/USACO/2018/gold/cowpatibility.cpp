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
#define td(v) v.begin(),v.end()
#define sz(v) (int)v.size()
//#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left sefude
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl; 
typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
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

typedef int pi;
typedef pair<pi,pi> pii;
typedef pair<pii,int> piii;
typedef pair<pii,pii> piiii;
typedef pair<pii,piii> piiiii;

map<pi,int> mp1;
map<pii,int> mp2;
map<piii,int> mp3;
map<piiii,int> mp4;
map<piiiii,int> mp5;

int32_t main(){
  fastio;
  
  ifstream cin("cowpatibility.in");
  ofstream cout("cowpatibility.out");
  


  int n;
  cin >> n;
  for(int i=0;i<n;i++){
    vi v(5);
    for(int j=0;j<5;j++)cin >> v[j];
    sort(all(v));  
    for(int msk=1;msk<(1<<5);msk++){
      vi cur;
      int cnt=0;
      for(int j=0;j<5;j++)if(msk&(1<<j))cur.pb(v[j]),cnt++;

      if(cnt == 1)mp1[cur[0]]++;
      if(cnt == 2)mp2[pii(cur[0],cur[1])]++;
      if(cnt == 3)mp3[piii(pii(cur[0],cur[1]),cur[2])]++;
      if(cnt == 4)mp4[piiii(pii(cur[0],cur[1]),pii(cur[2],cur[3]))]++;
      if(cnt == 5)mp5[piiiii(pii(cur[0],cur[1]),piii(pii(cur[2],cur[3]),cur[4]))]++;  

    }

  }

  ll tot = 1ll * n*(n-1);
  
  
  for(auto it : mp1)tot-=1ll*it.ss*(it.ss-1);
  for(auto it : mp2)tot+=1ll*it.ss*(it.ss-1);  
  for(auto it : mp3)tot-=1ll*it.ss*(it.ss-1);
  for(auto it : mp4)tot+=1ll*it.ss*(it.ss-1);  
  for(auto it : mp5)tot-=1ll*it.ss*(it.ss-1);

  tot/=2;

  cout << tot << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
