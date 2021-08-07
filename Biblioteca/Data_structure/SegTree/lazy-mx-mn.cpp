ll tree[4*MAXN];
ll lazy[4*MAXN];
int n;

void build(int no,int i,int j){
	if(i==j){
		tree[no] = pre[n] - pre[i-1];
	}else{
		int m = (i+j)/2;
		int l = 2*no,r=2*no+1;
		build(l,i,m);
		build(r,m+1,j);
		tree[no] = min(tree[l],tree[r]);
	}
}

void propagate(int no,int i,int j){
	if(lazy[no]==0)return;
	tree[no]+=lazy[no];
	if(i!=j){
		lazy[2*no]+=lazy[no];
		lazy[2*no+1]+=lazy[no];
	}
	lazy[no] = 0;
}

void update(int no,int i,int j,int a,int b,int v){
	propagate(no,i,j);
	if(i>b || j<a || i>j)return;
	if(a<=i && j<=b){
		tree[no] += v;
		if(i!=j){
			lazy[2*no]+=v;
			lazy[2*no+1]+=v;
		}
		return;
	}
	int m = (i+j)/2;
	int l = 2*no,r=2*no+1;
	update(l,i,m,a,b,v);
	update(r,m+1,j,a,b,v);	
	tree[no] = min(tree[l],tree[r]);
}

int query(int no,int i,int j,int a,int b){
	if(i>b || j<a || i>j)return 1e15;
	
	propagate(no,i,j);
	
	if(a<=i && j<=b)return tree[no];
	
	int m = (i+j)/2;
	int l = 2*no,r=2*no+1;
	
	return min(query(l,i,m,a,b),query(r,m+1,j,a,b));
}

