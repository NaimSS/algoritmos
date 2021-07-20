// Author : ME :)
// tested on https://codeforces.com/gym/100570/problem/C
// 3360ms vs 4800ms using deque
struct minqueue{
  vector<pii> q;
  int n;
  int idl,idr;
  minqueue(){}
  minqueue(int _n){
    n = _n;
    q.resize(2*n+10);
    idl = idr = n;
  }
   pii back(){
    return q[idr - 1];
  }
  pii front(){
    return q[idl];
  }
  int empty(){
    return  idr <= idl;
  }
  void insert(pii val,int f=0){// 1->max,0->min

    while(empty() and (f ? (back().ff<=val.ff) : (back().ff>=val.ff))){
      idr--;
    }
    q[idr++] = val;
  }
  void pop_front(){
    idl++;
  }
  void pop_back(){
    idr--;
  }
  int size(){
    return idr-idl;
  }
  void push_back(pii val){
    q[idr++] = val;
  }
  void push_front(pii val){//not tested
    q[--idl] = val;
  }

};
