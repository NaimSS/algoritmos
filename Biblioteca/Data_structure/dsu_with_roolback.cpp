// https://codeforces.com/contest/813/problem/F
// https://codeforces.com/contest/1444/problem/C
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
//#define sz(v) (int)v.size()
//#define int long long
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


struct event{
  int a,b,sz;
  int pai;
  int ca;
  int good;
  event(){}
  event(int a,int b,int sz,int pai,int ca,int good):a(a),
  b(b),sz(sz),pai(pai),ca(ca),good(good){}
};

struct dsu_roolback{
  vi pai,sz;
  vi cor;// for this problem
  int good = 1;
  dsu_roolback(){}
  dsu_roolback(int _n){
    int n = _n + 100;
    pai.resize(n);
    sz.resize(n);
    cor.resize(n);
    rep(i,0,n){
      pai[i] = i;
      sz[i] = 1;
      cor[i] = 0;
    }
  }

  int F(int x){// no path-compression allowed
    while(x!=pai[x])x=pai[x];
    return x;
  }
  int Cor(int x){
    int c=0;
    while(x!=pai[x])c^=cor[x],x=pai[x];
    return c;
  }

  stack<event> Rool;

  void foto(int a,int b){
    Rool.push(event(a,b,sz[a],pai[a],cor[a],good));
  }

  void join(int a,int b){
    if(sz[F(a)] > sz[F(b)])swap(a,b);
    int ca = Cor(a),cb = Cor(b);
    a = F(a),b = F(b);
    foto(a,b);
    
    if(a!=b){
      sz[b]+=sz[a];
      pai[a] = b;
      cor[a] = (ca^cb^1);
    }
    else{

      if(ca == cb)good = 0;

    }

  }
  void roolback(int t){
    while((int)Rool.size() > t){
      event ev = Rool.top();Rool.pop();
      if(ev.a!=ev.b){
        sz[ev.b]-=ev.sz;

        pai[ev.a] = ev.pai;
        cor[ev.a] = ev.ca;
      }
      good = ev.good;
    }
  }

};

const int N = 100100;
template <class T>
struct dcq{
  vector<vector<T>> st; int n;
  vi ans;
  dsu_roolback Dsu;
  dcq(int n ) : n(n){
    st.resize(2*n,vector<T>());
    ans.resize(n,0);
    Dsu = dsu_roolback(N);

  }
  void upd(int x , int y , T q){ //evento Q em [X,Y] (eventos 0 index)
    for(x += n, y += n+1; x < y ; x/=2 , y/=2){
      if(x&1) st[x++].push_back(q);
      if(y&1) st[--y].push_back(q);
    }
    return;
  }


  void solve(int curr = 1){
    int t = Dsu.Rool.size();
    allin(w, st[curr]){
      // adiciona as coisas

      Dsu.join(w.ff,w.ss);

    }
    if(curr >= n){
      // responde em ans[curr -n]
      ans[curr - n] = Dsu.good;
    }
    else{
      solve(2*curr) ; solve(2*curr+1);
    }
    // da roll back
    Dsu.roolback(t);
    return ;
  } 
};



int32_t main(){
  //fastio;
  int n,q;
  scanf("%d %d",&n,&q);
  dcq<pii> dynacon(q);

  map<pii,int> mp;
  for(int i=0;i<q;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    if(mp.count(pii(a,b))){

      dynacon.upd(mp[pii(a,b)],i-1,pii(a,b));

      mp.erase(pii(a,b));
    }else{
      mp[pii(a,b)] = i;
    }
  }

  for(auto it : mp){
    dynacon.upd(it.ss,q-1,pii(it.ff.ff,it.ff.ss));
  }

  dynacon.solve();
  for(int i=0;i<q;i++){
    printf((dynacon.ans[i] ? "YES\n" : "NO\n"));
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
