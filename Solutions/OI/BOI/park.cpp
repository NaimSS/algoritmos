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
#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left sefude
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
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


struct query{
  int r,e,id;
  query(){}
  query(int r,int e,int id):r(r),e(e),id(id){}
  bool operator<(const query& o)const{
    return tie(r,e,id) < tie(o.r,o.e,o.id);
  }
};
const int N = 2020;

struct DSU{
  vi p , ps;
  DSU(int n){
    p = vi(n+1),ps = vi(n+1,1);
    rep(i,0,n+1) p[i] = i;
  }
  int find(int x){return p[x]==x?x:p[x]=find(p[x]);}
  bool join(int x , int y){
    x = find(x) , y = find(y);
    if(x == y) return 0;
    if(ps[x] > ps[y]) swap(x,y);
    p[x] = y, ps[y] += ps[x];
    return 1;
  }
};  


ll sq(ll x){return x*x;}

pii Par[5];
string res[100100];
int x[N],y[N],r[N];
int32_t main(){
  fastio;
  int n,m;
  cin >> n >> m;
  DSU dsu(n + 10);
  int w,h;
  cin >> w >> h;
  Par[1] = pii(0,1);
  Par[2] = pii(w,0);
  Par[3] = pii(h,1);
  Par[4] = pii(0,0);
  for(int i=1;i<=n;i++){
    cin >> x[i] >> y[i] >> r[i];
  }


  vector<query> qry;
  for(int i=0;i<m;i++){
    int r,e;
    cin >> r >> e;
   qry.pb(query(r,e,i));
  }
  
  vector<query> circ,parede;
  
  for(int i=1;i<=n;i++){

    for(int j=i + 1;j<=n;j++){
      ll L = 0 , R = 1e9;
      ll ans = 0;
      while(L<=R){
        ll mid = (L+R)/2;
        if(sq(r[i] + r[j] + mid*2) > sq(x[i] - x[j]) + sq(y[i]-y[j])){
          ans = mid;
          R = mid-1;
        }else L = mid + 1;

      }
      assert(sq(r[i] + r[j] + 2*ans) > sq(x[i] - x[j]) + sq(y[i] - y[j]));
      assert(sq(r[i] + r[j] + 2*ans - 2) <= sq(x[i] - x[j]) + sq(y[i] - y[j]));
      // please dont TL..
      circ.pb(query(ans,i,j));
    }
    
    for(int lado=1;lado<=4;lado++){
      if(Par[lado].ss == 0){
        // X
        int falta = (abs(Par[lado].ff - x[i])-r[i])/2 + 1;
        
        //if(abs(Par[lado].ff - x[i]) == r[i] + 2 * falta)falta++;
        assert(abs(Par[lado].ff - x[i]) - r[i] - falta*2<0);
        assert(abs(Par[lado].ff - x[i]) - r[i] - falta*2 + 2>=0);
        parede.pb(query(falta,i,n + lado));
      }else{
        // Y
        int falta = (abs(Par[lado].ff - y[i]) - r[i])/2 + 1; 
        // if(abs(Par[lado].ff - y[i]) == r[i] + 2 * falta)falta++;
        assert(abs(Par[lado].ff - y[i]) - r[i] - falta*2 <0);
        assert(abs(Par[lado].ff - y[i]) - r[i] - falta*2 + 2 >=0);
        parede.pb(query(falta,i,n + lado));
      }
    }

  }
  sort(all(circ));sort(all(parede));sort(all(qry));
  int it = 0;
  int itP=0;
  int last = -1e9;
  for(auto pessoa : qry){
    
    assert(pessoa.r>=last);last = pessoa.r;

    while(it < sz(circ) and circ[it].r <= pessoa.r){
      dsu.join(circ[it].e,circ[it].id);
      it++;
    }
    while(itP < sz(parede) and parede[itP].r<=pessoa.r){
      dsu.join(parede[itP].e,parede[itP].id); 
      itP++;
    }
    
    int e = pessoa.e;
    string good = "";
    for(int c=1;c<=4;c++){
      if(c==e){
        good+=char('0' + c);
        continue;
      }
      // check if vertical blocks:
      int A = min(e,c),B = max(e,c);
      int op1 = (A == 1 and B == 4);
      int op2 = (A == 2 and B == 3);
      if(!op1 and !op2){

        if(dsu.find(n + 1) == dsu.find(n + 3))continue;
      }

      op1 = (A==1 and B==2);
      op2 = (A==3 and B==4);

      // check if horizontal blocks:
      if(!op1 and !op2){
        if(dsu.find(n+2)==dsu.find(n+4))continue;
      }

      int prv = n + (c == 1 ? 4 : c - 1);
      if(dsu.find(n + c) == dsu.find(prv))continue;
      prv = n + (e == 1 ? 4 : e - 1);
      if(dsu.find(n + e) == dsu.find(prv))continue;
      good+=char('0' + c);
    }
    sort(all(good));
    res[pessoa.id] = good;
  }
  for(int i=0;i<m;i++)cout << res[i] << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
