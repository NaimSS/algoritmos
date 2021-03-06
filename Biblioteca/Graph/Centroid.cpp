// Compute the centroid of a tree
// O(NlogN) * O(cost of querys)
// tested on https://codeforces.com/contest/715/problem/C
const int N = ;// MAXN here
vi g[N];
int del[N];
int sz[N];
int calc_sz(int v,int p=-1){
  sz[v] = 1;
  for(int to : g[v])if(to!=p and !del[to]){
    sz[v]+=calc_sz(to,v);
  }
  return sz[v];
}
int find_centroid(int v,int p,int tam){
  for(int to : g[v])if(to!=p and !del[to]){
    if(sz[to]*2>tam)return find_centroid(to,v,tam);
  }
  return v;
}


void decompose(int v){
  int tam = calc_sz(v);
  int cent = find_centroid(v,-1,tam);
  compute_answer(cent);
  del[cent] = 1;
  for(int to : g[cent]){
    if(del[to])continue;
    decompose(to);
  }
}
