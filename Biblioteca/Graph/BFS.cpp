void BFS(){
	queue<int> q;
	for(int i=1;i<=n;i++){
		vis[i] = false;
		dist[i] = 1e9;
		if(a[i]==id){ // flag
			q.push(i);
			dist[i] = 0;
			vis[i] = 1;
		}
	}
	while(!q.empty()){
		int v = q.front();
		q.pop();
		for(int i=0;i<adj[v].size();i++){
			int to = adj[v][i];
			if(!vis[to]){
				vis[to] = 1;
				dist[to] = dist[v] + 1;
				q.push(to);
			}
		}
	}
	
	
}
