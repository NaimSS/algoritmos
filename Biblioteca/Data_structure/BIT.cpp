struct BIT{
 int n;
 int MAX;
 vector<int> bit;
 BIT(){}
 BIT(int _n){
	 n = _n;
	 MAX = n +2;
	 bit.resize(n+10,0);
 }
 
 int query(int x){
	 int r=0;
	 while(x>0){
		 r+=bit[x];
		 x-=(x&-x);
	 }
	 return r;
 }
 
 int query(int l,int r){
	 return query(r) - query(l-1);
 }
 
 void update(int x,int val){
	 while(x<MAX){
		 bit[x]+=val;
		 x+=(x&-x);
	 }
 }
 
 int find_kth(int k){
	 int sum=0;
	 int pos=0;
	 // 30 == log(n) -> trocar conforme necessario
	 for(int i=30;i>=0;i--){
		 if(pos+(1LL<<i)>n)continue;
		 int atual = bit[pos+(1LL<<i)];
		 if(sum+atual<k){
			 sum+=atual;
			 pos+=(1LL<<i);
		 }
		 
	 }
	 
	 //acha a maior pos com <k;
	 return pos+1;
 }
 	
};
