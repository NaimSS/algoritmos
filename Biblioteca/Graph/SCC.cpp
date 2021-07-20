// Status: Not tested (only on this->https://codeforces.com/contest/1248/problem/F)

const int MAXN = 1e6 + 10;

vector<int> g[MAXN];
vector<int> gt[MAXN];
 int vis[MAXN];
vector<int> order;
 int comp[MAXN];
int in = 0;
 
void dfs(int v){
  vis[v]=true;
  for(int i=0;i<(int)g[v].size();i++){
    int u = g[v][i];
    if(!vis[u])dfs(u);
  }
  order.pb(v);
}
 
void dfs2(int v){
  comp[v] = in;
  vis[v] = true;
  for(int i=0;i<(int)gt[v].size();i++){
    int u = gt[v][i];
    if(!vis[u])dfs2(u);
  }
}
  
  vector<int> dag[MAXN];
  int bad[MAXN];
  int mark[MAXN];
  int n,m;
  void build(){
  order.clear();
  for(int i=1;i<=n;i++){
      g[i].clear();gt[i].clear();
      dag[i].clear();
      mark[i] =0;
    }
    for(int i=0;i<m;i++){
      int a,b;
      cin>>a>>b;
      g[a].pb(b);
      gt[b].pb(a);
    }
  in =0;
  for(int i=1;i<=n;i++)vis[i] = 0;
  for(int i=1;i<=n;i++){
    bad[i] = 0;
    mark[i] =0;
    if(!vis[i])dfs(i);
  }
  for(int i=1;i<=n;i++)vis[i] = 0;
    for(int i=n-1;i>=0;i--){
      int v = order[i];
      if(!vis[v]){
      in++;
      dfs2(v);
    }
  }
    
    for(int i=1;i<=n;i++){
      
      for(int j=0;j<g[i].size();j++){
        int v = g[i][j];
        if(comp[v]!=comp[i])dag[comp[i]].pb(comp[v]);
      }
    }
   
    
  }
