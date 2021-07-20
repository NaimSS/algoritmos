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

const int N = 200100;
int ar[N],x[N],y[N];
const int inf = 1e9;

int tree[N*4][2][2];

void build(int no,int i,int j){
  if(i == j){
    tree[no][0][0] = x[ar[i]];
    tree[no][1][1] = y[ar[i]];
    tree[no][0][1] = tree[no][1][0] = inf;
    return;
  }
  int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
  build(l,i,mid);build(r,mid+1,j);
  rep(i,0,2)rep(j,0,2)tree[no][i][j]=inf;
  rep(i,0,2){
    int f1 = min(tree[l][i][0],tree[l][i][1]);

    rep(j,0,2){
      int ini = (j==0 ? x[ar[mid+1]] : y[ar[mid+1]]);
      if(f1<=ini){
        tree[no][i][1] = min(tree[no][i][1],tree[r][j][1]);
        tree[no][i][0] = min(tree[no][i][0],tree[r][j][0]);
      }
    }
  }

}
void upd(int no,int i,int j,int p){
  if(i == j){
    tree[no][0][0] = x[ar[i]];
    tree[no][1][1] = y[ar[i]];
    tree[no][0][1] = tree[no][1][0] = inf;
    return;
  }
  int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
  if(p<=mid)upd(l,i,mid,p);
  else upd(r,mid+1,j,p);
  rep(i,0,2)rep(j,0,2)tree[no][i][j]=inf;
  rep(i,0,2){
    int f1 = min(tree[l][i][0],tree[l][i][1]);

    rep(j,0,2){
      int ini = (j==0 ? x[ar[mid+1]] : y[ar[mid+1]]);
      if(f1<=ini){
        tree[no][i][1] = min(tree[no][i][1],tree[r][j][1]);
        tree[no][i][0] = min(tree[no][i][0],tree[r][j][0]);
      }
    }
  }
}
void tranversal(int no,int i,int j){
  if(i == j){
    cout<<"leaf "<<i<<" "<<tree[no][0][0]<<" "<<tree[no][1][1]<<endl;
    return;
  }
  int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
  tranversal(l,i,mid);
  tranversal(r,mid+1,j);
  rep(i,0,2)rep(j,0,2)cout << tree[no][i][j]<<" ";
  cout<<endl;
}
int32_t main(){
  fastio;
  int n;
  cin>>n;
  for(int i=1;i<=n;i++){
    cin >> x[i] >> y[i];
    ar[i] = i;
  }
  build(1,1,n);
  int q;
  cin >> q;
  while(q--){
    int a,b;
    cin>>a>>b;
    swap(ar[a],ar[b]);
    upd(1,1,n,a);
    upd(1,1,n,b);
    int res = inf;
    rep(i,0,2)rep(j,0,2)res=min(res,tree[1][i][j]);
    if(res<inf)cout<<"TAK"<<endl;
    else cout <<"NIE"<<endl;
  }
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
