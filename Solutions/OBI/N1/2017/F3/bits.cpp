#include <bits/stdc++.h>
using namespace std;



int n,k;
const int N = 1010,M = 1e9 + 7;
int dp[N][N];
int solve(int i,int j){
	if(j == k)return 0;
	if(i == n+1)return 1;
	int&x = dp[i][j];
	if(x!=-1)return x;
	x=solve(i+1,j+1)+solve(i+1,0);
	x%=M;
	return x;
}

int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);
	cin>>n>>k;
	memset(dp,-1,sizeof(dp));
	cout<<solve(1,0)<<endl;
}
