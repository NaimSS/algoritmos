// based on yan_silva code
// used on https://codeforces.com/contest/487/problem/E
// if using with hld update cut vertex on its parent!!! parent[root] == root

struct blockCutTree{
  int n;
  vi tin,low,art,stk;
  vector<vi> comps;
  vector<vi> adj;
  vi mark;
  vi edgeBCC,hasEdge;
  vi indBCC,indNode;
  blockCutTree(){}
  blockCutTree(int _n,int _m){//0-index
    n = _n;
    int m = _m;
    low = art = tin = mark = edgeBCC = indBCC = indNode = hasEdge = vector<int>(n+m,0);
    adj.resize(n,vector<int>());
  }
  vector<pii> edges;
  int cur_id=0;
  void addEdge(int a,int b){
    edges.pb(pii(a,b));
    adj[a].pb(cur_id);
    adj[b].pb(cur_id);
    cur_id++;
  }
  int t;
  int curComponent=0;
  void makeBCC(int id,bool Clear = false){
    if(stk.empty())return;
    int last;

    do{
      last = stk.back();
      stk.pop_back();
      edgeBCC[last] = curComponent;
      int u = edges[last].ff;
      int v = edges[last].ss;
      indBCC[u] = indBCC[v] = curComponent;

      if(Clear)id = last -1;
    }while(!stk.empty() and last!=id);
    curComponent++;
  }

  void dfs(int x,bool Root = false){
    low[x] = tin[x] = ++t;
    bool hasPath=0;
    for(int id : adj[x]){
      int to = (edges[id].ff == x ? edges[id].ss : edges[id].ff);
      if(mark[id])continue;
      mark[id] = 1;
      stk.pb(id);
      if(tin[to]!=0){
        low[x] = min(low[x],tin[to]);
        continue; 
      }
      dfs(to);
      if(Root ? hasPath : (low[to]>=tin[x])){
       
        makeBCC(id);
        art[x] = 1;
      }
      hasPath = 1;
      low[x] = min(low[x],low[to]);
    }
  }
  int cnt;
  vector<pii> build_tree(){
    t=0;
    dfs(0,true); // assuming is connected!
    makeBCC(-1,true);
    cnt = curComponent;
    vector<pii> edge;

    for(int i=0;i<n;i++){
      if(!art[i]){
        continue;
      }
      indNode[i] = cnt++;
      for(int id : adj[i]){
        int c = edgeBCC[id];
        if(hasEdge[c])continue;
        hasEdge[c] = 1;

        edge.pb(pii(indNode[i] , c));
      }

      for(int id : adj[i])
        hasEdge[edgeBCC[id]] = false;
      

    }
    return edge;
  }
  
};
