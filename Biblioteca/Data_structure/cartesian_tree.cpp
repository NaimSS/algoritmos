// build O(N),busca O(N)
// util em alguns problemas de DP/quebrar ranges usando o maximo
// menor valor na raiz
// tested on https://judge.yosupo.jp/problem/cartesian_tree
	int root = 0;
	for(int i=1;i<=n;i++){
			int ant = i-1;
			while(ant!=0 and val[ant] > val[i]){
				ant = pai[ant];
			}
			if(ant){
				pai[i] = ant;
				L[i] = R[ant];
				pai[L[i]] = i;
				R[ant] = i;
			}else{
				pai[i] = 0;
				L[i] = root;
				pai[root] = i;
				root = i;
			}
			
	}
	pai[root] = root;
