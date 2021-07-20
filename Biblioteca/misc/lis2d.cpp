/* Find Largest subsequences of pairs strictly increasing (a,b) < (c,d) if and only if a<c and b<d
 * O(Nlog^2N) but pretty fast
 */

const int N = 200100;

int BIT[N];
int vis[N];
int T=0;


void upd(int x,int v){
  while(x<N){
    if(vis[x]!=T){
      vis[x] =T;
      BIT[x] = 0;
    }
    BIT[x] = max(BIT[x],v);
    x+=(x&-x);
  }
}
int sum(int x){
  int r=0;
  while(x>0){
    if(vis[x] == T){
      r = max(r,BIT[x]);
    }
    x-=(x&-x);;
  }
  return r;
}

int dp[N];

struct coisa{
  int x,y,id;
  coisa(){}
  bool operator<(const coisa& a)const{
    return x < a.x;
  }
};


void solve(vector<coisa>& v){
  if(sz(v) == 1){
    return;
  }
  int mid = (sz(v)-1)/2;

  vector<coisa>L,R;
  vi comp;
  for(int i=0;i<=mid;i++)L.pb(v[i]),comp.pb(v[i].y);
  for(int i=mid+1;i<sz(v);i++)R.pb(v[i]),comp.pb(v[i].y);
  
  assert(sz(L) > 0 and sz(R)>0);
  solve(L);
  
  vector<coisa> Left = L,Right = R;
  sort(all(comp));
  comp.erase(unique(all(comp)),comp.end());
  T++;  
  sort(all(Left));sort(all(Right));
  int pos;
  for(int i=0,j=0;i<sz(Right);i++){
    while(j < sz(Left) and Left[j].x < Right[i].x){
      pos = lower_bound(all(comp),Left[j].y) - comp.begin() + 1;
      upd(pos,dp[Left[j].id]);
      j++;
    }
    
    pos = lower_bound(all(comp),Right[i].y) - comp.begin()  + 1 - 1;
    dp[Right[i].id] = max(dp[Right[i].id],1 + sum(pos));
  }
  
  solve(R);
}
