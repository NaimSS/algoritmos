void update(int pos){

	qtd[cnt[a[pos]]]--;
	if(vis[pos]==0){
		cnt[a[pos]]++;
	}else{
		cnt[a[pos]]--;
	}
	qtd[cnt[a[pos]]]++;
	if(qtd[ans+1]>0)ans++;
	if(qtd[ans]==0)ans--;
	vis[pos]^=1;
}

//

int cl=1,cr=0;
	

	for(auto it : v){
		int l = it.l;
		int r = it.r;

		//
		while(cr < r)update(++cr);
		//
		while(cr > r)update(cr--);
		//
		while(cl < l)update(cl++);
		//
		while(cl>l)update(--cl);
		//
		
		res[it.id] = ;
	}
  
  // neps pedras seletiva 2015 - just in case of emergency
