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
