// Solution to BOI19 - Olympiads


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
//#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define td(v) v.begin(),v.end()
#define sz(v) (int)v.size()
//#define M   1000000007 // 1e9 + 7
#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left sefude
typedef long long ll;
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


const int N = 505;
vector<int> a[N];
int inside[N];

int n,k,c;
int cost(vi v){
  vi best(k,0);
  for(int x : v){
    for(int i=0;i<k;i++){
      best[i] = max(best[i],a[x][i]);
    }
  }
  int ans=0;
  for(int i=0;i<k;i++)ans+=best[i];
  return ans;
}

struct dado{
  vi v;
  dado(){}
  dado(vi a){
    v = a;
  }
  bool operator<(const dado& b) const{
    return cost(v) < cost(b.v); // reversed in queue
  }
};
priority_queue<dado> pq;
set<vi> vis;
vi g[N];
#define DB 0
int32_t main(){
  fastio;
  cin>>n>>k>>c;
  for(int i=1;i<=n;i++){
    a[i].resize(k);
    for(int j=0;j<k;j++)cin >> a[i][j];
  }
  vi opt;
  for(int it=0;it<k;it++){
    vector<pii> v;
    for(int i=1;i<=n;i++){
      v.pb(pii(a[i][it],i));
    }
    sort(all(v),greater<pii>());
    opt.pb(v[0].ss);

    for(int i=1;i<=n;i++){
      g[i].pb(v[0].ss);
    }
    for(int i=1;i<n;i++){
      g[v[i-1].ss].pb(v[i].ss);
    }

  }
  sort(all(opt));
  opt.erase(unique(all(opt)),opt.end());
  for(int i=1;i<=n;i++){
    if(opt.size() == k)break;
    if(find(all(opt),i)==opt.end())opt.pb(i);
  }
  sort(all(opt));
  pq.push(opt);
  vis.insert(opt);

  for(int iteration=0;iteration<c-1;iteration++){
    assert(!pq.empty());
    auto cur = pq.top().v;
    
    if(DB){
    for(int x : cur)cout<<x<<" ";
      cout << endl;
    }
    pq.pop();
    for(int j=0;j<k;j++){
      for(auto col : g[cur[j]]){
        auto nxt = cur;
        nxt[j] = col;
        int ok = 1;
        sort(all(nxt));
        for(int it=1;it<sz(nxt);it++){
          if(nxt[it]==nxt[it-1])ok=0;
        }
        if(ok and vis.find(nxt)==vis.end()){
          pq.push(nxt);
          if(DB){
            cout<<"poe: ";
            for(int x : nxt)cout<<x<<" ";
              cout << endl;
          }
          vis.insert(nxt);
        }

      }
    }

  }

  cout << cost(pq.top().v) << endl;
  // Math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
