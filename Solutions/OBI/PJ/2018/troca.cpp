#include <bits/stdc++.h>
using namespace std;

int cima[100100];
int baixo[100100];
int vezes[100100]; // >= N + 2
int soma[100100]; // N+1

int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);
	int n,t;
	cin >> n >> t;
	for(int i=1;i<=n;i++){ 
		cin >> cima[i];
	}
	for(int i=1;i<=n;i++){ 
		cin >> baixo[i];
	}
	for(int i=0;i<t;i++){
		int a,b;
		cin >> a >> b;
		vezes[a]+=1;
		vezes[b+1]-=1;
	}

	for(int i=1;i<=n;i++){
		soma[i] = soma[i-1] + vezes[i];
	}

	for(int i=1;i<=n;i++){
		if(soma[i]%2 == 0)
			cout << cima[i] ;
		else
			cout << baixo[i];
		if(i == n)
			cout << "\n";
		else 
			cout << " ";
	}
	


}
