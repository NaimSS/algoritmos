// from viniciustht

struct cx{
    int w,r;
    void read(){
        cin >> w >> r;
        r -= w; // if resistance of box is affected by its own weight
    }
    bool operator<(const cx& b){
        return (w + r > b.w + b.r);
    }
};

int32_t main(){
    int n;
    fastio;
    cin >> n;
    vector<cx> v;
    for(int i=0;i<n;i++){
        cx a;
        a.read();
        if(a.r >= 0){
            v.pb(a);
        }
    }
    sort(td(v));
    n = v.size();
    int dp[n+1][n+1];
    ms(dp,-1);
    dp[0][0] = inf;
    int ans = 0;
    for(int i=1;i<=n;i++){
        dp[i][0] = inf;
        for(int j=1;j<=i;j++){
            dp[i][j] = max(dp[i-1][j],min(dp[i-1][j-1]-v[i-1].w,v[i-1].r));
            if(dp[i][j] >= 0){
                ans = max(ans,j);
            }
        }
    }    
    cout << ans << endl;
    
}

// caixa tem um valor

struct cx{
    int w,r,v;
    void read(){
        cin >> w >> r >> v;
    }
    bool operator<(const cx& b){
        return (w + r < b.w + b.r);
    }
};

int32_t main(){
    int n;
    fastio;
    cin >> n;
    vector<cx> v(n);
    for(int i=0;i<n;i++){
        v[i].read();        
    }
    sort(td(v));
    int maxr = 1e4 * 3;
    vector<int> dp(maxr);
    for(int i=0;i<n;i++){
        for(int j=min(v[i].r,maxr - v[i].w);j>=0;j--){
            dp[j+v[i].w] = max(dp[j+v[i].w],dp[j] + v[i].v);
        }
    }
    cout << *max_element(td(dp)) << endl;
    
}
