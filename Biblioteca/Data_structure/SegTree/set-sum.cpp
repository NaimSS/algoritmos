struct SegTree{//#define int long long 
  vector<ll> tree;
  vector<pll> lazy;
  int n;
  SegTree(int nn){
    n = nn;
    tree.resize(4*n + 100);
    lazy.resize(4*n + 100);
    rep(i,0,4*n+100){
      tree[i]=0;
      lazy[i] = pll(0,-1);
    }
  }
    SegTree(){}
  void pushdown(int no,int i,int j){
      int ad = lazy[no].ff;
      int se = lazy[no].ss;
      if(ad==0 and se == -1)return;
      lazy[no] = pii(0,-1);
      if(se >= 0){
          tree[no] = 1LL*(j-i + 1)*(se);
          if(i!=j){
              lazy[2*no].ff = lazy[2*no+1].ff = 0;
              lazy[2*no].ss = lazy[2*no+1].ss = se;
          }
      }
      if(ad){
          tree[no]+=1LL*(j-i+1)*(ad);
          if(i!=j){
              if(lazy[2*no].ss >= 0)lazy[2*no].ss+=ad;
              else lazy[2*no].ff+=ad;
              if(lazy[2*no+1].ss >= 0)lazy[2*no+1].ss+=ad;
              else lazy[2*no+1].ff+=ad;
          }
      }
  }
  void pushup(int no,int i,int j){
      pushdown(no,i,j);
      if(i!=j){
          int m = (i+j)/2;
          pushdown(2*no,i,m);pushdown(2*no+1,m+1,j);
      }
      tree[no] = tree[2*no] + tree[2*no+1];
  }
   
  int query(int no,int i,int j,int a,int b){
      if(i>j || i>b || j<a)return 0;
      pushdown(no,i,j);
      if(a<=i && j<=b)return tree[no];
      int l =2*no,r=2*no+1,m=(i+j)/2;
      return query(l,i,m,a,b)+query(r,m+1,j,a,b);
  }
  // op == 1 -> ad,2 é set
  // add > 0 , set >=0
  void update(int no,int i,int j,int a,int b,int op,int v){
      if(i>j || i>b || j<a)return;
      pushdown(no,i,j);
      if(a<=i && j<=b){
          if(op==1){
              lazy[no] = pii(v,-1);
          }else{
              lazy[no] = pii(0,v);
          }
          pushdown(no,i,j);
          return;
      }    
      int l=2*no,r=2*no+1,m=(i+j)/2;
      update(l,i,m,a,b,op,v);
      update(r,m+1,j,a,b,op,v);
      pushup(no,i,j);
  }
  void Set(int L,int R,int v){
    update(1,1,n,L,R,2,v);
  }
  void Sum(int L,int R,int v){
    update(1,1,n,L,R,1,v);
  }
  int query(int L,int R){
    return query(1,1,n,L,R);
  }

}Seg;
