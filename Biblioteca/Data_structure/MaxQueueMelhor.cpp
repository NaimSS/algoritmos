// tested on https://codeforces.com/gym/102801/problem/K

struct maxqueue{
  vector<pll> q;
  int n;
  int idl,idr;
  maxqueue(){}
  maxqueue(int _n){
    n = _n;
    q.resize(2*n+10,pll(-1,-1));
    idl = idr = n;
  }
  void clear(){
  	idl = idr = n;
  }
   pll back(){
   	if(empty())return pll(-1,-1);
    return q[idr - 1];
  }
  pll front(){
    return q[idl];
  }
  int empty(){
    return  idr <= idl;
  }
  void insert(pll val,int K){// 1->max,0->min
  	//cout << "bota "<<val.ff<<" "<<val.ss<<endl;
  	while(!empty() and front().ss < K)
  		idl++;
    while(!empty() and (back().ss<K || back().ff<=val.ff)){
      idr--;
    }
    q[idr++] = val;
  }
  void erase(int K){
  	while(!empty() and front().ss<K)
  		idl++;
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
  void push_back(pll val){
    q[idr++] = val;
  }
  void push_front(pll val){//not tested
    q[--idl] = val;
  }
  ll query(){
  	return front().ff;
  }
};
