// https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/C
struct Seg{
  int n;
  vector<int> cnt,esq,dir,lazy,tot;
  Seg(){}
  Seg(int N){
    n = N;
    lazy = cnt = esq = dir = tot =  vi(4*n + 100,0);
    for(int i=0;i<sz(lazy);i++)lazy[i] = -1;
  }
void flush(int no,int i,int j){
  if(lazy[no] == -1)return;
 
  cnt[no] = 0;
  esq[no] = dir[no] = lazy[no];
  tot[no] = (lazy[no] ? j - i + 1 : 0);
  if(i!=j){
    lazy[no<<1] = lazy[no<<1|1]= lazy[no];
  }
  lazy[no] = -1;
}

  void upd(int no,int i,int j,int a,int b,int c){
    flush(no,i,j);
    if(i > b || j < a)return;
    
    if(a<=i and j<=b){
      lazy[no] = c;
      flush(no,i,j);
      return;
    }
    int mid = (i + j) >> 1,l = no << 1 ,r = no << 1 |1;
    upd(l,i,mid,a,b,c);
    upd(r,mid+1,j,a,b,c);
    esq[no] = esq[l];

    dir[no] = dir[r];
    cnt[no] = cnt[l] + cnt[r] + (dir[l]!=esq[r]);
    tot[no] = tot[l] + tot[r];
  }
  void upd(int a,int b,int c){
    upd(1,1,n,a,b,c);
  }
  pii query(){
    flush(1,1,n);
    return pii(cnt[1],tot[1]);
  }

};
