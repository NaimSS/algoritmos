// Tested on https://codeforces.com/contest/817/problem/E
const int MAXL = 30;
struct node{
  node *l,*r;
  int sz;
  node(){
    sz=0;
    l = r = NULL;
  }
  void add(int x,int v,int H = MAXL){//insert/remove
    if(H==-1){
      sz+=v;
      return;
    }
    if(x&(1<<H)){
      if(!r)r=new node();
      r->add(x,v,H-1);
    }else{
      if(!l)l=new node();
      l->add(x,v,H-1);
    }
    sz = Sz(l) + Sz(r);
  }
  int Sz(node *no){
    return !no ? 0 : no->sz;
  }
  int cnt(int x,int L,int H = MAXL){//qtd de caras com xor^x <= L:
    if(!sz)return 0;
    if(H == -1){
      return sz;
    }
    if(x&(1<<H)){
       
     if(L&(1<<H)){
        return Sz(r) + (l ? l->cnt(x,L,H-1) : 0);
      }
      return (r ? r->cnt(x,L,H-1) : 0);
    }else{
      if(L&(1<<H)){
        return Sz(l) + (r ? r->cnt(x,L,H-1) : 0);
      }
      return (l ? l->cnt(x,L,H-1) : 0);
    }
  }
};
