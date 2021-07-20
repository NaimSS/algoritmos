struct Tree{
  int N,MAXL;
  vector<vi> g;
  vector<vi> ans;
  vi tin,tout;
  vi H,tam;
  Tree(){}
  Tree(int n,int _MAXL = 20){
    N = n;
    MAXL = _MAXL;
    tam = H = tin = tout = vi(n+1,0);
    g.resize(n + 1);
    ans = vector<vi>(n+1,vi(MAXL,0));
    t=0;
  }
  int t;
  void dfs(int v,int p = -1){
    tin[v] = ++t;
    tam[v]=1;
    for(int to : g[v])if(to!=p){
      H[to] = H[v] + 1;
      ans[to][0] = v;
      dfs(to,v);
      tam[v]+=tam[to];
    }
    tout[v] = ++t;
  }
  void init(){
    t=0;
    // assuming conected!!!
    ans[1][0] = 1,H[1] = 0;
    dfs(1);

    for(int j=1;j<MAXL;j++){
      for(int i=1;i<=N;i++){
        ans[i][j] = ans[ans[i][j-1]][j-1];
      }
    }
  }
  void addEdge(int a,int b){
    g[a].pb(b);
    g[b].pb(a);
  }

  bool is_ans(int a,int b){
    return tin[a]<=tin[b] and tout[a]>=tout[b]; 
  }
  int lca(int a,int b){

    if(H[a] < H[b])swap(a,b);
    for(int j=MAXL-1;j>=0;j--){
      if(H[a] - (1<<j) >= H[b]){
        a=ans[a][j];
      }
    }
    if(a==b)return a;
    for(int j=MAXL-1;j>=0;j--){
      if(ans[a][j]!=ans[b][j]){
        a=ans[a][j],b=ans[b][j];
      }
    }
    return ans[a][0];
  }
  int dist(int a,int b){
    return H[a] + H[b] - 2*H[lca(a,b)]; 
  }
  int up(int v,int k){
    for(int j=MAXL-1;j>=0;j--){
      if(k&(1<<j))v = ans[v][j];
    } 
    return v;
  }
  // for CSA
  bool inpath(int a,int b,int c){
    int L = lca(a,b);
   
    if(c == L)return 1;
    if(!is_ans(c,a) and !is_ans(c,b))return 0;
    if(is_ans(c,L) and c!=L)return 0;
    return 1;
  }
  int get(int a,int c){
    int d = dist(a,c);
    a = up(a,d-1);
    return a;
  }
  int solve(int a,int b,int c){
    if(!inpath(a,b,c))return 0;
    int L = lca(a,b);
    if(c == L){
      return N - tam[get(a,c)] - tam[get(b,c)];
    }
    if(is_ans(c,a))return tam[c] - tam[get(a,c)];
    return tam[c] - tam[get(b,c)];
  }


};
