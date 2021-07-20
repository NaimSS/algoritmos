ll stars(int n,int m){ // x1 + x2 ... + xn == m
  if(m < 0)return 0;
  assert(n >= 0);
  if(m == 0)return 1;
  return C(n + m - 1,n-1);
}

ll stars_with_upper(int n,int m,int mx){ // 0 <= xi < mx
  ll res=0;
  if(n * (mx-1) < m)return 0; // 
  for(int cnt=0;cnt<=n;cnt++){
    ll cur = (ll)C(n,cnt)*stars(n,m - cnt * mx)%M;
    if(cnt&1)res = (res - cur);
    else res = (res + cur);
    if(res<0)res+=M;
    if(res>=M)res-=M;
  }
  return res;
}
// https://codeforces.com/contest/1096/problem/E
