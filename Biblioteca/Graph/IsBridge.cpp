/*
 *Finds all the Bridges
 * Handle multiple edges
*/

const int M = 1e6 + 10;
pii e[M];
int is_bridge[M];
int tin[N];
int t=1;
vector<int> adj[N];
int nxt(int v,int i){
  return e[i].ff^e[i].ss^v;
}
int vis[N];
int dfs2(int v,int p=-1){
  vis[v] = 1;
  tin[v] = t++;
  int low = tin[v];
  for(int x : adj[v]){
    int w = nxt(v,x);
    if(!vis[w])low = min(low,dfs2(w,x));
    else if(x!=p)low = min(low,tin[w]);
  }
  if(low==tin[v] and p!=-1)is_bridge[p] = true;
  return low;
}
