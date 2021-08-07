// solution to https://cses.fi/problemset/task/2088/  
  rep(i,1,n+1)cin >> x[i],pre[i]=pre[i-1]+x[i];
  rep(t,1,n+1){
    for(int l=1;l+t-1<=n;l++){
      if(t==1){
        dp[l][l] = 0;
        opt[l][l]=l;
        continue;
      }
      int r = l+t-1;
      dp[l][r] = 1e18;
      for(int k= opt[l][r-1];k<=opt[l+1][r];k++){
        ll cost = dp[l][k] + dp[k+1][r] + pre[r]-pre[l-1];
        if(dp[l][r]  > cost){
          dp[l][r]=cost;
          opt[l][r]=k;
        }
      }
    }
  }