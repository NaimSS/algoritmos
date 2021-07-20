// a swap changes the parity of inversions !!!

const int inf = 1e9;

int merge(vector<int> &v){
	if(v.size()==1)return 0;
	
	vector<int> u1,u2;

	for(int i=0;i<(int)v.size()/2;i++){
		u1.push_back(v[i]);
	}
	
	for(int i=(int)v.size()/2;i<(int)v.size();i++){
		u2.push_back(v[i]);
	}

	ll res = merge(u1)+merge(u2);
	
	u1.push_back(inf);
	
	u2.push_back(inf);
	
	int pos1 = 0,pos2=0;
	
	for(int i=0;i<(int)v.size();i++){
		if(u1[pos1]<u2[pos2]){
			v[i]=u1[pos1];
			pos1++;
		}else{
			v[i]=u2[pos2];
			res+=u1.size()-1-pos1;
			pos2++;
		}
		
	}
	return res;
}
