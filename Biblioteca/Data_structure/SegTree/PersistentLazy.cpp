// Range update/point query on persistent segment tree
// used on https://codeforces.com/contest/837/problem/G


const int MX = 200100;
const int MAX = 2e7;// change to 2e7



ll pre[N];

int ID = 0;
int version[3 * N];
pll lazy[MAX],val[MAX];
int l[MAX],r[MAX];
// based on bqi persistent lazy seg
#define mid ((i+j)/2)
int build(int i = 1,int j = MX - 10){
  int cur = ++ID;

  lazy[cur] = val[cur] = pll(0,0);

  if(i == j)return cur;
  l[cur] = build(i,mid);
  r[cur] = build(mid+1,j);
  return cur;
}
pll sum(pll a,pll b){
  return pll(a.ff + b.ff,a.ss + b.ss);
}

int update(int cur,int a,int b,pll v,int i=1,int j = MX - 10){
  if(i > b or j < a)return cur;
  int novo = ++ID;
  if(novo>=MAX){
    cout<<"ops"<<endl;
    exit(0);
  }
  if(a<=i and j<=b){
  
    lazy[novo] = sum(lazy[cur],v);

    val[novo] = sum(v,val[cur]);
    l[novo] = l[cur];
    r[novo] = r[cur];
    return novo;
  }
  if(lazy[cur]!=pll(0,0)){
    l[cur] = update(l[cur],i,j,lazy[cur],i,mid);
    r[cur] = update(r[cur],i,j,lazy[cur],mid+1,j);
    lazy[cur] = pll(0,0);
  }
  l[novo] = update(l[cur],a,b,v,i,mid);
  r[novo] = update(r[cur],a,b,v,mid+1,j);
  val[novo] = pll(0,0);
  return novo;
}
pll query(int cur,int pos,int i = 1,int j = MX-10){
  if(i == j)return val[cur];
  if(pos<=mid)return sum(lazy[cur],query(l[cur],pos,i,mid));
  else return sum(lazy[cur],query(r[cur],pos,mid+1,j));
}
