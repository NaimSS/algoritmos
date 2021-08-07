// from benqi

template<class T> struct RMQ { // floor(log_2(x))
  int level(int x) { return 31-__builtin_clz(x); } 
  vector<T> v; vector<vi> jmp;
  int comb(int a, int b) { // index of min
    return v[a]==v[b]?min(a,b):(v[a]<v[b]?a:b); } 
  void init(const vector<T>& _v) {
    v = _v; jmp = {vi(sz(v))}; iota(all(jmp[0]),0);
    for (int j = 1; 1<<j <= sz(v); ++j) {
      jmp.pb(vi(sz(v)-(1<<j)+1));
      rep(i,0,sz(jmp[j])) jmp[j][i] = comb(jmp[j-1][i],
                  jmp[j-1][i+(1<<(j-1))]);
    }
  }
  int index(int l, int r) { // get index of min element
    int d = level(r-l+1);
    return comb(jmp[d][l],jmp[d][r-(1<<d)+1]); }
  T query(int l, int r) { return v[index(l,r)]; }
};
