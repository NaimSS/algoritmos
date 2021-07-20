/*
  Solve Problem of divide an array into K blocks, with each cost being max - min , with maximum cost;
  ^ link in yan and leo contest problem H

*/
// https://codeforces.com/contest/321/problem/E -> another problem on D&C -dp


const int MAXN = 200100;

int a[MAXN];
const int K = 20;
pii st[MAXN][K + 1];
int Log[MAXN+1];


pii f(pii a,pii b){
    return pii(min(a.ff,b.ff),max(a.ss,b.ss));
}
int n;
int query(int L,int R){
    int j = Log[R - L + 1];
    pii x = f(st[L][j], st[R - (1 << j) + 1][j]);
    return x.ss - x.ff;
}

long long C(int i, int j){
    //cout<<i<<" "<<j<<" "<<query(i,j)<<endl;
    return query(i,j);
}

vector<long long> dp_before(MAXN), dp_cur(MAXN);

// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int l, int r, int optl, int optr)
{
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    pair<long long, int> best = {0, -1};

    for (int k = optl; k <= min(mid, optr); k++) {
        best = max(best, {(k==0 ? 0 : dp_before[k-1]) + C(k, mid), k});
    }

    dp_cur[mid] = best.first;
  
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}


int32_t main(){
    int k;
    cin>>n>>k;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }   
    for (int i = 0; i < n; i++)
        st[i][0] = pii(a[i],a[i]);

    for (int j = 1; j <= K; j++)
    for (int i = 0; i + (1 << j) <= n; i++)
        st[i][j] = f(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
    
    Log[1] = 0;
    for (int i = 2; i < MAXN; i++)
    Log[i] = Log[i/2] + 1;

    for(int i=0;i<n;i++){
        dp_before[i] = C(0,i);
    }
  
    for(int i=2;i<=k;i++){
        for(int i=0;i<n-1;i++)dp_cur[i]=0;
        compute(i-1,n-1,i-1,n-1);
        
        swap(dp_cur,dp_before);
    }   
    cout<<dp_before[n-1]<<endl;

}

