// cancer NAO FACA 32 MB SE FUDER
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
#define Unique(v) sort(all(v));v.erase(unique(all(v)),v.end());
#define sz(v) (int)v.size()
//#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left sefude
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl; 
#define prl cerr<<"called: "<< __LINE__<<endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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

const int N = 1e6;
int F[N];
int RF[N];
int INI[N],END[N];
int ans;
bitset<N> done,vis;

void dfs(int _v){
  vi st{_v};
  while(sz(st)){
    int v = st.back();vis[v] = 1;
    if(INI[v] == END[v]){
      ans+=done[v];
      if(sz(st)>1 and !done[v]){
        done[st[sz(st) - 2]] = 1;
      }
      st.pop_back();
      continue;
    }
    int to = RF[INI[v]++];
    if(!vis[to])st.pb(to);
  }
}


int32_t main(){
  fastio;
  int n;
  cin>>n;
  for(int i=0;i<n;i++){
    int x;
    cin>>x;
    x--;
    F[i] = x;
    INI[F[i]]++;
  }
  int id = 0;
  for(int i=0;i<n;i++){
    int tmp = id;
    id+=INI[i];
    INI[i] = tmp,END[i] = id;
  }
  for(int i=0;i<n;i++){
    RF[INI[F[i]] ++ ] = i;
  }
  for(int i=0;i<n;i++){
    INI[F[i]]--;
  }
  
  for(int i=0;i<n;i++){
    if(!vis[i]){
      int v = i;
       int x = v,y = F[v];
        while(x!=y){
          x = F[x],y = F[F[y]];
        }
        vi cic = {x};y = F[x];
        while(cic.back()!=x){
          cic.pb(F[cic.back()]);
        }
        for(int t : cic)vis[t] = 1;

        for(int c : cic){
          dfs(c);
        }
        int st = -1;
        for(int i=0;i<sz(cic);i++){
          if(done[cic[i]]){
            st = i;
            rotate(cic.begin(),cic.begin() + st,cic.end());
            break;
          }
        }
       
       int tam=0;
        for(int j = 0;j<sz(cic);j++){
          if(done[cic[j]]){
            ans+=(tam/2);
            tam=0;
          }else tam++;
        }
        ans+=(tam/2);
    }
  }
  cout << ans << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
