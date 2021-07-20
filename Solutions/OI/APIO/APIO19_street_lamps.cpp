#include <bits/stdc++.h>
#define pb push_back
#define mp(a,b) make_pair(a,b)
#define all(v) v.begin(),v.end()
#define ff first
#define ss second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(v) ((int)v.size())
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> pii;


template<class T, int SZ> struct OffBIT2D { 
  bool mode = 0; // mode = 1 -> initialized
  vector<pii> todo; // locations of updates to process
  int cnt[SZ], st[SZ];
  vi val; vector<T> bit; // store all BITs in single vector
  void init() { assert(!mode); mode = 1;
    int lst[SZ]; 
    rep(i,0,SZ) lst[i] = cnt[i] = 0;
    sort(all(todo),[](const pii& a, const pii& b) { 
      return a.ss < b.ss; });
    trav(t,todo) for (int x = t.ff; x < SZ; x += x&-x) {
          if (lst[x] != t.ss) lst[x] = t.ss, cnt[x] ++;
    }

    int sum = 0; rep(i,0,SZ) lst[i] = 0, st[i] = (sum += cnt[i]);
    val.resize(sum); bit.resize(sum); reverse(all(todo));
    trav(t,todo) for (int x = t.ff; x < SZ; x += x&-x) 
      if (lst[x] != t.ss) lst[x] = t.ss, val[--st[x]] = t.ss;
  }
  int rank(int y, int l, int r) {
    return upper_bound(begin(val)+l,begin(val)+r,y)-begin(val)-l; }
  void UPD(int x, int y, T t) {
    for (y = rank(y,st[x],st[x]+cnt[x]); y <= cnt[x]; y += y&-y) 
      bit[st[x]+y-1] += t; }
  void upd(int x, int y, T t) { 
    if (!mode) todo.pb({x,y});
    else for (;x<SZ;x+=x&-x) UPD(x,y,t); }
  int QUERY(int x, int y) { T res = 0;
    for (y = rank(y,st[x],st[x]+cnt[x]); y; y -= y&-y) res += bit[st[x]+y-1];
    return res; }
  T query(int x, int y) { assert(mode);
    T res = 0; for (;x;x-=x&-x) res += QUERY(x,y);
    return res; }
  T query(int xl, int xr, int yl, int yr) { 
    return query(xr,yr)-query(xl-1,yr)
      -query(xr,yl-1)+query(xl-1,yl-1); }
};

typedef long long ll;

struct event{
  int l,r,mx;
  ll v;
};

OffBIT2D<ll,300100> BIT;

vector<event> ev;

int n,q;
void add_event(int l,int r,int mx,ll v,int A=0){
  BIT.upd(l,mx,v);
  if(r!=n)BIT.upd(r+1,mx,-v);
  if(!A)ev.pb({l,r,mx,v});
}

ll ask(int a,int b,int A=0){
  ll res=0;
  if(!A)ev.pb({a,b,-1,-1});
  else{
    res = BIT.query(1,a,b,n);
  }
  return res;
}

const int N = 300100;
char s[N];

int fim[N];

int last[N];
string Q[N];
int a[N],b[N];


int32_t main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  cin >> n >> q;
  for(int i=1;i<=n;i++){
    cin >> s[i];
  }
  s[0]='0';
  set<pii> S;
  s[n+1]='0';
  for(int i=n;i>=0;i--){
    last[i] = 0;
    if(s[i] =='1'){
      if(s[i+1]=='1')fim[i] = fim[i+1];
      else{
        fim[i] = i;
      }
      continue;
    }
    if(s[i+1]=='1'){
      S.insert(pii(i+1,fim[i+1]));
    }
  }
  
  for(int i=1;i<=q;i++){
    cin >> Q[i];
    if(Q[i][0]=='t'){
      cin >> a[i];
      int pos = a[i];
      if(s[pos] == '0'){
        s[pos] ='1';
        int l = pos,r = pos;
        if(s[pos-1]=='1'){
          auto it = S.lower_bound(pii(pos,-1));
          assert(it!=S.begin());
          it--;
          l = it->ff;
          add_event(it->ff,it->ss,it->ss,i-last[it->ff]);
          last[it->ff] = i;
          S.erase(it);
        }
        if(s[pos+1]=='1'){
          auto it = S.lower_bound(pii(pos,-1));
          assert(it!=S.end());
          r=it->ss;
          add_event(it->ff,it->ss,it->ss,i-last[it->ff]);
          last[it->ff] = i;
          S.erase(it);
        }
        S.insert(pii(l,r));
        last[l] = i;
        
       // db2(l,r);
      }else{

        s[pos]='0';
        auto it = S.lower_bound(pii(pos+1,-1));
        assert(it!=S.begin());
        it--;
        int t = last[it->ff];
        int l = it->ff,r = it->ss;
        
        if(pos!=r)
          last[pos+1] = t;
        
        add_event(it->ff,pos,it->ss,i-last[it->ff]);
        
        S.erase(it);
        last[l] = i;
        if(pos!=l)S.insert(pii(l,pos-1));
        if(pos!=r)S.insert(pii(pos+1,r));
      }

    }else{
      cin >> a[i] >> b[i];
      b[i]--;
      if(s[a[i]] == '0'){
        ask(a[i],b[i]);
        continue;
      }
      auto it = S.lower_bound(pii(a[i]+1,-1));
      it--;
      add_event(it->ff,it->ss,it->ss,i-last[it->ff]);
      last[it->ff] = i;
      ask(a[i],b[i]);
    }
  }
  BIT.init();

  for(auto it : ev){
    if(it.mx != -1){
      add_event(it.l,it.r,it.mx,it.v,1);
    }else{
      cout << ask(it.l,it.r,1) << '\n';
    }
  }
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
