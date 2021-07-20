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

vector<vi> v;
struct node{
  ll tot;
  int pos,id;
  node(){}
  node(ll tot,int pos,int id):id(id),tot(tot),pos(pos){}
  bool operator<(const node& o)const{
    return tot > o.tot; // reversed on pq
  }
};

int32_t main(){
  fastio;
    ifstream cin("roboherd.in");
  ofstream cout("roboherd.out");
  int n,k;
  cin >> n >> k;

  ll tot=0;
  for(int i=0;i<n;i++){
    int m;
    cin >> m;
    vi vec;
    vec.resize(m);
    for(int &j : vec)cin>>j;
    sort(all(vec));
    tot+=vec[0];
    if(m == 1){
      continue;
    }  
    for(int j=1;j<m;j++)vec[j]-=vec[0];  
    vec[0] = 0;
    v.pb(vec);
  }

  sort(all(v));


  priority_queue<node> pq;
  pq.push(node(0,0,0));
  ll ans = 0;
  if(sz(v) == 0){
    cout << tot << endl;
    return 0;
  }

  while(!pq.empty()){
    if(k==0)break;
    k--;
    auto cur = pq.top();
    pq.pop();
    ans+=tot+cur.tot;
    if(cur.id == 1 and cur.pos + 1 < sz(v)){
        pq.push(node(cur.tot - v[cur.pos][1] + v[cur.pos][0] +
        v[cur.pos+1][1],cur.pos+1,1));
    }
    if(cur.pos + 1 < sz(v) and cur.id!=0){
      pq.push(node(cur.tot + v[cur.pos+1][1],cur.pos+1,1));
    }
    if(cur.id + 1 < sz(v[cur.pos]) ){
      pq.push(node(cur.tot - v[cur.pos][cur.id] + v[cur.pos][cur.id+1],cur.pos,cur.id+1));
    }
  }
  cout << ans << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
