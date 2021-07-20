#include "crocodile.h"
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;
#define pb push_back

const int MAXN = 1e5 + 100;
int vis[MAXN];
int cnt[MAXN];
ll d[MAXN];
typedef pair<ll,ll> pll;
vector<pii> g[MAXN];

priority_queue<ll,vector<ll>,greater<ll> > fila[MAXN];
void process(int id,bool clear = 0){
  ll x = fila[id].top();
  fila[id].pop();
  if(fila[id].empty() and !clear){
    fila[id].push(x);
    return;
  }

  d[id] = min(d[id],fila[id].top());
  fila[id].push(x);
  if(clear){
    while(!fila[id].empty())fila[id].pop();
  }
}
const int inf = 1e9;
int travel_plan(int N, int M, int R[][2], int L[], int K, int P[]){ 

  for(int i=0;i<M;i++){
    g[R[i][0]].pb(pii(R[i][1],L[i]));
    g[R[i][1]].pb(pii(R[i][0],L[i]));
  }   
  for(int i=0;i<N;i++)vis[i] = 0,d[i] = 1e18;
  priority_queue<pll,vector<pll>,greater<pll> > pq; 
  for(int i=0;i<K;i++){
    d[P[i]] = 0;
    vis[P[i]] = 1;
    cnt[P[i]] = -MAXN * 3;
    for(pii to : g[P[i]]){
      fila[to.ff].push(to.ss);
      cnt[to.ff]++;
    }
  }
  for(int i=0;i<N;i++){
    if(cnt[i]>=2){
      process(i,0);
      pq.push(pll(d[i],i));
    }
  }

  while(!pq.empty()){
    int cur=pq.top().ss;pq.pop();
    if(vis[cur])continue;
    vis[cur] = 1;
    process(cur,1);
    if(d[cur] > inf)continue;
    for(auto to : g[cur]){
      if(!vis[to.ff]){
        fila[to.ff].push(to.ss + d[cur]);
        ll antes = d[to.ff];
        process(to.ff);
        if(d[to.ff]!=antes)pq.push(pll(d[to.ff],to.ff));
      }
    }
  }

  int x = d[0];
  return x;
}
