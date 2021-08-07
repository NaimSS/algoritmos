/*
  fat[i] = (i*fat[i-1])
  inv[i] = (inv[i+1]*(i+1)) ou inv[i] = fat[i] ^ (phi(M) - 1)
  per_caotica[n] = (n-1)*(per_caotica[n-2] + per_caotica[n-1])
  per_caotica[n] = n! * sum(1/k! * (-1)^k)
  sum(C(n,k)*k) = n*2^(n-1)
*/


inline ll mod(ll n, ll m){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll exp(ll a,ll b,ll m){
    
    if(b==0LL) return 1LL;
    if(b==1LL) return mod(a,m);
    ll k = mod(exp(a,b/2,m),m);
    if(b&1LL){
        return mod(a*mod(k*k,m),m);
    }
    else return mod(k*k,m);
}


const int N = 200100;
const int M =;
// long long?

ll fat[N],inv[N];
ll C(int n,int k){
  if(k>n)return 0;
  return mod(fat[n]*mod(inv[k]*inv[n-k],M),M);
}

void init(){
  fat[0] = inv[0] = 1;
  for(int i=1;i<N;i++){
    fat[i] = (1LL*fat[i-1]*i)%M;
  }
  inv[N-1] = exp(fat[N-1],M-2,M);
  for(int i=N-2;i>=0;i--){
    inv[i] = (inv[i+1]*(i+1))%M;
  }
}
// Useful things:

ll S(int n,int k){
  // Stirling numbers of the second kind:
  // Number of partitions of N elements in K non-empty subsets
  ll prod = inv[k];
  ll res=0;
  for(int i=0;i<=k;i++){
    if(i%2==0)res = mod(res + C(k,i)*exp(k-i,n,M),M);
    else res = mod(res - C(k,i)*exp(k-i,n,M),M);
  }

return mod(res*prod,M);

}

// solve for Stars and Bars problem
// https://codeforces.com/contest/1096/problem/E

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





