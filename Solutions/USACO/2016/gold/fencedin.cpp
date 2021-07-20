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

const int N = 2020;
int a[N],b[N];
int dx[]={0,1};
int dy[]={1,0};

struct edge{
  int a,b;
  int c;
  edge(){}
  edge(int A,int B,int C){
    a = A,b = B,c = C;
  }
};
int pai[2002*2002];
int f(int x){
  return pai[x] = (pai[x]==x?x:f(pai[x]));
}
void join(int a,int b){
  pai[f(a)]=f(b);
}
struct coisa{
  int a,b,c;
  coisa(){}
  coisa(int A,int B,int C){
    a = A,b = B, c = C;
  }
};
int32_t main(){
  fastio;
  
  ifstream cin("fencedin.in");
  ofstream cout("fencedin.out");
  
  int AA,BB,n,m;
  cin >> AA >>BB >> n >> m;
  for(int i=1;i<=n;i++)cin>>a[i];
  sort(a+1,a+1+n);  
  n++;
  a[n] = AA;

  for(int i=1;i<=m;i++)cin>>b[i];
  sort(b+1,b+1+m);
  m++;
  b[m] = BB;


  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      pai[j + i*m] = j + i*m;
      
    }
  }
  ll res =0;
  vector<coisa> vec;
  for(int i=0;i<n;i++)vec.pb(coisa(i,0,a[i+1]-a[i]));
  for(int i=0;i<m;i++)vec.pb(coisa(i,1,b[i+1]-b[i]));
  
  sort(all(vec),[&](coisa A,coisa B){
    return A.c < B.c;
  });
  

  for(auto e : vec){
    int cost = e.c;
    if(e.b == 0){
      // i->i+1
      int i = e.a;

      for(int j=0;j<m-1;j++){

        if(f(i * m + j)!=f(i*m + j + 1)){
          join(i*m + j,i * m + j + 1);
          res+=cost;
        }
      }

    }else{
      // j->j+1;
      int j = e.a;
      for(int i=0;i<n-1;i++){
        if(f(i*m + j)!=f((i+1)*m + j)){
          join(i*m + j,(i+1)*m + j);
          res+=cost;
        }
      }
    }
  }  

  cout << res << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
