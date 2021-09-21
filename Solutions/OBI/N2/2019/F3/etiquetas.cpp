#include <bits/stdc++.h>
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;



int n,k,c;
const int N = 10010,M = 1e9 + 7;
int dp[N][N];
bool vis[N][N];
int A[N];
int solve(int i,int j){
	if(i+j*c > n+1)return -1e9;
	if(i==n+1){
		if(j==0)return 0;
		return -1e9;
	}
	if(i>n)return -1e9;
	int&x = dp[i][j];
	if(vis[i][j])return x;
	else vis[i][j]=1;
	x=-1e9;
	if(j)x=solve(i+c,j-1);
	x=max(x,solve(i+1,j)+A[i]);
	return x;
}

int main(){
	fastio;
	cin>>n>>k>>c;
	for(int i=1;i<=n;i++)cin>>A[i];
	cout << solve(1,k) << endl;
}
