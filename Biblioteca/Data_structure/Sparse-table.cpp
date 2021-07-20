// 0-index
namespace RMQ{
int rmq[22][N] , jump[22][N];
void build(vi v){
 int n = v.size();
 for(int i = 0 ;i < n; i ++){
  rmq[0][i] = v[i];
  jump[0][i] = min(i+1,n-1);
 }
 for(int j = 1 ; j < 22 ; j ++){
  for(int i = 0 ; i < n; i ++)
   jump[j][i] = jump[j-1][jump[j-1][i]];
 }
 for(int j = 1 ;j < 22; j ++)
  for(int i = 0 ; i < n; i ++){
   rmq[j][i] = min(rmq[j-1][i] , rmq[j-1][jump[j-1][i]]);
  }
}
 
int query(int l , int r){
 int sz = r-l+1;
 int pot = 31-__builtin_clz(sz) ; 
 return min(rmq[pot][l],rmq[pot][r-(1<<pot) +1]);
}
};
