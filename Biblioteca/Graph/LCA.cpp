// O(logN) LCA

const int MAXL = 20;
int level[MAXN];
vector<int> adj[MAXN];
int pai[MAXN];
int ans[MAXN][MAXL+1];
int euler[MAXN];
int out[MAXN];

int is_ans(int u,int v){
	return euler[u]<=euler[v] && out[v]<=out[u];
}

int LCA(int u,int v){
	if(is_ans(u,v)){
		return u;
	}
	for(int i=MAXL-1;i>=0;i--){
		if(ans[u][i]==-1)continue;
		if(!is_ans(ans[u][i],v))u = ans[u][i];
	}
	return ans[u][0];
}

int tim = 0;
 
void dfs(int u,int p){
	euler[u]=tim++;
	pai[u]=p;
	level[u] = 1 + level[p];
	for(int i=0;i<(int)adj[u].size();i++){
		int v = adj[u][i];
		if(v==p)continue;
		dfs(v,u);
	}
	out[u] = tim++;
}
void init(){
  dfs(1,-1);
  pai[1] = 1;
	for(int i=1;i<=n;i++)ans[i][0] = pai[i];
	for(int j=1;j<MAXL;j++){
	  for(int i=1;i<=n;i++){
	    ans[i][j] = ans[ans[i][j-1]][j-1];
	  }
	}
}
