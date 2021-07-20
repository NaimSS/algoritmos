struct LAZY{
vector<ll> mn,sum,lazy;
int n;
LAZY(){}
LAZY(int _n){ // pass a vector/array if needed
  n = _n;
  mn = sum = lazy = vector<ll>(4*n+10,0);
}




void propagate(int no,int i,int j){
  if(lazy[no]==0)return;
  mn[no]+=lazy[no];
  sum[no]+=lazy[no]*(j-i+1);
  if(i!=j){
    lazy[2*no]+=lazy[no];
    lazy[2*no+1]+=lazy[no];
  }
  lazy[no] = 0;
}

void update(int no,int i,int j,int a,int b,ll v){
  propagate(no,i,j);
  if(i>b || j<a || i>j)return;
  if(a<=i && j<=b){
    lazy[no]+=v;
    propagate(no,i,j);
    return;
  }
  int m = (i+j)/2;
  int l = 2*no,r=2*no+1;
  update(l,i,m,a,b,v);
  update(r,m+1,j,a,b,v);  
  mn[no] = min(mn[l],mn[r]);
  sum[no] = sum[l]+sum[r];
}

ll querymn(int no,int i,int j,int a,int b){
  propagate(no,i,j);
  if(i > b || j < a)return 1e15;
  if(a<=i and j<=b)return mn[no];
  int mid =(i+j)>>1,l=no<<1,r=no<<1|1;
  return min(querymn(l,i,mid,a,b),querymn(r,mid+1,j,a,b));
}
ll querysum(int no,int i,int j,int a,int b){
  propagate(no,i,j);
  if(i>b || j <a)return 0;
  if(a<=i and j<=b)return sum[no];
  int mid =(i+j)>>1,l=no<<1,r=no<<1|1;
  return querysum(l,i,mid,a,b) + querysum(r,mid+1,j,a,b); 
}

};
