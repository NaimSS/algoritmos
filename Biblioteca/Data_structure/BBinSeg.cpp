struct node{
 int mx,mn;	
};
node tree[MAXN*4];
 
node merge(node a,node b){
	node c;
	c.mx = max(a.mx,b.mx);
	c.mn = min(a.mn,b.mn);
	return c;
}
 
void build(int no,int i,int j){ // 1 to 2*n
	if(i==j){
		tree[no].mn = tree[no].mx = a[i];
	}else{
		int m = (i+j)/2;
		int l =2*no,r=2*no+1;
		build(l,i,m);
		build(r,m+1,j);
		tree[no] = merge(tree[l],tree[r]);
	}
}
 
 
int maior(int no,int i,int j,int L,int val){
	if(i>j || j<L)return 1e9;
	if(tree[no].mx<val)return 1e9;
	
	if(i==j)return i;
	int m = (i+j)/2;
	int l=2*no,r=2*no+1;
	
	if(i<L){
		return min(maior(l,i,m,L,val),maior(r,m+1,j,L,val));
	}
	if(tree[l].mx>=val)return maior(l,i,m,L,val);
	return maior(r,m+1,j,L,val);
	
}
// alterar conforme necessario
int menor(int no,int i,int j,int L,int R,int val){
	if(i>j || j<L || i>R)return 1e9 + 10;
	if(tree[no].mn>=val)return 1e9 + 10;
	if(i==j)return i;
	int m = (i+j)/2;
	int l=2*no,r=2*no+1;
	
	if(i<L || j>R){
		return min(menor(l,i,m,L,R,val),menor(r,m+1,j,L,R,val));
	}
	if(tree[l].mn<val)return menor(l,i,m,L,R,val);
	return menor(r,m+1,j,L,R,val);	  		
}
