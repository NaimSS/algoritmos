struct Seg{
  int n;
  vector<ll> a1,an,tree;
  Seg(){}
  Seg(int N){
    n = N;
    tree = a1 = an = vector<ll>(4*n + 100,0);
  }

  void flush(int no,ll i,ll j){
    if(a1[no] + an[no] == 0)return;
    // CAREFUL WITH OVERFLOW
    tree[no]+=1ll*(a1[no] + an[no])*(j-i+1)/2;

     
    int mid = (i+j)>>1,L=no<<1,R=no<<1|1;
    if(i!=j){
      ll step = (an[no] - a1[no])/(j - i);
      ll m = (mid - i);
    
      a1[L]+=a1[no];
      an[L]+=a1[no] + step * m;

      a1[R]+=a1[no] + (step * (m+1));
      an[R]+=an[no];
    }
    a1[no] = an[no] = 0;
  }

  void upd(int no,int i,int j,int a,int b,pll v){
    // v.ff + (i-a) * v.ss;
    flush(no,i,j);
    if(i > b || j <a)return;
    if(a<=i and j<=b){
      a1[no]+=v.ff + (v.ss)*ll(i - a);
      an[no]+=v.ff + (v.ss)*ll(j - a);
      flush(no,i,j);
      return;
    }
    int mid = (i+j)>>1,L=no<<1,R=no<<1|1;
    upd(L,i,mid,a,b,v);
    upd(R,mid+1,j,a,b,v);
    tree[no] = tree[L] + tree[R];
  } 
  void upd(int L,int R,int a,int d){
    upd(1,1,n,L,R,pll(a,d));
  }
  ll query(int no,int i,int j,int a,int b){
    flush(no,i,j);
    if(i > b || j < a)return 0;
    if(a<=i and j<=b)return tree[no];
    int mid = (i+j)>>1,L=no<<1,R=no<<1|1;
    return query(L,i,mid,a,b) + query(R,mid+1,j,a,b);
  }
  ll query(int a,int b){
    return query(1,1,n,a,b);
  }
};
