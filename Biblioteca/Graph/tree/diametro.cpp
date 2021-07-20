struct Tree{
  vector<vector<pii> > g;
  vi pai;
  int N;
  Tree(){}
  Tree(int n){
    N = n;
    g.resize(N+1,vector<pii>());
    pai.resize(N+1);
  }
  void addEdge(int a,int b,int c = 1){
    g[a].pb(pii(b,c));
    g[b].pb(pii(a,c));
  }

  void dfs(int v,int p,vector<ll>& d){
    if(p==-1)d[v]=0;
    for(auto to : g[v])if(to.ff!=p){
      d[to.ff] = d[v] + to.ss;
      pai[to.ff]=v;
      dfs(to.ff,v,d);
    }
  }

  ll diametro(){
    vector<ll> d[2];
    int root = 1;
    int ponta[2]={0,0};// pontas do diametro
    rep(it,0,2){
      d[it].resize(N+1,0);
      dfs(root,-1,d[it]);
      ll best=-1;
      int id=0;
      for(int i=1;i<=N;i++)if(d[it][i] > best){
        best = d[it][i];
        id = i;
      }
      root = id;
      ponta[it] = id;
    }
    dfs(ponta[0],-1,d[0]);
    dfs(ponta[1],-1,d[1]);
    // max(d[0][i],d[1][i]) == maior distancia pra alguma folha
    ll diam=d[1][ponta[0]];
    
    vi path;
    int cur = ponta[0];
    while(cur!=ponta[1]){
      path.pb(cur);
      cur = pai[cur];
    }
    path.pb(ponta[1]);
    cout << diam<<" "<<sz(path)<<endl;
    for(auto it : path)cout<<it-1<<" ";
    cout << endl;
    return diam;
  }

};
