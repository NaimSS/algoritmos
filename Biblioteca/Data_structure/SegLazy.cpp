/*Seg Lazy de soma padrão;
 *Autor: Yo
 */
const int NN = ; //define it

struct SegLazy{
  vector<ll> tree,lazy;
  int n;
  SegLazy(){}
  SegLazy(int _n){
    n = _n;
    tree.resize(n*4 + 10);
    lazy.resize(n*4 + 10);
  }
  void propagate(int no,int i,int j){
    if(i>j)return;
    if(lazy[no]!=0){
      tree[no]+=1LL*lazy[no]*(j-i+1);
      if(i!=j){
        lazy[2*no]+=lazy[no],lazy[2*no+1]+=lazy[no];
      }
      lazy[no] =0;
    }
  }
  void update(int a,int b,int v,int no=1,int i=1,int j=NN){
    propagate(no,i,j);
    if(i>b || j<a || i>j)return;

    if(a<=i and j<=b){
      tree[no]+=1LL*(j-i + 1)*v;
      if(i!=j){
        lazy[2*no]+=v;
        lazy[2*no + 1]+=v;
      }
      return;
    }
    int mid = (i+j)/2,l=2*no,r=2*no+1;
    update(a,b,v,l,i,mid);update(a,b,v,r,mid+1,j);
    tree[no] = tree[l] + tree[r];
  }

  ll query(int a,int b,int no=1,int i=1,int j=NN){
    if(i>j || j<a || i>b)return 0;
    propagate(no,i,j);
    if(a<=i and j<=b)return tree[no];
    int mid = (i+j)/2,l=2*no,r=2*no+1;
    return query(a,b,l,i,mid) + query(a,b,r,mid+1,j);
  }

};
