/* TEMPLATE FOR A CACTUS GRAPH
 * author: NaimSS
 * Finds the number of cicles between two vertices
 * 1 - index, O(N) + O(NlogN) for the LCA
 * tested on https://codeforces.com/problemset/problem/231/E
 */
struct Cactus{
  vector<vi> adj;
  int n,m;
  vi vis,incic,pai,meuval;
  vector<vi> ciclos;
  int cnt = 0;
  Cactus(int _n,int _m){
    n = _n,m = _m;
    adj.resize(2*n + 2);
    vis.resize(2*n + 2);
    incic.resize(2 * n + 2);
    pai = meuval = vis ;
  }

  void addEdge(int a,int b){
    adj[a].pb(b);
    adj[b].pb(a);
  }
  void buildCiclo(int fim,int ini){
    vi cic;
    while(ini!=fim){
      
      cic.pb(ini);
      ini = pai[ini];
    }
    cic.pb(fim);
    ++cnt;
    for(int x : cic){incic[x] = 1,meuval[x] = cnt;}
    ciclos.pb(cic);
  }
  vi L;
  void dfs(int v,int p = -1){
    vis[v] = 1;
    for(int to : adj[v]){
      if(to == p)continue;
      if(vis[to] and to!=p and L[to] < L[v]){
        buildCiclo(to,v);
        continue;
      }
      if(!vis[to]){
        pai[to] = v;
        L[to] = L[v] + 1;
        dfs(to,v);
      }
    }

  }
  vector<vi> g;

  vector<vi> ans;
  vi acu;

  void dfs2(int v,int p = -1){
    acu[v]+=(v<=n);
    for(int to : g[v]){
      if(to == p)continue;
      acu[to] = acu[v];
      L[to] = L[v] + 1;
      ans[to][0] = v;
      dfs2(to,v);
    }
  }

  void buildTree(){
    L = acu = vi(n + n+2,0);
    for(int i=1;i<=n;i++)meuval[i] = n + i;
    dfs(1);
    L = acu = vi(n + n + 2 ,0);
 

    g.resize(n + n + 2);

    for(int i=1;i<=n;i++){
      for(auto to : adj[i]){
        if(meuval[to] == meuval[i])continue;
        g[meuval[i]].pb(meuval[to]);
      }
    }
    ans.resize(2 * n+1,vector<int>(20,0));
      
    ans[meuval[1]][0] = meuval[1];
    L[meuval[1]] = 0;
    dfs2(meuval[1]);
    for(int j=1;j<20;j++){
      for(int i=1;i<=n;i++){
        int id = meuval[i];
        ans[id][j] = ans[ans[id][j-1]][j-1];
      }
    }

  }

  int LCA(int a,int b){
    if(L[a] < L[b])swap(a,b);
    for(int j=19;j>=0;j--){
      if(L[a] - (1<<j) >= L[b]){
        a = ans[a][j];
      }
    }

    if(a == b)return a;
    for(int j=19;j>=0;j--){
      if(ans[a][j]!=ans[b][j]){
        a = ans[a][j],b = ans[b][j];
      }
    }
    return ans[a][0];
  }

  int query(int a,int b){
    a = meuval[a],b = meuval[b];
    int lca = LCA(a,b);

    int tot = acu[a] + acu[b] - 2*acu[lca];
    if(lca<=n)tot++;
    return tot;
  }


};
