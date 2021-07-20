// Tested on : https://codeforces.com/contest/961/problem/F
// Overflow? Didn't use int long long in it ;)

struct Hash{
  const int p[2] = {31,37};
  const int m[2] = {(int)1e9 + 7,(int)1e9 + 9};
  vector<int> h[2],pwr[2];
  int Tam;
  Hash(string& s){
    Tam = sz(s);
    rep(it,0,2){
      h[it] = pwr[it] = vi(sz(s));
      pwr[it][0]=1;
      h[it][0] = s[0];
      rep(i,1,sz(s)){
        h[it][i] = (h[it][i-1]*(ll)p[it] + s[i])%m[it];
        pwr[it][i] = pwr[it][i-1]*(ll)p[it]%m[it];
      }
    }

  }
  pii val(int l,int r){
    if(l>r)swap(l,r);
    pii res;
    rep(it,0,2){
      int cur = (!l ? h[it][r] : h[it][r] - h[it][l-1]*(ll)pwr[it][r-l+1]%m[it]);
      cur%=m[it];
      if(cur<0)cur+=m[it];
      if(it)res.ss=cur;
      else res.ff=cur;
    }
    return res;
  }
};
