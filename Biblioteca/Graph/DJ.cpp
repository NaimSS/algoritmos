void DJ(vector<int>&d,int S){
  for(int i=1;i<=n;i++){
    vis[i] = 0;
    d[i] = 1e9+10;
  }
  priority_queue<pii,vector<pii>,greater<pii> > pq;
  pq.push(pii(0,S));
  d[S] =0;
  vis[S] = 1;
  while(!pq.empty()){
    int cur = pq.top().ss;
    pq.pop();
    for(auto to : g[cur]){
     // pii to = pii(e[x].a^e[x].b^cur,e[x].c);
      if(d[to.ff] > d[cur] + to.ss){
        d[to.ff] = d[cur] + to.ss;
        if(S==s){
          pai[to.ff] = cur;
          W[to.ff]= to.ss; 
        }
        if(!vis[to.ff]){
          pq.push(pii(d[to.ff],to.ff));
        }
 
      }
    }
  }
 
}
