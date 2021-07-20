// Exemplo Lazy de OR, query de AND. Ver os VALORES INCIAIS NO BUILD!!!
template <class T> 
struct lazy_seg{
public:
  vector<T>  st , lazy;
  lazy_seg(int n){
    st.resize(4*n + 1 , 0) , lazy.resize(4*n + 1, 0);
  }
  lazy_seg() = default;
  
 
  T propagate(T a,T b,int l,int r){
    // edit here
    return  a|b;
  }
  T combineTree(T a,T b){
    // junta as querys/arvores
    // edit here
    return (a&b);
  }
  void combinelazy(T& a,T b){
    // junta as lazys
    // edit here
    a|=b;
  }
  
  void push(int l , int r , int curr){
    if(lazy[curr] != 0){
      st[curr] =  propagate(st[curr],lazy[curr],l,r);
      if(l!=r){
        combinelazy(lazy[2*curr],lazy[curr]);
        combinelazy(lazy[2*curr + 1],lazy[curr]);
      }
      lazy[curr] = 0;
    }
  }
  
  void pull(int l , int r , int curr){
    push(l,r,curr); int mid = (l+r)/2;
    if(l!=r) push(l,mid,2*curr) , push(mid+1,r,2*curr+1);
    st[curr] = combineTree(st[2*curr] , st[2*curr+1]);
  }
  void upd(int x , int y, T v,  int l, int r , int curr){
    int mid = (l+r)/ 2;  push(l,r,curr);
    if(l == x && r == y){
      // EDIT HERE !!
      lazy[curr] |= v;
      // *************
      push(l,r,curr);
      return ;
    }
    if(y <= mid) upd(x,y,v,l,mid,2*curr);
    else if(x > mid) upd(x,y,v,mid+1,r,2*curr+1);
    else upd(x,mid,v,l,mid,2*curr) , upd(mid+1,y,v,mid+1,r,2*curr+1);
    pull(l,r,curr);
  }
  T qry(int x , int y , int l , int r , int curr){
    int mid = (l+r)/2; push(l,r,curr);
    if(l == x && r == y) return st[curr];
    if(y <= mid) return qry(x,y,l,mid,2*curr);
    else if(x > mid) return qry(x,y,mid+1,r,2*curr+1);
    return combineTree(qry(x,mid,l,mid,2*curr) , qry(mid+1,y,mid+1,r,2*curr+1));
  }
  void build(int l , int r,  int curr){
    lazy[curr] = 0; // edit here
    int mid = (l+r)/2;
    if(l == r){ // EDIT HERE
      st[curr] = 0; 
      return ;
    }
    build(l,mid,2*curr);
    build(mid+1,r,2*curr+1);
    st[curr] = combineTree(st[2*curr] , st[2*curr+1]);
  }
};
