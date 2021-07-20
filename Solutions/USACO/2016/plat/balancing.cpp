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
#define sz(v) ((int)v.size())
//#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left sefude
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl; 
#define prl cerr<<"called: "<< __LINE__ << endl;
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


struct SuperSeg{
  vi tot;
  // vi pre,suf;
  int n;
  SuperSeg(){}
  SuperSeg(int N){
    n = N;
    //pre = suf = 
    tot = vi(4*n+10,0);
  }
  void upd(int no,int i,int j,int p,int v){
    if(i==j){
      tot[no]+=v;
      //pre[no] = max(tot[no],0);
      //suf[no] = max(tot[no],0);
      return;
    }
    int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
    if(p<=mid)upd(l,i,mid,p,v);
    else upd(r,mid+1,j,p,v);
    tot[no] = tot[l] + tot[r];
  }

  int findB(int no,int i,int j,int x){
    if(i==j){
      if(tot[no] > x)return i-1;
      return i;
    }
    int mid =(i+j)>>1,l=no<<1,r=no<<1|1;
    if(tot[l] <= x)return findB(r,mid+1,j,x - tot[l]);
    return findB(l,i,mid,x);
  }
  int findS(int no,int i,int j,int x){
    if(i == j){
      return i;
    }
    int mid =(i+j)>>1,l=no<<1,r=no<<1|1;
    if(tot[l]>=x)return findS(l,i,mid,x);
    return findS(r,mid+1,j,x - tot[l]);
  }

  int findR(int x){
    return findB(1,1,n,x);// maior com <=x
  }
  int findL(int x){
    return findS(1,1,n,tot[1] - x);//menor tal que o resto tem <=x
  }
  pii get(int x){
    return pii(findL(x),findR(x));
  }

};

int n;
const int N = 1e6 + 1;
int32_t main(){
  fastio;
  ifstream cin("balancing.in");
  ofstream cout("balancing.out");
  
 // auto z = clock();
  cin >> n;
  vector<pii> vec;
  
  vi comp;
  for(int i=1;i<=n;i++){
    int a,b;
    cin>>a>>b;
    vec.pb(pii(a,b));
    comp.pb(b);
  }
  Unique(comp);
  for(auto& it : vec){
    it.ss = lower_bound(all(comp),it.ss) - comp.begin() + 1;
  }
  int tam = sz(comp);
  SuperSeg S1(tam),S2(tam);

  for(auto&it : vec){
    S2.upd(1,1,tam,it.ss,1);
  }

  sort(all(vec));
  int res = n;
  int ptr=0;
  for(int x = 0;x<=N;x+=2){
    bool some = 0;
    while(ptr<sz(vec) and vec[ptr].ff<=x){
      // move to the other side:
      S2.upd(1,1,tam,vec[ptr].ss,-1);
      S1.upd(1,1,tam,vec[ptr].ss,1);
      ptr++;
      some = 1;
    }
    if(!some)continue;

    int l = 1,r = n;
    while(l<=r){
      int mid = (l+r)/2;

      pii s1 = S1.get(mid);
      pii s2 = S2.get(mid);
      if(max(s1.ff,s2.ff) > min(s1.ss,s2.ss)){
        // bad... impossible
        l = mid + 1;
      }else{
        if(res > mid)res= mid;
        r = mid - 1;
      }
    } 

  }
  cout << res << endl;
//  cerr << "time: "<<(double)(clock() - z)/CLOCKS_PER_SEC<<" ms\n";
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
