// https://codeforces.com/contest/1363/problem/E
// https://codeforces.com/contest/1099/problem/F
struct segtree{
  vector<pii> tree;
  int n;
  segtree(){}
  segtree(int _n){
     n = _n;
     tree.resize(n*4 + 100,pii(0,n+2));
  }
 
  void update(int no,int i,int j,int p,pii v){
    if(i==j){
      tree[no]=v;
      return;
    }
    int mid = (i+j)/2;
    int l = 2*no,r=2*no+1;
    if(p<=mid)update(l,i,mid,p,v);
    else update(r,mid+1,j,p,v);
    tree[no].ff = tree[l].ff + tree[r].ff;
    tree[no].ss = min(tree[l].ss,tree[r].ss);
  }
 
  int query(int no,int i,int j,int a,int b){
    if(i>j or i>b or j<a)return 0;
    if(a<=i and j<=b)return tree[no].ff;
 
    int mid = (i+j)/2;
    int l = 2*no,r=2*no+1;
    return query(l,i,mid,a,b) + query(r,mid+1,j,a,b);
  }
  pii find(int no,int i,int j,int L,int R){
    if(i>R or j<L)return pii(1e9,-1);
    if(i==j)return pii(tree[no].ss,i);
    int mid = (i+j)/2;
    int l= 2*no,r=2*no+1;
    if(i<L or j>R){
      return min(find(l,i,mid,L,R),find(r,mid+1,j,L,R));
    }
    if(tree[l].ss < tree[r].ss){
      return find(l,i,mid,L,R);
    }
    return find(r,mid+1,j,L,R);
  }
 
};
