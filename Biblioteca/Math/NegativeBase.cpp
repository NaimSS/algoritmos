// source  https://en.wikipedia.org/wiki/Negative_base
vi res;
while(p!=0){
    int a = p%(-k);
    p/=-k;
    if(a<0){
      a+=k;
      p++;
      
    }
    res.pb(a);
  }
