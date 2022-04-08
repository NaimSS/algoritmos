#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i < (b); ++i)
using namespace std;
const int N = 100100;

long long T[N],D[N];
long long pre[N];
int used[N];

const long long inf = 1e18;

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    auto z = clock();
    int n;
    cin >> n;
    vector<int> ids;
    for(int i=0;i<n;i++){
        cin >> T[i] >> D[i];
        ids.push_back(i);
    }
    sort(ids.begin(),ids.end(),[&](int a,int b){
        return D[a] < D[b];
    });

    long long cur=0;
    int flag=0;
    rep(i,0,n){     
        cur+=T[ids[i]];
        if(cur>D[ids[i]]){
            flag=1;
            break;
        }
    }
    if(flag){
        // print invalid
        cout<<"*"<<endl;
        return 0;
    }
    vector<int> res;
    long long acu=0;
    rep(step,0,n){

        long long mn = inf;
        int mn_id = n + 1,idx=0;
        
        rep(i,0,n){ // 
            pre[i] = (!i ? 0 : pre[i-1]);
            if(!used[i]){
                if(T[ids[i]] <= mn && ids[i] < mn_id){
                    mn_id = ids[i];
                    idx = i;
                }
                pre[i] += T[ids[i]];
                mn = min(mn,D[ids[i]] - acu - pre[i]);
            }
        }
        assert(mn_id!=n+1);
        res.push_back(mn_id);

        used[idx] = 1;
        acu+=T[mn_id];
    }

    cur=0;
    for(auto id : res){
      cur+=T[id];
      if(cur > D[id]){
        assert(0);
      }
    }
    rep(i,0,n)cout<<res[i]+1<<" \n"[i==n-1];
    //cerr << (double)(clock() - z)/CLOCKS_PER_SEC << endl;
    return 0;
}
