//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <map>
#include <bits/stdc++.h>
#define ff first
#define ss second
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> pii;
const int N = 200100;

int sz[N];
int Sz[N];//Sz para DSU
int pai[N];// para DSU
int find(int x){return pai[x]==x?x:pai[x]=find(pai[x]);}
bool join(int x , int y){
    x = find(x) , y = find(y);
    if(x == y) return 0;
    if(Sz[x] > Sz[y]) swap(x,y);
    pai[x] = y, Sz[y] += Sz[x];
    return 1;
}
map<vector<int>,int> mapa;
int getHash(vi v){
    if(!mapa.count(v))mapa[v] = mapa.size();
    return mapa[v];
}
vi g[N];
int getHash(int v,int p=-1){
    vi hashes;
    for(auto to : g[v])if(to!=p && find(to)==find(v)){
        hashes.push_back(getHash(to,v));
    }
    sort(hashes.begin(),hashes.end());
    return getHash(hashes);
}

vi centr;
void get_centroid(int v,int d,int p=-1){
    int mx=d-sz[v];
    for(auto to : g[v])if(to!=p && find(to)==find(v)){
        get_centroid(to,d,v);
        mx = max(mx,sz[to]);
    }
    if(mx * 2 <= d){
        centr.push_back(v);
    }
}
int ok=1;
vector<pii> Hashes;
void decomposeTree(int v,int d,int p=-1){
    if(!ok)return; // speed up
    for(auto to : g[v])if(to!=p){
        decomposeTree(to,d,v);
        if(!ok)return;
        if(sz[to] < d){
            assert(join(v,to));
            sz[v]+=sz[to];
            assert(sz[v] == Sz[find(v)]);
        }
    }
    if(sz[v] > d){
        ok = 0;
    }
    
    if(sz[v] == d){
        centr.clear();
        get_centroid(v,d,p);
        assert(centr.size() <= 2);
        int a = getHash(centr[0]);
        if(centr.size() == 1){
            Hashes.push_back(pii(-1,a));
        }else{
            int b = getHash(centr[1]);
            if(a > b)swap(a,b);
            Hashes.push_back(pii(a,b));
        }
        if(Hashes.back() != Hashes[0]){
            ok=0;
        }
    }
}

map<pii,int> existe[N];
int here[N];
pii Hash[N];
vector<vector<pii>> ar;
void buildDSU(int n){
    for(int i=1;i<=n;i++){
        pai[i]=i;
        sz[i]=1;
        Sz[i]=1;
    }
}
void build(int id){
    vector<pii> arr = ar[id];
    int n = arr.size() + 1;
    buildDSU(n);
    for(int i=1;i<=n;i++){
        g[i].clear();
    }
    for(auto it : arr){
        g[it.ff].push_back(it.ss);
        g[it.ss].push_back(it.ff);
    }
}

void insertHash(int id){
    build(id);
    Hashes.clear();
    ok=1;
    int n = ar[id].size() + 1;
    decomposeTree(1,n);
    assert(ok && Hashes.size() == 1);
    existe[n][Hashes[0]]++;
    Hash[id] = Hashes[0];
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int k;
    cin >> k;
    int tot=0;
    for(int q=0;q<k;q++){
        int n;
        cin >> n;
        here[n]=1;
        assert(n>=2 && n<=200000);
        tot+=n;
        vector<pii> cur;
        for(int i=1;i<n;i++){
            int a,b;cin>>a>>b;
            assert(min(a,b)>=1 && max(a,b)<=n);
            cur.push_back(pii(a,b));
        }
        ar.push_back(cur);
        insertHash(q);
    }
    assert(tot<=400000);

    int pesoTotal = 0;
    for(int q=0;q<k;q++){
        int ans = -1;//subtract myself
        int n = (ar[q].size()) + 1;
        build(q);
        for(int d=1;d<=n;d++)if(n%d==0 && here[d]){
            ok = 1;
            buildDSU(n);
            Hashes.clear();
            decomposeTree(1,d);
            pesoTotal += n;
            
            if(!ok)continue;
            int num = existe[d][Hashes[0]];
            ans+=num;
        }
        cout << ans << " \n"[q==k-1];
    }

}
