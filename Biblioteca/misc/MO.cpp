// sample MO
// tested on https://neps.academy/br/exercise/351
void update(int pos){

	qtd[cnt[a[pos]]]--;
	if(vis[pos]==0){ //add
		cnt[a[pos]]++;
	}else{ // remove
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
  

