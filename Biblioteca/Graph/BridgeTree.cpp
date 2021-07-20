// Refer to https://codeforces.com/contest/659/problem/E
// O((N+M)*alpha)
// Reference: Blog do Baba
// Arestas bidirecionais!!
// n,m devem ser globais
const int N = ;//maxN

const int M = ;//maxM
vector<int> t[N]; // bridge tree;
vector<int> g[N];
int U[M],V[M],vis[N],arr[N],dsu[N];
bool isbrigde[M];
int sz[N];
int adj(int u,int e){
  return U[e]^V[e]^u;
}

int f(int x){
  return dsu[x]==x ? x : dsu[x] = f(dsu[x]);
}
void merge(int a,int b){
  a=f(a),b=f(b);
  if(a==b)return;
  if(sz[a] > sz[b])swap(a,b);
  sz[b]+=sz[a];
  dsu[f(a)] = f(b);
}
int T=1;
int dfs0(int u,int edge){
  vis[u] = 1;
  arr[u] = T++;
  int dbe = arr[u];
  for(int i=0;i<(int)g[u].size();i++){
    int e = g[u][i];
    int w = adj(u,e);
    if(!vis[w])dbe = min(dbe,dfs0(w,e));
    else if(e!=edge)dbe = min(dbe,arr[w]);
  }
  if(dbe == arr[u] && edge!=-1)isbrigde[edge] = 1;
  else if(edge!=-1)merge(U[edge],V[edge]);
  return dbe;
}
int n,m;
int k=0;
int mp[N],rev[N];
void buildBridgeTree(){
  for(int i=1;i<=n;i++){dsu[i] = i;vis[i] = 0;sz[i]=1;}
  for(int i=1;i<=n;i++)if(!vis[i])dfs0(i,-1);
  k=0;
  for(int i=1;i<=n;i++){
    if(mp[f(i)]==0){
      mp[f(i)] = ++k;
      rev[k]=f(i);
    }
  }
  for(int i=1;i<=m;i++){
    if(f(U[i])!=f(V[i])){
      int a = f(U[i]);
      int b = f(V[i]);

      t[mp[a]].pb(mp[b]);
      t[mp[b]].pb(mp[a]);
    }
  }
}

void read(){
  for(int i=1;i<=m;i++){
    int a,b;
    cin>>a>>b;
    U[i] = a;
    V[i] = b;
    g[a].pb(i);
    g[b].pb(i);
  }
}
