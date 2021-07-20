struct SuperSeg{
  vi tot;
  // vi pre,suf;
  int n;
  SuperSeg(){}
  SuperSeg(int N){
    n = N;
    //pre = suf = 
    tot = vi(4*n+10,0);
  }
  void upd(int no,int i,int j,int p,int v){
    if(i==j){
      tot[no]+=v;
      //pre[no] = max(tot[no],0);
      //suf[no] = max(tot[no],0);
      return;
    }
    int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
    if(p<=mid)upd(l,i,mid,p,v);
    else upd(r,mid+1,j,p,v);
    tot[no] = tot[l] + tot[r];
  }

  int findB(int no,int i,int j,int x){
    if(i==j){
      if(tot[no] > x)return i-1;
      return i;
    }
    int mid =(i+j)>>1,l=no<<1,r=no<<1|1;
    if(tot[l] <= x)return findB(r,mid+1,j,x - tot[l]);
    return findB(l,i,mid,x);
  }
  int findS(int no,int i,int j,int x){
    if(i == j){
      return i;
    }
    int mid =(i+j)>>1,l=no<<1,r=no<<1|1;
    if(tot[l]>=x)return findS(l,i,mid,x);
    return findS(r,mid+1,j,x - tot[l]);
  }

  int findR(int x){
    return findB(1,1,n,x);// maior com <=x
  }
  int findL(int x){
    return findS(1,1,n,tot[1] - x);//menor tal que o resto tem <=x
  }
  pii get(int x){
    return pii(findL(x),findR(x));
  }

};
