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
const int inf = 1e9 + 1;
const int N = 755;
int A[N][N];
int pai[N*N];
int tam[N*N];
int qtd[N*N];
int dx[] ={0,1,0,-1};
int dy[] ={1,0,-1,0};
int DX[] ={1,1,-1,-1};
int DY[] ={1,-1,1,-1}; 
int hsh(int i,int j){
  return i*N + j;
}
int f(int x){
  return pai[x] = (pai[x] == x ? x : f(pai[x]));
}
void join(int a,int b){
  a=f(a);
  b=f(b);
  if(a==b)return;
  if(tam[a] > tam[b])swap(a,b);
  pai[a] = b;
  tam[b]+=tam[a];
  qtd[b]+=qtd[a];
}

int n;

int eval(int a,int b,int c){
  if(a + b + c == 0)return 1;
  if(a + b + c == 1){
    if(b == 1)return 1;
    return -1;
  }
  if(a+b+c == 2){
    if(b == 0)return -3;
    return -1;
  }
  return 1;
}

void print(int a,int b){
  cout<<"("<<a<<","<<b<<") ";
}

int32_t main(){
  fastio;
    ifstream cin("valleys.in");
  ofstream cout("valleys.out");
  cin >> n;
  rep(i,0,N*N)pai[i]=i,tam[i] =1;
  rep(i,0,N)rep(j,0,N)A[i][j] =inf;
  vector<pii> vec;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      cin >> A[i][j];
      vec.pb(pii(i,j));
    }
  }

  sort(all(vec),[&](pii a,pii b){
    return A[a.ff][a.ss] < A[b.ff][b.ss];
  });
  ll res=0;
  for(auto it : vec){
    int i = it.ff,j = it.ss;
    for(int k=0;k<4;k++){
      int l = i + dx[k];
      int c = j + dy[k];
      if(A[i][j] >= A[l][c]){
        join(hsh(i,j),hsh(l,c));
      }
    }
    int curva = 0;

    for(int k=0;k<4;k++){
      
      int v =  hsh(i,j);

      int v1 = hsh(i + DX[k],j);
      int v2 = hsh(i + DX[k], j + DY[k]);
      int v3 = hsh(i,j + DY[k]);
     
      curva+=eval(f(v)==f(v1),f(v)==f(v2),f(v)==f(v3));
    }

    qtd[f(hsh(i,j))]+=curva;
    if(qtd[f(hsh(i,j))] > 0){
      res+=tam[f(hsh(i,j))];
    }
  }

  cout << res << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
