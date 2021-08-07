// source: https://codeforces.com/blog/entry/44351

void add(int v,int p,int x){
  update(cnt[cor[v]],-1);
  cnt[cor[v]]+=x;
  update(cnt[cor[v]],1);
  for(auto to : g[v]){
    if(to!=p and !big[to])add(to,v,x);
  }
}

int n;

void dfs(int v,int p,bool keep){
  int mx=-1,bigchild=-1;
  for(auto to : g[v]){
    if(to!=p and mx < sz[to])
      mx=sz[to],bigchild=to;
  }

  for(auto to : g[v]){
    if(to!=p and to!=bigchild){
      dfs(to,v,0);
    }
  }
  if(bigchild!=-1){
    dfs(bigchild,v,1);big[bigchild]=1;
  }
  add(v,p,1);
  // answer queries;
  for(auto q : qry[v]){
    int k = q.ff;
    int id = q.ss;
    res[id] = query(k,n);
  }
  if(bigchild!=-1)big[bigchild]=0;
  if(!keep)add(v,p,-1);

}
