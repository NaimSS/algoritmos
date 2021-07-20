struct Seg{
  int n;
  vector<ll> tree,sum;
  vector<ll> lazy;
  Seg(){}
  Seg(int N,vi &a){
    n = N;
    lazy = vi(4*n + 100,0);
    tree = sum = vector<ll>(4*n+100,0);
    build(1,1,n,a);
  }
  void build(int no,int i,int j,vi& a){
    lazy[no] = 0;
    if(i == j){
      tree[no] = sum[no] = a[i];
      return;
    }
    int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
    build(l,i,mid,a);
    build(r,mid+1,j,a);
    tree[no] = tree[l] + tree[r] + sum[r] * (mid - i + 1);
    sum[no] = sum[l] + sum[r];
  }

  void flush(int no,ll i,ll j){
    if(lazy[no] == 0)return;
    sum[no]+=lazy[no]*(j - i + 1);
    tree[no]+=lazy[no]*(1ll * (j - i + 2)*(j-i+1)/2);
    if(i!=j){
      int l=no<<1,r=no<<1|1;
      lazy[l]+=lazy[no];
      lazy[r]+=lazy[no];
    }
    lazy[no] = 0;
  }

  void upd(int no,int i,int j,int a,int b,ll c){
    flush(no,i,j);
    if(i > b || j < a)return;
    
    if(a<=i and j<=b){
      lazy[no]+=c;
      flush(no,i,j);
      return;
    }
    int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
    upd(l,i,mid,a,b,c);
    upd(r,mid+1,j,a,b,c);
    tree[no] = tree[l] + tree[r] + sum[r] * (mid - i + 1);
    sum[no] = sum[l] + sum[r];
  }
  void upd(int a,int b,ll c){
    upd(1,1,n,a,b,c);
  }
  pll query(int no,int i,int j,int a,int b){
    flush(no,i,j);
    if(i > b || j < a)assert(false);
    if(a<=i and j<=b)return pll(tree[no],sum[no]);
    int mid = (i + j) >> 1,l = no << 1 ,r = no << 1 |1;
    if(mid < a)return query(r,mid+1,j,a,b);
    if(mid+1>b)return query(l,i,mid,a,b);
    
    assert(a<=mid and b>mid);

    pll A = query(l,i,mid,a,b);
    pll B = query(r,mid+1,j,a,b);

    ll soma = A.ss + B.ss;
    ll len = mid - max(i,a) + 1;

    ll tot = A.ff + B.ff + B.ss * len;
    
    return pll(tot,soma);
  }
  ll query(int l,int r){
    return query(1,1,n,l,r).ff;
  }

};
