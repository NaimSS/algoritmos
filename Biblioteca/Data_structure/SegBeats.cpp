// Source: Benq
// O(NlogN ? ), but kinda slow
// tested on https://codeforces.com/contest/815/problem/D -> TLE on test 15
typedef pair<ll,ll> pll;
typedef pair<pll,int> T;
const ll INF = 1e18;
template<int SZ> struct Seg { // SZ is power of TWO!!
  int N,Q;
  ll mxMod[2*SZ], mnMod[2*SZ], mod[2*SZ];
  T mx[2*SZ], mn[2*SZ]; ll sum[2*SZ];
  Seg() { init(); }
  void init(int ind = 1, int L = 0, int R = SZ-1) {
    mxMod[ind] = INF, mnMod[ind] = -INF, mod[ind] = 0; // OK
    if (L == R) {
      mx[ind] = {{0,-INF},1}; mn[ind] = {{0,INF},1}; sum[ind] = 0;
      return;
    } 
    int M = (L+R)/2;
    init(2*ind,L,M); init(2*ind+1,M+1,R);
    pull(ind);
  }
  T combMn(T a, T b) { // MIN
    if (a > b) swap(a,b);
    if (a.ff.ff == b.ff.ff) return {{a.ff.ff,min(a.ff.ss,b.ff.ss)},a.ss+b.ss};
    return {{a.ff.ff,min(a.ff.ss,b.ff.ff)},a.ss};
  }
  T combMx(T a, T b) {
    if (a < b) swap(a,b);
    if (a.ff.ff == b.ff.ff) return {{a.ff.ff,max(a.ff.ss,b.ff.ss)},a.ss+b.ss};
    return {{a.ff.ff,max(a.ff.ss,b.ff.ff)},a.ss};
  }
  void pull(int ind) { // OK
    sum[ind] = sum[2*ind]+sum[2*ind+1];
    mn[ind] = combMn(mn[2*ind],mn[2*ind+1]);
    mx[ind] = combMx(mx[2*ind],mx[2*ind+1]);
  }

  template<class T> bool ckmin(T& a, const T& b) { 
  return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { 
  return a < b ? a = b, 1 : 0; } 

  void push(int ind, int L, int R) {
    auto chk = [](ll& a, ll b, ll c) { if (a == b) a = c; };
    if (mnMod[ind] != -INF) {
      if (mnMod[ind] > mn[ind].ff.ff) {
        assert(mnMod[ind] < mn[ind].ff.ss);
        sum[ind] += (mnMod[ind]-mn[ind].ff.ff)*mn[ind].ss;
        chk(mx[ind].ff.ff,mn[ind].ff.ff,mnMod[ind]);
        chk(mx[ind].ff.ss,mn[ind].ff.ff,mnMod[ind]);
        mn[ind].ff.ff = mnMod[ind];
        if (L != R) 
          rep(i,0,2) {
            int pos = 2*ind+i;
            ckmax(mnMod[pos],mnMod[ind]-mod[pos]);
            ckmax(mxMod[pos],mnMod[pos]);
          }
      }
      mnMod[ind] = -INF;
    }
    if (mxMod[ind] != INF) {
      if (mxMod[ind] < mx[ind].ff.ff) {
        assert(mxMod[ind] > mx[ind].ff.ss);
        sum[ind] += (mxMod[ind]-mx[ind].ff.ff)*mx[ind].ss;
        chk(mn[ind].ff.ff,mx[ind].ff.ff,mxMod[ind]);
        chk(mn[ind].ff.ss,mx[ind].ff.ff,mxMod[ind]);
        mx[ind].ff.ff = mxMod[ind];
        if (L != R) 
          rep(i,0,2) {
            int pos = 2*ind+i;
            ckmin(mxMod[pos],mxMod[ind]-mod[pos]);
            ckmin(mnMod[pos],mxMod[pos]);
          }
      }
      mxMod[ind] = INF;
    }
    if (mod[ind] != 0) {
      sum[ind] += mod[ind]*(R-L+1);
      auto inc = [](T& a, ll b) { 
        if (abs(a.ff.ff) != INF) a.ff.ff += b;
        if (abs(a.ff.ss) != INF) a.ff.ss += b; 
      };
      inc(mx[ind],mod[ind]); inc(mn[ind],mod[ind]);
      if (L != R) 
        rep(i,0,2) {
          int pos = 2*ind+i;
          mod[pos] += mod[ind];
        }
      mod[ind] = 0;
    }
  }
  ll query(int lo, int hi, int ind = 1, int L = 0, int R = SZ-1) {
    push(ind,L,R);
    if (R < lo || hi < L) return 0;
    if (lo <= L && R <= hi) {
      //dbg("???",ind,L,R,sum[ind]);
      return sum[ind];
    }
    int M = (L+R)/2;
    return query(lo,hi,2*ind,L,M)+query(lo,hi,2*ind+1,M+1,R);
  }
  void upd(int lo, int hi, int t, ll b, int ind = 1, int L = 0, int R = SZ-1) {
    push(ind,L,R);
    if (R < lo || hi < L) return;
    if (t == 0) {
      if (b >= mx[ind].ff.ff) return;
    } else if (t == 1) {
      if (b <= mn[ind].ff.ff) return;
    }
    if (lo <= L && R <= hi) {
      if (t == 0) {
        if (b > mx[ind].ff.ss) {
          mxMod[ind] = b; 
          push(ind,L,R); return;
        }
      } else if (t == 1) {
        if (b < mn[ind].ff.ss) {
          mnMod[ind] = b;
          push(ind,L,R); return;
        }
      } else if (t == 2) {
        mod[ind] = b;
        push(ind,L,R); return;
      }
    }
    assert(L != R);
    int M = (L+R)/2;
    upd(lo,hi,t,b,2*ind,L,M); upd(lo,hi,t,b,2*ind+1,M+1,R);
    pull(ind);
  }
};
#define CHMIN 0
#define CHMAX 1
#define ADD 2
#define QUERY 3
// t == 0  - chmin , t ==1 - chmax , t == 2 - add , t == 3 query
