/*
 * Author: NaimSS
 * find biggest edge in the path a->b
 * O(logN) per query
 * Status: tested
 * https://codeforces.com/contest/1184/problem/E3
 * https://codeforces.com/problemset/problem/827/D
*/

int find_big(int a,int b){
  int res = 0;
  if(L[a]<L[b])swap(a,b);
  for(int j=MAXL-1;j>=0;j--){
      if(L[a] - (1<<j) >= L[b]){
        res = max(res,dp[a][j]);
        a = ans[a][j];
      }
  }
  if(a==b)return res;

  for(int j = MAXL-1;j>=0;j--){
    if(ans[a][j]!=ans[b][j]){
       res = max(res,dp[a][j]);
       res = max(res,dp[b][j]);
       a = ans[a][j];
       b = ans[b][j];
    }
  }
  res = max(res,dp[a][0]);
  res = max(res,dp[b][0]);
  return res;
}


void init(int n){   
  ans[1][0] = 1;
  dp[1][0] = 0;
  dfs(1);

  for(int j=1;j<MAXL;j++){
    for(int i=1;i<=n;i++){
      ans[i][j] = ans[ans[i][j-1]][j-1];
      dp[i][j] = max(dp[i][j-1],dp[ans[i][j-1]][j-1]);
    }
  }
}
