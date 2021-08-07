	//https://cses.fi/problemset/task/1654
  for(int i=0;i<n;i++){
		cin>>a[i];
		F1[a[i]]++;
		F2[a[i]]++;
	}
	int full=0;
	for(int i=0;i<20;i++)full+=(1<<i);
 
	
	for(int i=0;i<20;i++){
		for(int msk=1;msk<MAXN;msk++){
			if((msk&(1LL<<i)))F1[msk]+=F1[msk^(1<<i)];
			if((msk&(1LL<<i)))F2[msk^(1<<i)]+=F2[msk];
			
		}
	}
 
	
	for(int i=0;i<n;i++){
		cout<<F1[a[i]]<<" "<<F2[a[i]]<<" "<<n-F1[full^a[i]]<<endl;
	}
  // F1 -> qtd de caras tal que y|a[i] = a[i]
  // F2 -> qtd de caras tal que y&a[i] = a[i] 
  // F3 -> qtd de caras tal que y&a[i]!=0 
