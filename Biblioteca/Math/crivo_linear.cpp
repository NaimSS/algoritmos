// crivo linear - calcular mobius em O(N)
// tested on https://codeforces.com/contest/1559/problem/E
// pode achar outras funcoes multiplicativas tb, como phi(N)

const int N = 100100;
vi pr;
int mu[N];
int mark[N];
void crivo(){
  rep(i,1,N){
    mu[i] = 1;
    mark[i] = 0;
  }

  rep(i,2,N){
    if(!mark[i]){
      pr.pb(i);
      mu[i]=-1;
    }

    for(auto p : pr){
      if(1ll * p * i >= N)break;

      mark[i * p] = 1;
      if(i%p == 0){
        mu[i * p] = 0;
        break;
      }else mu[i * p] = -mu[i];

    }

  }
}
