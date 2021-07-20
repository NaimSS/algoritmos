/* Se queremos colocar O(N) separadores com N<=1e5 basta botar todos iguais a '#'
 * E então fazer:
  Para todo '#' settar como 0
  if(tot[sa.sa[i]] == '#')sa.lcp[i] = 0;
  Para toda string que vai de [ini[i],fim[i]] ajusta o lcp pra não passar do separador
  sa.lcp[pos] = min(sa.lcp[pos],(fim[i] - j + 1));
*/


struct SuffixArray {
  vi sa, lcp;
  SuffixArray(){}
  SuffixArray(string& s, int lim=256) { // or basic_string<int>
    int n = sz(s) + 1, k = 0, a, b;
    vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
    sa = lcp = y, iota(all(sa), 0);
    for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
      p = j, iota(all(y), n - j);
      rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
      fill(all(ws), 0);
      rep(i,0,n) ws[x[i]]++;
      rep(i,1,lim) ws[i] += ws[i - 1];
      for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
      swap(x, y), p = 1, x[sa[0]] = 0;
      rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
        (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
    }
    rep(i,1,n) rank[sa[i]] = i;
    for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
      for (k && k--, j = sa[rank[i] - 1];
          s[i + k] == s[j + k]; k++);
  }
};
const int N = 400100;
struct RMQ{
  vi rmq[22] , jump[22];
  void build(vi v){
   int n = v.size();
    rep(i,0,22){
      rmq[i].resize(n+100,0);
      jump[i].resize(n+100,0);
    }
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
 
   assert(l<=r);
   int sz = r-l+1;
   int pot = 31-__builtin_clz(sz) ; 
   return min(rmq[pot][l],rmq[pot][r-(1<<pot) +1]);
  }
};
 
int rev[N];
