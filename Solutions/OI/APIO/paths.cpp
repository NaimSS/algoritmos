// 90% due to TLE... maybe remove maps...
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
const ll inf = 1e9 + 7;
const int N = 1010;

int ID = 0;
map<pii,int> MP;
const int MAXN = 15*N;
pii rev[MAXN];
int where[MAXN];

struct ret{
  int x[4],y[4];
  ret(){}
  ret(int a,int b,int c ,int d,int id){
    if(c == -inf){
      c = a,d = b;
    }
    if(a > c)swap(a,c);
    if(b > d)swap(b,d);
    x[0] = x[3] = a;
    y[0] = y[1] = b;
    x[1] = x[2] = c;
    y[2] = y[3] = d;
    rep(i,0,4){
      if(MP.count(pii(x[i],y[i]))==0){
        MP[pii(x[i],y[i])] = ++ID;
        where[ID] = id;
        rev[ID] = pii(x[i],y[i]);
      }
    }
  }
 friend ostream& operator<<(ostream& os, ret R) {
    for(int i=0;i<4;i++){
      os << R.x[i]<<","<<R.y[i]<<"\n";
    }    
    return os<<endl;
  }
}R[N];



int curT = 0;
template<class T = int>
struct BIT{
 int n;
 int MAX;
 vector<T> bit;
 vector<int> vis;
 BIT(){}
 BIT(int _n){
   n = _n;
   MAX = n +2;
   vis.resize(n + 10,0);
   bit.resize(n+10,0);
 }
 
 T query(int x){
  //assert(x!=0);
   T r=0;
   while(x>0){
     if(vis[x] == curT)r+=bit[x];
     x-=(x&-x);
   }
   return r;
 }
 
 T query(int l,int r){
  if(l > r)swap(l,r);
   return query(r) - query(l-1);
 }
 
 void update(int x,T val){
   while(x<MAX){
     if(vis[x]!=curT){
      vis[x] = curT;
      bit[x]=0;
     }
     bit[x]+=val;
     x+=(x&-x);
   }
 }
 void upd(int l,int r,T val){
  if(l > r)swap(l,r);
  update(l,val);
  update(r+1,-val);
 }
   
};


map<int,int> mx,my;


bool inside(int a,int b,int c){
  return b<=a and a<=c;
}
struct cord{
  ll d;
  int id,c;
  int V;
  cord(){}
  cord(ll d,int id,int c,int V = -1):d(d),id(id),c(c),V(V){}
  bool operator<(const cord& o)const{
    return d > o.d; // reverse at pq;
  }
  friend ostream& operator<<(ostream& os, cord C) {
    return os<<C.d<<" "<<C.id<<" "<<C.c << endl;
  }
};

vector<int> vec[MAXN];
int n;


void join(pii A,pii B,int I,int J){
  //assert(ID + 2 < MAXN);
  if(MP.count(A) == 0){
    MP[A] = ++ID;
    rev[ID] = A;
    where[ID] = I;
  }
  if(MP.count(B) == 0){
    MP[B] = ++ID;
    rev[ID] = B;
    where[ID] = J;
  }
  vec[MP[A]].pb(MP[B]);
  vec[MP[B]].pb(MP[A]);
}

bool ok(int a,int b,int flag){
  if(where[a]!=where[b])return 1;
    int pos = where[a];

  if(flag){
    if(rev[a].ss!=R[pos].y[0] and rev[a].ss!=R[pos].y[3])return 0;
  }else{
    if(rev[a].ff!=R[pos].x[0] and rev[a].ff!=R[pos].x[1])return 0;
  }
  return 1;
}

BIT<int> bit(N*2);

void SWEEP(){

  vi id;
  for(int i=1;i<=n+2;i++){
    id.pb(i);
  }
  rep(iter,0,2){
    sort(all(id),[&](int a,int b){
      if(iter == 0)return R[a].x[0] < R[b].x[0];
      return R[a].y[0] < R[b].y[0];
    });
    for(int pos = 0;pos < sz(id);pos ++ ){
      int I = id[pos];

      curT++;
      for(int pos2=pos-1;pos2>=0;pos2--){
        int J = id[pos2];
        vi C,E;
        if(iter == 0){
          C = {0,3},E = {1,2};
        }else{
          C = {0,1},E = {2,3};
        }
        int bad = 0;
        for(int c : C){
          for(int e : E){
            if(bad)continue;

            int ok1 = 0 ,ok2 = 1;
            if(iter == 0){
              if(R[I].x[c] < R[J].x[e])bad = 1,ok2=0;;
              

              if(inside(R[I].y[c],R[J].y[0],R[J].y[3])){
                if(bit.query(my[R[I].y[c]]) == 0){
                  ok1|=(1<<0);
                }
              }
              if(inside(R[J].y[e] , R[I].y[0],R[I].y[3])){
               if(bit.query(my[R[J].y[e]]) == 0){
                  ok1|=(1<<1);
                }
              }

            }else{

              if(R[I].y[c] < R[J].y[e])bad = 1,ok2 = 0;

              
              if(inside(R[I].x[c],R[J].x[0],R[J].x[1])){
                if(bit.query(mx[R[I].x[c]]) == 0){
                  ok1|=(1<<0);
                }
              }
              if(inside(R[J].x[e],R[I].x[0],R[I].x[1])){
                if(bit.query(mx[R[J].x[e]]) == 0){
                  ok1|=(1<<1);
                }
              }

            }

            if(ok1 and ok2){
             
               if(ok1&1){
                
                if(iter == 0){
                  join(pii(R[I].x[c],R[I].y[c]),pii(R[J].x[e],R[I].y[c]),I,J);
                }else{
                  join(pii(R[I].x[c],R[I].y[c]),pii(R[I].x[c],R[J].y[e]),I,J);
                }
                
               }

               if(ok1&(1<<1)){
                
                if(iter == 0){
                  join(pii(R[J].x[e],R[J].y[e]),pii(R[I].x[c],R[J].y[e]),J,I);
                }else{
                  join(pii(R[J].x[e],R[J].y[e]),pii(R[J].x[e],R[I].y[c]),J,I);
                }

               }

            }

          }
        }
        if(bad)continue;
        if(iter == 0)bit.upd(my[R[J].y[0]],my[R[J].y[3]],1);
        else bit.upd(mx[R[J].x[0]],mx[R[J].x[1]],1);

     }

    }
    

  }

}


ll d[MAXN];
bool vis[MAXN];
typedef pair<ll,ll> pll;

ll dist(int a,int b){
  return abs(rev[a].ff - rev[b].ff) + abs(rev[a].ss - rev[b].ss);
}

void solve(){
  mx.clear();my.clear();
  MP.clear();
  for(int i=0;i<=ID;i++)vec[i].clear(),d[i] = inf * inf,vis[i]=0;
  ID=0;

  int A,B,C,D;cin >> A >> B >> C >> D;
  cin >> n;
  R[n+1] = ret(A,B,A,B,n+1);
  R[n+2] = ret(C,D,C,D,n+2);
  mx[A];mx[C];my[B];my[D];
  for(int i=1;i<=n;i++){
    cin >> A >> B >> C >> D;
    R[i] = ret(A,B,C,D,i);
    mx[A];mx[C];my[B];my[D];
  }
  int Kx=0,Ky=0;
  
  for(auto& it : mx)it.ss = ++Kx;
  for(auto& it : my)it.ss = ++Ky;

  //assert(ID < 4 * (n + 2));
  SWEEP();
  //assert(ID < MAXN);
  mx.clear();my.clear();

  for(int i=0;i<=ID;i++){
    vis[i] = 0;
    d[i] = inf * inf;
  }


  vi Vec;
  for(int i=1;i<=ID;i++)Vec.pb(i);


  sort(all(Vec),[&](int a,int b){
    return rev[a].ff < rev[b].ff;
  });

  for(int id : Vec){
    if(my[rev[id].ss]!=0 and ok(id,my[rev[id].ss],1)){
      vec[id].pb(my[rev[id].ss]);
      vec[my[rev[id].ss]].pb(id);

    }
    my[rev[id].ss] = id;
  }
  sort(all(Vec),[&](int a,int b){
    return rev[a].ss < rev[b].ss;
  });
  for(int id : Vec){
    if(mx[rev[id].ff]!=0 and ok(id,mx[rev[id].ff],0)){
      vec[id].pb(mx[rev[id].ff]);
      vec[mx[rev[id].ff]].pb(id);
    }
    mx[rev[id].ff] = id;
  }

  priority_queue<pll,vector<pll>,greater<pll> > pq;
  
  d[MP[pii(R[n+1].x[0],R[n+1].y[0])]] = 0;
  pq.push(pll(d[MP[pii(R[n+1].x[0],R[n+1].y[0])]],1));

  while(!pq.empty()){
    int cur = pq.top().ss;
    pq.pop();
    if(vis[cur])continue;
    vis[cur] = 1;

    for(int to : vec[cur]){
      if(d[to] > d[cur] + dist(to,cur)){
         pq.push(pll(d[to] = d[cur] + dist(to,cur),to));
      }
    }
  }
  
  ll res = d[MP[pii(R[n+2].x[0],R[n+2].y[0])]];
  
  if(res >= inf * inf){
    cout<<"No Path" << endl;
  }else{
    cout << res << endl;
  }

}

int32_t main(){
  fastio;
  int T;
  cin >> T;
  while(T--){
    solve();
  }
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
