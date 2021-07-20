struct segtree{

  vector<int> tree;
  int n;
  segtree(){}
  segtree(int _n){
    _n++;
    n = _n;
    tree.resize(4*n,0);
  }
  void update(int no,int i,int j,int p,int val){
    if(i==j){
      tree[no] = max(tree[no],val);
      return;
    }
    int mid = (i+j)/2,l=no*2,r=no*2 + 1;
    if(p<=mid)update(l,i,mid,p,val);
    else update(r,mid+1,j,p,val);
    tree[no] = max(tree[l],tree[r]); 
  }
  int query(int no,int i,int j,int a,int b){
    if(i>j or i>b or j<a or a>b)return 0;
    if(a<=i and j<=b)return tree[no];
    int mid = (i+j)/2,l=no*2,r=no*2 + 1;
    return max(query(l,i,mid,a,b),query(r,mid+1,j,a,b));
  }
  void build(int no,int i,int j){
    if(i==j){
      tree[no] = 0;
      return;
    }
    int mid = (i+j)/2,l=2*no,r=2*no+1;
    build(l,i,mid);build(r,mid+1,j);
    tree[no] = max(tree[l],tree[r]);
  }
};
