// https://codeforces.com/contest/962/problem/F
const int N = 100100;
pii e[N];
int too(int c,int id){
  return e[id].ff^e[id].ss^c;
}
vi g[N];
int low[N],tin[N];
int t=0;
int st;
int vis[N];
stack<int> s;
vector<vi> comp;
void dfs(int v,int p=-1){
  tin[v] = low[v] = ++t;
  vis[v] = 1;
  bool ok = 0;
  for(int id : g[v]){
    int to = too(v,id);
    if(id==p)continue;
  //  cout << v<<" -> "<<to << endl;
    if(!vis[to]){
      s.push(id);
      dfs(to,id);
      low[v] = min(low[v],low[to]);
      if((v == st and ok) || (v!=st and low[to]>=tin[v])){
        // articulation point!
        vi ans;
        while(!s.empty()){
          int u = s.top();s.pop();
          ans.pb(u);
          if(u == id)
            break;
        }
 
        if(sz(ans))comp.pb(ans);
      }

     if(v == st)
      ok = 1; 

    }else{
      if(tin[to] < tin[v]){
        // back edge
        s.push(id);
      }
      low[v] = min(low[v],tin[to]);
    }
  }


  if(v == st){
    vi ans;

    while(!s.empty()){
      int u = s.top();
      s.pop();
      ans.pb(u);
    }
    if(sz(ans))comp.pb(ans);
  }

}
