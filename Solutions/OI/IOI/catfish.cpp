#include "fish.h"
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<(b);++i)
#define Unique(v) sort(all(v));v.erase(unique(all(v)),v.end());
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define ff first
#define ss second
#define pb push_back
const int N = 100100;
typedef long long ll;
typedef pair<ll,ll> pll;
vector<pll> dp[N][2];
vector<pll> suf[N];
vector<pll> pref[N];

vector<int> posi[N];
vector<int> ys[N];
vector<pll> peixes[N];
vector<pll> peixesSum[N];
const ll inf = 1e18;
long long max_weights(int N, int M, std::vector<int> X, std::vector<int> Y,std::vector<int> W) {
  for(auto &it : Y)it++;
  rep(i,0,M){
    peixes[X[i]].pb(pll(Y[i],W[i]));
    ys[X[i]].pb(Y[i]);
  }

  for(int i=0;i<N;i++){
    sort(all(peixes[i]));
    rep(j,0,sz(peixes[i])){
      peixesSum[i].pb(peixes[i][j]);
      if(j)peixesSum[i][j].ss+=peixesSum[i][j-1].ss;
    }
    posi[i].pb(0);
    if(i)for(auto it : ys[i-1]){
      posi[i].pb(it);
    }
    if(i+1<N)for(auto it : ys[i+1]){
      posi[i].pb(it);
    }
    Unique(posi[i]);
  }



  for(int i=0;i<N;i++){
    
    // calc my dp

    for(int j=0;j<2;j++){

      if(j == 0){
        // subindo!
        // h(i-1) <= h(i).
        // pego um prefixo + valores dos peixes do anterior
        ll val=0;
        int pt=0;
        int ptPref=0;
        for(auto it : posi[i]){
          if(i == 0){
            dp[i][j].pb(pll(it,0));
            continue;
          }
          while(pt < sz(peixes[i-1]) && peixes[i-1][pt].ff<=it){
            val+=peixes[i-1][pt].ss;
            pt++;
          }
          while(ptPref + 1 < sz(pref[i-1]) && pref[i-1][ptPref+1].ff <= it)
            ptPref++;
          dp[i][j].pb(pll(it,pref[i-1][ptPref].ss + val));

        }

      }else{
        // descendo
        // h(i-1) >= h[i]
        // pega sufixo - valores dos meus peixes
        ll val=0;
        int pt=0;
        for(auto it : posi[i]){
          if(i == 0){
            dp[i][j].pb(pll(it,0));
            continue;
          }
          while(pt < sz(peixes[i]) && peixes[i][pt].ff<=it){
            val-=peixes[i][pt].ss;
            pt++;
          }
          auto ItSuf = lower_bound(all(suf[i-1]),pll(it,-inf));
          if(ItSuf == suf[i-1].end()){
            dp[i][j].pb(pll(it,0));
          }else{
            dp[i][j].pb(pll(it,val + ItSuf->ss));
          }
        }
      }

    }
    // calc pref -> subtrair os peixes de i

    ll val=0;
    int pt=0;
    for(auto it : dp[i][0]){
      while(pt < sz(peixes[i]) && peixes[i][pt].ff <= it.ff){
        val+=peixes[i][pt].ss;
        pt++;
      }
      pref[i].pb(pll(it.ff,it.ss - val));
    }
    // pref[i][0]: pode ter ignorado tudo tb:
    if(i){
      rep(j,0,sz(dp[i-1][0])){
        ll v = max(dp[i-1][0][j].ss,dp[i-1][1][j].ss);
        pref[i][0].ss = max(pref[i][0].ss,v);
      }
    }

    for(int j=1;j<sz(pref[i]);j++){
      pref[i][j].ss = max(pref[i][j].ss,pref[i][j-1].ss);
    }

    // calc suf -> somar peixes de i+1
    int K = 0;
    for(auto it : dp[i][1]){
      ll peixesNext = 0;
      if(i+1<N){
        int pos = upper_bound(all(peixes[i+1]),pll(it.ff,inf)) - peixes[i+1].begin() - 1;
        if(pos >= 0)peixesNext = peixesSum[i+1][pos].ss;
      }
      suf[i].pb(pll(it.ff,max(it.ss,dp[i][0][K].ss) + peixesNext));
      K++;
    }

    for(int j=sz(suf[i])-2;j>=0;j--){
      suf[i][j].ss = max(suf[i][j].ss,suf[i][j+1].ss);
    }

  }
  
  ll res=0;
  rep(j,0,2)for(auto it : dp[N-1][j])res=max(res,it.ss);
  return res;
}
