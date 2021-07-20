struct Seg{
  vector<pii> lazy;
  int n;
  Seg(){}
  Seg(int N){
    n = N;
    lazy.resize(4*n + 100,pii(0,0));
  }

  void pushdown(int no){
    int l = no << 1 ,r = no << 1 | 1;
    lazy[l].ss = min(max(lazy[no].ss,lazy[l].ss),lazy[no].ff);
    lazy[l].ff = max(min(lazy[no].ff,lazy[l].ff),lazy[no].ss);
    //
    lazy[r].ss = min(max(lazy[no].ss,lazy[r].ss),lazy[no].ff);
    lazy[r].ff = max(min(lazy[no].ff,lazy[r].ff),lazy[no].ss);
  }
  void pushup(int no){
    int l = no << 1 ,r = no << 1 | 1;
    lazy[no].ff = max(lazy[l].ff,lazy[r].ff);
    lazy[no].ss = min(lazy[l].ss,lazy[r].ss);
  }
  void upd(int no,int i,int j,int a,int b,pii v){
    if(i > b || j < a)return;
    if(a<=i and j<=b){
      if(v.ff == 1){
        lazy[no].ff = max(lazy[no].ff,v.ss);
        lazy[no].ss = max(lazy[no].ss,v.ss);
      }else{
        lazy[no].ff = min(lazy[no].ff,v.ss);
        lazy[no].ss = min(lazy[no].ss,v.ss);
      }
      return;
    }
    pushdown(no);
    int mid = (i + j) >> 1,l = no << 1 ,r = no << 1 |1;
    upd(l,i,mid,a,min(mid,b),v);
    upd(r,mid+1,j,max(a,mid+1),b,v);

    pushup(no);
  }
  void upd(int l,int r,pii v){
    return upd(1,1,n,l,r,v);
  }

  void query(int no,int i,int j,vi& res){
    if(i == j){
      res[i] = lazy[no].ss;
      return;
    }
    pushdown(no);
    int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
    query(l,i,mid,res);
    query(r,mid+1,j,res);
  }
  
  void query(vi& res){
    query(1,1,n,res);
  }
};
