// tested on https://codeforces.com/contest/763/problem/D
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
 
typedef pair<ll,ll> pll;
map<pll,ll> mp;
 
const ll inf = 1e18;
ll H(ll x,ll y){
  if(y == 0)return 0;
  if(mp.count(pll(x,y)))return mp[pll(x,y)];
  return mp[pll(x,y)] = rng()%inf;
}
int n;
const int N = 100100;
vi g[N];
ll Hash[N];
int res = 0;
int ID  =0;
ll HashCima[N];
ll ImRoot[N];
 
 
map<ll,ll> allcnt;
 
void dfscalc(int v,int p = -1){
  if(p == -1){
    ImRoot[v] = Hash[v];
    // calc HashCima:
    map<ll,ll> cnt;
    for(int to : g[v])if(to!=p){
      cnt[Hash[to]]++;
    }
    for(int to : g[v])if(to!=p){
      HashCima[to] = ImRoot[v]^H(Hash[to],cnt[Hash[to]])^H(Hash[to],cnt[Hash[to]]-1);
    }
 
  }else{
    // calc ImRoot
    map<ll,ll> cnt;
    cnt[HashCima[v]]++;
    for(int to : g[v])if(to!=p){
      cnt[Hash[to]]++;
    }
    ImRoot[v] = 0;
    for(auto x : cnt){
      ImRoot[v]^=H(x.ff,x.ss);
    }
 
    for(int to : g[v])if(to!=p){
      HashCima[to] = ImRoot[v]^H(Hash[to],cnt[Hash[to]])^H(Hash[to],cnt[Hash[to]]-1);
    }
    
 
  }
  allcnt[Hash[v]]--;
  allcnt[ImRoot[v]]++;
  if(allcnt[Hash[v]]==0)allcnt.erase(Hash[v]);
  
  if(res < sz(allcnt)){
      res=  sz(allcnt);
      ID = v;
 
  }
 // cout << v<<" "<<sz(allcnt) << endl;
 
  allcnt[ImRoot[v]]--;
  if(allcnt[ImRoot[v]]==0)allcnt.erase(ImRoot[v]);
  for(int to : g[v])if(to!=p){
    allcnt[HashCima[to]]++;
    dfscalc(to,v);
    allcnt[HashCima[to]]--;
    if(allcnt[HashCima[to]]==0)allcnt.erase(HashCima[to]);
  }
  allcnt[Hash[v]]++;
}
 
 
void dfspre(int v,int p=-1){
  int tot=0;
  for(int to : g[v])if(to!=p){
    tot++;
  }
  if(tot==0){
    Hash[v] = 0;
  }else{
    map<ll,ll> cnt;
    for(int to : g[v])if(to!=p){
      dfspre(to,v);
      cnt[Hash[to]]++;
    }
    for(auto x : cnt){
      Hash[v]^=H(x.ff,x.ss);
    }
  }
  allcnt[Hash[v]]++;
}
