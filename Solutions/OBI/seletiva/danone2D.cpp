// 100% no neps. O(Nlog^3(maxcord))
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
#define right sefudermano
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


const int N = 2e5 + 10;


struct ST{
  vector<multiset<int>> st; int n; 

  ST(int n) : st(2*n) , n(n) {}
  void upd(int pos, int val,bool add){ // pos 0index
    if(add)st[pos+=n].insert(val);
    else pos+=n,st[pos].erase(st[pos].find(val));
    for(; pos >>=1;){
      if(add)st[pos].insert(val);
      else st[pos].erase(st[pos].find(val));
    }
  }
  bool query(int x , int y,int Y,int DX){ // [x,y] , x, y -0index
  
   for(x += n, y += n+1 ; x < y ; x>>=1 , y>>=1){
    
      if(x&1){
        multiset<int>::iterator it = st[x].lower_bound(Y - DX);
        if(it!=st[x].end() and *it<=Y+DX)return true;
        x++;
     }
      
      if(y&1){
        --y;
        multiset<int>::iterator it = st[y].lower_bound(Y - DX);
        if(it!=st[y].end() and *it<=Y+DX)return true;
      }
    }
    return false;
  }
};


struct BIT{
 int n;
 int MAX;
 vector<ll> bit;
 vector<int> qtd;
 BIT(){}
 BIT(int _n){
   n = _n;
   MAX = n +2;
   bit.resize(n+10,0);
    qtd.resize(n+10,0); 
  }
 
 ll query(int x){
   ll r=0;
   while(x>0){
     r+=bit[x];
     x-=(x&-x);
   }
   return r;
 }
 ll query_qtd(int x){
  int r=0;
  while(x>0){
    r+=qtd[x];
    x-=(x&-x);
  }
  return r;
 }
 
 ll query(int l,int r){
   return query(r) - query(l-1);
 }

 ll solve(int mid){
  int q1 = query_qtd(mid-1);
  int q2 = query_qtd(n) - query_qtd(mid);
  return q1 * mid - query(mid-1) + query(mid+1,n) - q2 * mid;
 }
 
 void update(int x,int val,int add = 1){
   while(x<MAX){
     bit[x]+=val;
     qtd[x]+=add;
     x+=(x&-x);
   }
 }
 
 int find_kth(int k){
   int sum=0;
   int pos=0;
   // 20 == log -> trocar conforme necessario
   for(int i=20;i>=0;i--){
     if(pos+(1LL<<i)>n)continue;
     int atual = qtd[pos+(1LL<<i)];
     if(sum+atual<k){
       sum+=atual;
       pos+=(1LL<<i);
     }
     
   }
   
   //acha a maior pos com <k;
   return pos+1;
 }
   
};

const int inf1 = 1e5 + 1,inf2 = 2e5 + 2; 
int32_t main(){
  fastio;
  int n,q;
  cin>>n>>q;

  BIT Tx(N);
  BIT Ty(N);
  ST T(N);
  for(int i=0;i<n;i++){
    int x,y;
    cin>>x>>y;
    x++;y++;
    int XX = x-y+inf1;
    int YY = x+y;
    T.upd(XX,YY,1);
    Tx.update(x,x,1);
    Ty.update(y,y,1);
  }

  for(int i=0;i<q;i++){
    // resolve:
    
    if(n&1){
      int m = (n+1)/2;
      int medx = Tx.find_kth(m);
      int medy = Ty.find_kth(m);

      ll res = Tx.solve(medx) + Ty.solve(medy);
      int l = 0,r = inf2;
      int ans=0;
      int XX = medx - medy + inf1;
      int YY = medx + medy; 
   
      while(l<=r){
        int mid = (l+r)/2;
        int a1 = max(0,XX - mid);
        int a2 = min(inf2,XX + mid);
        if(T.query(a1,a2,YY,mid)){
          ans = mid;
          r = mid-1;
        }else l = mid+1;
      }
      cout <<res - ans << endl;
    }else if(n>0){
      int m = (n/2);
      int medx = Tx.find_kth(m);
      int medy = Ty.find_kth(m);
     // cout << medx<<" "<<medy << endl;
      cout << Tx.solve(medx) + Ty.solve(medy) << endl;
    }else cout << 0 << endl;

    int op,x,y;
    cin>>op>>x>>y;
    x++;y++;
    int XX = x-y+inf1;
    int YY = x+y;
    if(op == 1){
      n++;
      Tx.update(x,x,1);
      Ty.update(y,y,1);
      T.upd(XX,YY,1);
    }else{
      n--;
      Tx.update(x,-x,-1);
      Ty.update(y,-y,-1);
      T.upd(XX,YY,0);
    }

  }

  if(n&1){
      int m = (n+1)/2;
      int medx = Tx.find_kth(m);
      int medy = Ty.find_kth(m);

      ll res = Tx.solve(medx) + Ty.solve(medy);
      int l = 0,r = inf2;
      int ans=0;
      int XX = medx - medy + inf1;
      int YY = medx + medy; 
   
      while(l<=r){
        int mid = (l+r)/2;
        int a1 = max(0,XX - mid);
        int a2 = min(inf2,XX + mid);
        if(T.query(a1,a2,YY,mid)){
          ans = mid;
          r = mid-1;
        }else l = mid+1;
      }
      cout << res - ans << endl;
    }else if(n>0){
      int m = (n/2);
      int medx = Tx.find_kth(m);
      int medy = Ty.find_kth(m);
      cout << Tx.solve(medx) + Ty.solve(medy) << endl;
    }else cout << 0 << endl;

  // Math -> gcd it all
  // Did u check N=1? Did you switch N,M?
} 
