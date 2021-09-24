#include <bits/stdc++.h>
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;


int op[] = {5,3,4,1,2,0};

int v[1010][10];

int val(int id,int x){
	int res=0;
	for(int i=0;i<6;i++){
		if(i!=x && i!=op[x]){
			res=max(res,v[id][i]);
		}
	}
	return res;
}
int res[1010][10];

int main(){
	fastio;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)for(int j=0;j<6;j++){
		cin>>v[i][j];
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<6;j++){
			// j virado para cima:
			int baixo = v[i][op[j]]-1;
			res[i][v[i][j]-1] = res[i-1][baixo] + val(i,j);
		}
	}
	int r=0;
	for(int j=0;j<6;j++)r=max(r,res[n][j]);
	cout<<r<<endl;
}
