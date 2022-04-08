#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define sz(v) ((int)v.size())
#define rep(i,a,b) for(int i=(a);i<(b);i++)
using namespace std;
#define int long long
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,ll> pll;
const int N = 500100;
ll v[N];
ll pre[N];
int p[N];// ultimo que dá bom

int x,n;
ll maxPre[N];

int P[N];
void getP(){
    // pre[r] - pre[l-1] < 0
    // pre[r] < pre[l-1]
    pre[n+1] = -1e18;
    vector<pll> vec;
    vec.pb(pll(-1e18,n+1));
    for(int i=n;i>=0;i--){
        auto poss = upper_bound(vec.begin(),vec.end(),pll(pre[i],0)) - vec.begin() - 1;
        ll pos = vec[poss].ss;
        P[i] = (pos > n ? n : pos - 1);

        while( pre[i] <= vec.back().first )
            vec.pop_back();
        vec.pb(pll(pre[i],i));
    }
    for(int i=1;i<=n;i++){
        p[i] = P[i-1];
    }
}
ll getPositive(){
    // pre[r] + X - pre[l-1] < 0;
    // pre[r] < pre[l-1] - x
    vector<pll> v;
    v.pb(pll(-1e18,n+1));
    ll res = -n*(n+1)/2 + n;
    for(int i=n;i>=0;i--){
        auto poss = upper_bound(v.begin(),v.end(),pll(pre[i] - x,0)) - v.begin() - 1;
        ll pos = v[poss].ss;
        
        P[i] = (pos > n ? n : pos - 1);

        while( pre[i] <= v.back().first )
            v.pop_back();    
        v.pb(pll(pre[i],i));
    }

    vector<pii> vec;
    for(int i=1;i<=n;i++){
        res+=p[i];
        if(P[i-1]==p[i])continue;;
        if(p[i] >= i){
            vec.pb(pll(i,+P[i-1] - p[i]));
            vec.pb(pll(p[i]+2,-(P[i-1] - p[i])));
        }else{
            assert(p[i] == i-1);
            vec.pb(pll(i,P[i-1] - p[i]));
            vec.pb(pll(i+1,-(P[i-1] - p[i])));
        }
    }
    sort(vec.begin(),vec.end());
    int pt=0;
    ll mx = -1e18;
    ll ini = res;
    for(int i=1;i<=n;i++){
        while(pt < sz(vec) && vec[pt].ff == i){
            res+=vec[pt].ss;
            pt++;
        }
        mx=max(mx,res);
    }
    return mx;
}

int pos[N];
vector<int> here[N];

struct node{
    ll act;
    ll sum,lazy;
    node(ll a=0,ll b=0,ll c=-1):act(a),sum(b),lazy(c){}
    node operator+(const node& o){
        assert(lazy == -1 && o.lazy == -1);
        node r;
        r.act = act + o.act;
        r.sum = sum + o.sum;
        return r;
    }
}tree[4*N];

void flush(int no,int i,int j){
    if(tree[no].lazy == -1)return;
    tree[no].sum = tree[no].act * tree[no].lazy;
    if(i!=j){
        int l = 2*no,r=2*no+1,m=(i+j)/2;
        tree[l].lazy = tree[r].lazy = tree[no].lazy;
    }
    tree[no].lazy=-1;
}

#define UPD_PREFIX 0
#define MAKE_ACT 1
#define MAKE_DACT -1
void upd(int no,int i,int j,int a,int b,int t,int v){
    flush(no,i,j);
    if(i > j || i>b || j<a)return;
    if(a<=i && j<=b){
        if(t == 0)tree[no].lazy = v;
        else{
            if(t==1)tree[no].act = 1,tree[no].sum = v;
            else tree[no].act = 0,tree[no].sum = 0; 
        }
        return flush(no,i,j);
    }
    int l = 2*no,r=2*no+1,m=(i+j)/2;
    upd(l,i,m,a,b,t,v);
    upd(r,m+1,j,a,b,t,v);
    tree[no] = tree[l] + tree[r];
}

int32_t main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> x >> n;
    for(int i=1;i<=n;i++)cin >> v[i];
    for(int i=1;i<=n;i++)pre[i] = pre[i-1] + v[i];
    getP();
    if(x >= 0){
        return cout << getPositive() << endl,0;
    }
    vector<pll> vals;
    
    rep(i,1,n+1)vals.pb(pll(pre[i-1],i));
    sort(vals.begin(),vals.end());

    ll cur=-n*(n+1)/2 + n;
    ll sumDact=0;
    rep(i,1,n+1){
        pos[i] = lower_bound(vals.begin(),vals.end(),pll(pre[i-1],i)) - vals.begin() + 1;
        if(p[i]>=i)
            here[p[i]].pb(i);
        sumDact+=p[i];
        // ativado -> desativado: i
        // desativo -> ativado: p[j] = i
        // desativo perdendo ->
        // pre[i] + x < pre[j-1] -> passa a ser 
    //    cout << "p["<<i<<"] = "<<p[i]<<endl;
    }
    ll mx = -1e18;
    for(int i=n;i>=1;i--){
        for(auto id : here[i]){
            sumDact-=p[id];//tirar ele
            upd(1,1,n,pos[id],pos[id],MAKE_ACT,p[id]);
   //         cout << "MAKE ACT "<<i<<" "<<id<<" "<<p[id]<<" "<<sumDact<<endl;
        }
        // desativo perdendo:
        int pp = upper_bound(vals.begin(),vals.end(),pll(pre[i]+x,n+1)) - vals.begin() + 1;
      //  cout << i<<" "<<pp<<endl;
        if(pp<=n)
            upd(1,1,n,pp,n,UPD_PREFIX,i-1);
        flush(1,1,n);
        mx = max(mx,cur + sumDact + tree[1].sum);
       // cout <<i<<": "<< mx<<" "<<cur<<" "<<sumDact<<" "<<tree[1].sum<<endl;
        // Me desativar de volta:
        if(p[i]>=i)
            sumDact+=p[i],upd(1,1,n,pos[i],pos[i],MAKE_DACT,p[i]);
    }
    cout << mx << endl;
    
}
