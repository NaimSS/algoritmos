// l>1 , r<=1e12 , r-l <= 1e6
const int MAX = 1e6 + 10;
int mark[MAX];
int mark2[MAX];
void crivo_segmentado(int l,int r){ 
	l = max(l,2LL);
	vector<int> pr;
	for(int i=2;i<MAX;i++){
		if(!mark[i])pr.pb(i);
		for(int j=2*i;j<MAX;j+=i){
			mark[j] = 1;
		}
	}
	for(int i=l;i<=r;i++){
		mark2[i-l] = i;
	}
	for(int it=0;it<pr.size();it++){
		int p = pr[it];
		
		for(int i = (l + p - 1)/p * p ;i<=r;i+=p){
			  while(mark2[i-l]%p==0)mark2[i-l]/=p;
		}
	}
	primes = pr;
	
	for(int i=l;i<=r;i++){
		if(mark2[i-l]!=1)primes.pb(mark2[i-l]);
	}
	std::sort(primes.begin(), primes.end());
	primes.resize(std::unique(primes.begin(), primes.end()) - primes.begin());
}
